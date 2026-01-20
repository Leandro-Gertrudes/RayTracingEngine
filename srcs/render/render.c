/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:48:20 by ghenriqu          #+#    #+#             */
/*   Updated: 2026/01/18 17:03:30 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define DEPTH 3
#define TEST_REFLECTIVITY 0.5

void	image_put_pixel(t_image *img, int x, int y, t_rgb color);

t_rgb apply_specular(
    t_vec3 normal,
    t_vec3 light_dir,
    t_vec3 view_dir,
    t_light *light,
    double shininess
)
{
    t_vec3 reflect_dir;
    double spec;
    t_rgb res;

    reflect_dir = reflect(light_dir, normal);
    spec = vec3_dot(reflect_dir, view_dir);
    if (spec < 0)
        spec = 0;
    spec = pow(spec, shininess);
    res.r = light->color.r * light->ratio * spec;
    res.g = light->color.g * light->ratio * spec;
    res.b = light->color.b * light->ratio * spec;
    return (res);
}


void	*render_thread(void *arg)
{
	t_thread_data	*data;
	int				y;
	int				x;
	t_rgb			color;

	data = (t_thread_data *)arg;
	y = data->y_start;
	while (y < data->y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = compute_pixel_color(
					data->scene,
					make_ray(x, y, data->scene),
					DEPTH);
			if (g_mode == SAVE_FRAMES)
				image_put_pixel(data->scene->image, x, y, color);
			else
				put_pixel(data->scene, x ,y, rgb_to_int(color));
			x++;
		}
		y++;
	}
	return (NULL);
}

/*
typedef struct s_render_st
{
	t_vec3	point;
	t_vec3	normal;
	t_rgb	local_color;
	t_rgb	reflected_color;
	t_ray	rd.reflected_ray;
}	t_render_st;
*/

/*
double	fresnel_schlick(double cos_theta, double f0)
{
	return (f0 + (1.0 - f0) * pow(1.0 - cos_theta, 5.0));
}


t_rgb	compute_pixel_color(t_scene *scene, t_ray ray, int depth)
{
	t_hit		hit;
	t_render_st	rd;
	double		r;
	double		fresnel;
	t_vec3		in_dir;
	double		cos_theta;

	if (depth <= 0 || !hit_objects(scene, ray, &hit))
		return ((t_rgb){0, 0, 0});

	// Ponto de impacto
	rd.point = vec3_add(ray.origin,
			vec3_scale(ray.direction, hit.t));

	// Normal correta
	rd.normal = vec3_normalize(get_normal(&hit, rd.point));
	if (vec3_dot(rd.normal, ray.direction) > 0)
		rd.normal = vec3_scale(rd.normal, -1);

	// Iluminação local
	rd.local_color = shade_hit(scene, &hit, rd.point, rd.normal);

	// Direção de entrada normalizada
	in_dir = vec3_normalize(ray.direction);

	// Ângulo entre view e normal
	cos_theta = -vec3_dot(in_dir, rd.normal);
	if (cos_theta < 0.0)
		cos_theta = 0.0;

	// Reflexividade base do material
	r = get_reflectivity(&hit);

	// Fresnel (Schlick)
	fresnel = fresnel_schlick(cos_theta, r);

	// Se não reflete, retorna shading normal
	if (fresnel <= 0.001)
		return (rd.local_color);

	// Raio refletido
	rd.reflected_ray.origin = vec3_add(
			rd.point,
			vec3_scale(rd.normal, 1e-6)
	);
	rd.reflected_ray.direction = vec3_reflect(in_dir, rd.normal);

	rd.reflected_color = compute_pixel_color(
			scene,
			rd.reflected_ray,
			depth - 1
	);

	// Mistura com Fresnel
	return (rgb_clamp(rgb_add(
			vec3_rgb_scale(rd.local_color, 1.0 - fresnel),
			vec3_rgb_scale(rd.reflected_color, fresnel)
	)));
}
*/

t_rgb	compute_pixel_color(t_scene *scene, t_ray ray, int depth)
{
	t_hit		hit;
	t_render_st	rd;
	double		r;

	if (depth <= 0 || !hit_objects(scene, ray, &hit))
		return ((t_rgb){0, 0, 0});
	rd.point = vec3_add(ray.origin, vec3_scale(ray.direction, hit.t));
	rd.normal = get_normal(&hit, rd.point);
	rd.local_color = shade_hit(scene, &hit, rd.point, rd.normal);
	if (vec3_dot(rd.normal, ray.direction) > 0)
		rd.normal = vec3_scale(rd.normal, -1);
	r = get_reflectivity(&hit);
	if (r <= 0.0)
		return (rd.local_color);
	rd.reflected_ray.origin = vec3_add(rd.point,
			vec3_scale(rd.normal, 1e-4));
	rd.reflected_ray.direction = vec3_normalize(
			vec3_reflect(ray.direction, rd.normal));
	rd.reflected_color = compute_pixel_color(scene,
			rd.reflected_ray, depth - 1);
	return (rgb_clamp(rgb_add(
				vec3_rgb_scale(rd.local_color, 1.0 - r),
				vec3_rgb_scale(rd.reflected_color, r)
			)));
}

// static void	render_row(t_scene *scene, int y)
// {
// 	int		x;
// 	t_rgb	color;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		color = compute_pixel_color(scene, make_ray(x, y, scene), DEPTH);
// 		put_pixel(scene, x, y, rgb_to_int(color));
// 		x++;
// 	}
// }

void	display_image(t_scene *scene)
{
	if (scene->disp.mlx && scene->disp.win && scene->disp.img)
		mlx_put_image_to_window(scene->disp.mlx,
			scene->disp.win, scene->disp.img, 0, 0);
}

void	render_scene(t_scene *scene)
{
	pthread_t		threads[THREAD_COUNT];
	t_thread_data	data[THREAD_COUNT];
	int				i;
	int				rows_per_thread;

	rows_per_thread = HEIGHT / THREAD_COUNT;
	i = 0;
	while (i < THREAD_COUNT)
	{
		data[i].scene = scene;
		data[i].y_start = i * rows_per_thread;
		data[i].y_end = (i + 1) * rows_per_thread;
		if (i == THREAD_COUNT - 1)
			data[i].y_end = HEIGHT;
		pthread_create(&threads[i], NULL, render_thread, &data[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	display_image(scene);
}

void	put_pixel(t_scene *scene, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = scene->disp.addr + (y * scene->disp.line_length
			+ x * (scene->disp.bpp / 8));
	*(unsigned int *)dst = color;
}

void	image_put_pixel(t_image *img, int x, int y, t_rgb color)
{
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	img->pixels[y * img->width + x] = color;
}

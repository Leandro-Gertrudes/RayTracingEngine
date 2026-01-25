/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:57:06 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/25 16:49:21 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	get_object_color(t_hit *hit)
{
	if (hit->type == SPHERE)
		return (((t_sphere *)hit->object)->color);
	if (hit->type == PLANE)
		return (((t_plane *)hit->object)->color);
	if (hit->type == CYLINDER)
		return (((t_cylinder *)hit->object)->color);
	if (hit->type == TRIANGLE)
		return (((t_triangle *)hit->object)->color);
	return ((t_rgb){0, 0, 0});
}
// t_vec3 get_light_position(t_scene *scene)
// {
//     int i;

//     if (scene->obj_edit.type == LIGHT && scene->obj_edit.data && g_edit)
//     {
//         t_light *l = scene->obj_edit.data;
//         return l->position;
//     }


//     for (i = 0; i < scene->light_count; i++)
//     {
//         if (scene->lights[i])
//             return scene->lights[i]->position;
//     }
//     return (t_vec3){0, 0, 0};
// }


t_rgb	low_compute_pixel_color(t_scene *scene, t_ray ray)
{
	t_hit	hit;
	t_vec3	point;
	t_vec3	normal;
	t_vec3	light_dir;
	double	diff;
	t_rgb	color;
	t_rgb	ambient;

	if (!hit_objects(scene, ray, &hit))
		return ((t_rgb){0, 0, 0});

	if (hit.type == LIGHT)
		return (((t_light *)hit.object)->color);

	point = vec3_add(ray.origin, vec3_scale(ray.direction, hit.t));
	normal = get_normal(&hit, point);

	color = get_object_color(&hit);

	ambient.r = color.r * scene->ambient->ratio;
	ambient.g = color.g * scene->ambient->ratio;
	ambient.b = color.b * scene->ambient->ratio;

	if (!g_low_light)
		return (ambient);

	light_dir = vec3_normalize(
		vec3_sub(g_low_light->position, point)
	);

	diff = vec3_dot(normal, light_dir);
	if (diff < 0)
		diff = 0;

	color.r = color.r * diff + ambient.r;
	color.g = color.g * diff + ambient.g;
	color.b = color.b * diff + ambient.b;

	return (color);
}


void	*low_render_thread(void *arg)
{
	t_thread_data	*data;
	int				y;
	int				x;
	int				dx;
	int				dy;
	int				step;
	t_rgb			color;

	data = (t_thread_data *)arg;
	step = 4;

	y = data->y_start;
	while (y < data->y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = low_compute_pixel_color(
					data->scene,
					make_ray(x, y, data->scene));

			dy = 0;
			while (dy < step)
			{
				dx = 0;
				while (dx < step)
				{
					if (x + dx < WIDTH && y + dy < HEIGHT)
					{

					if (g_mode == SAVE_FRAMES)
							image_put_pixel(data->scene->image, x, y, color);
					else
						put_pixel(data->scene,
							x + dx, y + dy,
							rgb_to_int(color));
					}
					dx++;
				}
				dy++;
			}
			x += step;
		}
		y += step;
	}
	return (NULL);
}

void	low_render_scene(t_scene *scene)
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
		pthread_create(&threads[i],
			NULL, low_render_thread, &data[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	display_image(scene);
	if(g_mode != SAVE_FRAMES)
		draw_hud(scene);
}

void draw_hud(t_scene *scene)
{
	int x = 10, y = 10;
	int w = 185, h = 220; 
	int alpha = 150;
	t_rgb color;
	char buf[128];

	//box
	for (int j = y; j < y + h; j++)
	{
		for (int i = x; i < x + w; i++)
		{
			t_rgb old = get_pixel(scene, j, i);

			color.r = (old.r * (255 - alpha)) / 255;
			color.g = (old.g * (255 - alpha)) / 255;
			color.b = (old.b * (255 - alpha)) / 255;

			put_pixel(scene, j, i, rgb_to_int(color));
		}
	}

	mlx_put_image_to_window(scene->disp.mlx, scene->disp.win,
		scene->disp.img, 0, 0);

	int line_y = y + 15;
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFD700, "MiniRaytracer");
	line_y += 20;

	snprintf(buf, sizeof(buf), "Mode: %s", ("PREVIEW"));
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf);
	line_y += 20;

	snprintf(buf, sizeof(buf), "Camera Pos: (%.2f, %.2f, %.2f)",
		scene->camera->position.x, scene->camera->position.y, scene->camera->position.z);
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf);
	line_y += 20;

	snprintf(buf, sizeof(buf), "Camera Vec: (%.2f, %.2f, %.2f)",
		scene->camera->vector.x, scene->camera->vector.y, scene->camera->vector.z);
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf); // vetor em ciano
	line_y += 20;

	snprintf(buf, sizeof(buf), "Objects: %d", scene->object_count);
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf);
	line_y += 20;
	
	snprintf(buf, sizeof(buf), "Lights: %d", scene->light_count);
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf);
	line_y += 20;

	snprintf(buf, sizeof(buf), "FOV: %d", scene->camera->fov);
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf);
}
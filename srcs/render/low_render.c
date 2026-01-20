/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:57:06 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/18 16:58:53 by lgertrud         ###   ########.fr       */
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


t_rgb	low_compute_pixel_color(t_scene *scene, t_ray ray)
{
	t_hit	hit;
	t_vec3	point;
	t_vec3	normal;
	t_vec3	light_dir;
	double	diff;
	t_rgb	color;

	if (!hit_objects(scene, ray, &hit))
		return ((t_rgb){0, 0, 0});

	point = vec3_add(ray.origin, vec3_scale(ray.direction, hit.t));
	normal = get_normal(&hit, point);

	light_dir = vec3_normalize(
		vec3_sub(scene->lights[0]->position, point)
	);

	diff = vec3_dot(normal, light_dir);
	if (diff < 0)
		diff = 0;

	color = get_object_color(&hit);
	color.r *= diff;
	color.g *= diff;
	color.b *= diff;

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
	step = 4; // <<< CONTROLA A QUALIDADE (4, 6, 8...)

	y = data->y_start;
	while (y < data->y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = low_compute_pixel_color(
					data->scene,
					make_ray(x, y, data->scene)); // <<< depth baixo

			dy = 0;
			while (dy < step)
			{
				dx = 0;
				while (dx < step)
				{
					if (x + dx < WIDTH && y + dy < HEIGHT)
						put_pixel(data->scene,
							x + dx, y + dy,
							rgb_to_int(color));
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
}
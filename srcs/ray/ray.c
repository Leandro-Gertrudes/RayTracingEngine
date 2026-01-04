/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:41:55 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/13 20:57:08 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ft_ray(t_vec3 o, t_vec3 d)
{
	t_ray	r;

	r.origin = o;
	r.direction = vec3_normalize(d);
	return (r);
}

t_ray	make_ray(int x, int y, t_scene *scene)
{
	double	u;
	double	v;
	t_vec3	pixel_dir;

	u = (double)x / (WIDTH - 1);
	v = (double)y / (HEIGHT - 1);
	u = u - 0.5;
	v = 0.5 - v;
	pixel_dir = vec3_add(vec3_add(
				vec3_scale(scene->camera->camdata.right,
					u * scene->camera->camdata.viewport_width),
				vec3_scale(scene->camera->camdata.up,
					v * scene->camera->camdata.viewport_height)),
			scene->camera->camdata.forward);
	return (ft_ray(scene->camera->position, pixel_dir));
}

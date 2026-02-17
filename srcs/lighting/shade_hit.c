/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:57:47 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/17 14:48:53 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	shade_hit(t_scene *sc, t_hit *hit, t_vec3 point, t_vec3 normal)
{
	t_rgb	color;
	t_rgb	tmp;
	t_rgb	obj_color;
	t_vec3	light_dir;
	t_vec3	view_dir;
	int		i;

	if (hit->type == SPHERE)
		obj_color = ((t_sphere *)hit->object)->color;
	else if (hit->type == PLANE)
		obj_color = ((t_plane *)hit->object)->color;
	else if (hit->type == CYLINDER)
		obj_color = ((t_cylinder *)hit->object)->color;
	else
		obj_color = ((t_triangle *)hit->object)->color;

	color = apply_ambient(sc, obj_color);
	i = 0;
	while (i < sc->light_count)
	{
		if (!is_in_shadow(sc, point, sc->lights[i]))
		{
			light_dir = vec3_normalize(
					vec3_sub(sc->lights[i]->position, point));
			view_dir = vec3_normalize(
					vec3_sub(sc->camera->position, point));

			/* diffuse */
			tmp = apply_diffuse(
				normal,
				light_dir,
				sc->lights[i],
				obj_color
			);
			color = rgb_add(color, tmp);

			/* specular */
			tmp = apply_specular(
				normal,
				light_dir,
				view_dir,
				sc->lights[i],
				50.0
			);
			color = rgb_add(color, tmp);
		}
		i++;
	}
	return (rgb_clamp(color));
}

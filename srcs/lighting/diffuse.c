/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:51:58 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/13 14:58:31 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	apply_diffuse(t_vec3 normal, t_vec3 light_dir,
							t_light *light, t_rgb obj_color)
{
	double	diff;
	t_rgb	res;

	diff = vec3_dot(normal, light_dir);
	if (diff < 0)
		diff = 0;
	res.r = obj_color.r * diff * light->ratio * (light->color.r / 255.0);
	res.g = obj_color.g * diff * light->ratio * (light->color.g / 255.0);
	res.b = obj_color.b * diff * light->ratio * (light->color.b / 255.0);
	return (res);
}

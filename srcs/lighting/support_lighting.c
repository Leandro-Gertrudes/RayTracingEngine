/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:55:04 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/14 14:57:36 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_in_shadow(t_scene *sc, t_vec3 point, t_light *light)
{
	t_ray	shadow;
	t_hit	tmp;
	t_vec3	to_light;
	double	dist;

	to_light = vec3_sub(light->position, point);
	dist = vec3_len(to_light);
	to_light = vec3_normalize(to_light);
	shadow.origin = vec3_add(point, vec3_scale(to_light, 1e-4));
	shadow.direction = to_light;
	if (hit_objects(sc, shadow, &tmp))
	{
		if (tmp.t > 1e-6 && tmp.t < dist)
			return (true);
	}
	return (false);
}

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	t_rgb	c;

	c.r = a.r + b.r;
	c.g = a.g + b.g;
	c.b = a.b + b.b;
	return (c);
}

t_rgb	rgb_clamp(t_rgb c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.g > 255)
		c.g = 255;
	if (c.b > 255)
		c.b = 255;
	if (c.r < 0)
		c.r = 0;
	if (c.g < 0)
		c.g = 0;
	if (c.b < 0)
		c.b = 0;
	return (c);
}

int	rgb_to_int(t_rgb color)
{
	int	r;
	int	g;
	int	b;

	r = (int)color.r;
	g = (int)color.g;
	b = (int)color.b;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return (r << 16 | g << 8 | b);
}

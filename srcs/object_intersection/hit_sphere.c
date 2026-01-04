/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:36:51 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/15 17:33:27 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
typedef struct s_sphere_hit
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sqrt_d;
	double	t0;
	double	t1;
}	t_sphere_hit;
*/

bool	hit_sphere(t_ray ray, t_sphere *sp, double *t)
{
	t_sphere_hit	h;

	h.oc = vec3_sub(ray.origin, sp->center);
	h.a = vec3_dot(ray.direction, ray.direction);
	h.b = 2.0 * vec3_dot(h.oc, ray.direction);
	h.c = vec3_dot(h.oc, h.oc)
		- (sp->diameter / 2) * (sp->diameter / 2);
	h.delta = h.b * h.b - 4 * h.a * h.c;
	if (h.delta < 0)
		return (false);
	h.sqrt_d = sqrt(h.delta);
	h.t0 = (-h.b - h.sqrt_d) / (2 * h.a);
	h.t1 = (-h.b + h.sqrt_d) / (2 * h.a);
	if (h.t0 > 1e-6)
	{
		*t = h.t0;
		return (true);
	}
	if (h.t1 > 1e-6)
	{
		*t = h.t1;
		return (true);
	}
	return (false);
}

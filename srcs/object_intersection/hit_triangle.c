/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:16:04 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/27 19:18:06 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EPSILON 1e-6

t_vec3	triangle_normal(t_triangle *tr)
{
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	n;

	e1 = vec3_sub(tr->b, tr->a);
	e2 = vec3_sub(tr->c, tr->a);
	n = vec3_cross(e1, e2);
	return (vec3_normalize(n));
}


bool	hit_triangle(t_ray ray, t_triangle *tr, double *t)
{
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	h;
	t_vec3	s;
	t_vec3	q;
	double	a;
	double	f;
	double	u;
	double	v;
	double	tmp;

	e1 = vec3_sub(tr->b, tr->a);
	e2 = vec3_sub(tr->c, tr->a);
	h = vec3_cross(ray.direction, e2);
	a = vec3_dot(e1, h);
	if (fabs(a) < EPSILON)
		return (false);
	f = 1.0 / a;
	s = vec3_sub(ray.origin, tr->a);
	u = f * vec3_dot(s, h);
	if (u < 0.0 || u > 1.0)
		return (false);
	q = vec3_cross(s, e1);
	v = f * vec3_dot(ray.direction, q);
	if (v < 0.0 || u + v > 1.0)
		return (false);
	tmp = f * vec3_dot(e2, q);
	if (tmp > EPSILON)
	{
		*t = tmp;
		return (true);
	}
	return (false);
}

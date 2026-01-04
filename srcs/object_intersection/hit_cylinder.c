/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:45:05 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/15 17:52:52 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EPSILON 1e-6
#define INF_VAL 1e30

static bool	cy_lateral(t_ray ray, t_cylinder *cy, double *out);
static bool	cy_cap(t_ray ray, t_cylinder *cy, double *out, int top);

bool	hit_cylinder(t_ray ray, t_cylinder *cy, double *t)
{
	double	t_lateral;
	double	t_top;
	double	t_bottom;
	bool	hit;

	t_lateral = INF_VAL;
	t_top = INF_VAL;
	t_bottom = INF_VAL;
	hit = false;
	if (cy_lateral(ray, cy, &t_lateral))
		hit = true;
	if (cy_cap(ray, cy, &t_top, 1))
		hit = true;
	if (cy_cap(ray, cy, &t_bottom, 0))
		hit = true;
	if (!hit)
		return (false);
	*t = t_lateral;
	if (t_top < *t && t_top > EPSILON)
		*t = t_top;
	if (t_bottom < *t && t_bottom > EPSILON)
		*t = t_bottom;
	return (true);
}

/*
 * caps: top == 1 -> top cap ; top == 0 -> bottom cap
 * assume cy->center is the base (bottom).
 * top center = center + normal*height
 */
static bool	cy_cap(t_ray ray, t_cylinder *cy, double *out, int top)
{
	t_plane	pl;
	t_vec3	center;
	t_vec3	p;
	double	t;

	if (top)
		center = vec3_add(cy->center, vec3_scale(cy->normal, cy->height));
	else
		center = cy->center;
	pl.point = center;
	pl.normal = cy->normal;
	pl.color = (t_rgb){0, 0, 0};
	if (!hit_plane(ray, &pl, &t))
		return (false);
	if (t < EPSILON)
		return (false);
	p = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	if (vec3_len(vec3_sub(p, center)) <= cy->diameter / 2.0)
	{
		*out = t;
		return (true);
	}
	return (false);
}

static bool	cy_lateral_2(t_ray ray, t_cylinder *cy,
		double *out, t_cylinder_hit hit)
{
	hit.t1 = (-hit.b - sqrt(hit.discriminant)) / (2 * hit.a);
	hit.t2 = (-hit.b + sqrt(hit.discriminant)) / (2 * hit.a);
	if (hit.t1 > EPSILON)
	{
		hit.p = vec3_add(ray.origin, vec3_scale(ray.direction, hit.t1));
		hit.h = vec3_dot(vec3_sub(hit.p, cy->center), cy->normal);
		if (hit.h >= 0.0 && hit.h <= cy->height)
		{
			*out = hit.t1;
			return (true);
		}
	}
	if (hit.t2 > EPSILON)
	{
		hit.p = vec3_add(ray.origin, vec3_scale(ray.direction, hit.t2));
		hit.h = vec3_dot(vec3_sub(hit.p, cy->center), cy->normal);
		if (hit.h >= 0.0 && hit.h <= cy->height)
		{
			*out = hit.t2;
			return (true);
		}
	}
	return (false);
}

/*
typedef struct s_cylinder_hit
{
	t_vec3	oc;
	t_vec3	d;
	t_vec3	w;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	t_vec3	p;
	double	h;
}	t_cylinder_hit;*/
static bool	cy_lateral(t_ray ray, t_cylinder *cy, double *out)
{
	t_cylinder_hit	hit;

	hit.oc = vec3_sub(ray.origin, cy->center);
	hit.d = vec3_sub(ray.direction,
			vec3_scale(cy->normal, vec3_dot(ray.direction, cy->normal)));
	hit.w = vec3_sub(hit.oc, vec3_scale(cy->normal,
				vec3_dot(hit.oc, cy->normal)));
	hit.a = vec3_dot(hit.d, hit.d);
	hit.b = 2 * vec3_dot(hit.d, hit.w);
	hit.c = vec3_dot(hit.w, hit.w) - (cy->diameter * cy->diameter) / 4.0;
	hit.discriminant = hit.b * hit.b - 4 * hit.a * hit.c;
	if (hit.discriminant < 0.0 || fabs(hit.a) < EPSILON)
		return (false);
	return (cy_lateral_2(ray, cy, out, hit));
}

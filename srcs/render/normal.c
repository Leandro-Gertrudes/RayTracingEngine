/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:01:14 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/12/30 16:30:27 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// dist_to_base = 0, dist_to_top = 1
static t_vec3	get_cylinder_normal(t_hit *hit, t_vec3 point)
{
	t_cylinder	*cy;
	t_vec3		to_point;
	double		proj;
	t_vec3		point_on_axis;
	double		dist[2];

	cy = (t_cylinder *)hit->object;
	to_point = vec3_sub(point, cy->center);
	proj = vec3_dot(to_point, cy->normal);
	dist[0] = fabs(proj);
	dist[1] = fabs(proj - cy->height);
	if (dist[0] < 1e-4)
		return (vec3_scale(cy->normal, -1.0));
	if (dist[1] < 1e-4)
		return (cy->normal);
	point_on_axis = vec3_add(cy->center, vec3_scale(cy->normal, proj));
	return (vec3_normalize(vec3_sub(point, point_on_axis)));
}

t_vec3	get_normal(t_hit *hit, t_vec3 point)
{
	t_vec3		normal;
	t_sphere	*sp;
	t_plane		*pl;

	if (hit->type == SPHERE)
	{
		sp = (t_sphere *)hit->object;
		normal = vec3_normalize(vec3_sub(point, sp->center));
	}
	else if (hit->type == PLANE)
	{
		pl = (t_plane *)hit->object;
		normal = vec3_normalize(pl->normal);
	}
	else if (hit->type == CYLINDER)
		normal = get_cylinder_normal(hit, point);
	else if (hit->type == TRIANGLE)
		normal = triangle_normal((t_triangle *)hit->object);
	else
		normal = vec3_new(0, 1, 0);
	return (normal);
}

double	get_reflectivity(t_hit *hit)
{		
	if (hit->type == SPHERE)
	{
		return (((t_sphere *)hit->object)->reflectivity);
	}
	if (hit->type == PLANE)
		return (((t_plane *)hit->object)->reflectivity);
	if (hit->type == CYLINDER)
		return (((t_cylinder *)hit->object)->reflectivity);
	if (hit->type == TRIANGLE)
		return (((t_triangle *)hit->object)->reflectivity);
	return (0.0);
}

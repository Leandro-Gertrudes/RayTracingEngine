/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:39:35 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/21 14:33:52 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool hit_light(t_ray ray, t_light *l, double *t)
{
	double	radius = 5.0;
	t_sphere fake;

	fake.center = l->position;
	fake.diameter = radius * 2;
	return (hit_sphere(ray, &fake, t));
}


static void	update_hit(t_hit *hit, double t, t_object *obj, int type)
{
	hit->t = t;
	hit->object = obj->data;
	hit->type = type;
}

static int	is_valid_t(double t, double current)
{
	if (t > 1e-6 && t < current)
		return (1);
	return (0);
}

static void	test_object(t_object *obj, t_ray ray, t_hit *hit)
{
	double	t;

	if (obj->type == SPHERE
		&& hit_sphere(ray, (t_sphere *)obj->data, &t)
		&& is_valid_t(t, hit->t))
		update_hit(hit, t, obj, SPHERE);
	else if (obj->type == PLANE
		&& hit_plane(ray, (t_plane *)obj->data, &t)
		&& is_valid_t(t, hit->t))
		update_hit(hit, t, obj, PLANE);
	else if (obj->type == CYLINDER
		&& hit_cylinder(ray, (t_cylinder *)obj->data, &t)
		&& is_valid_t(t, hit->t))
		update_hit(hit, t, obj, CYLINDER);
	else if (obj->type == TRIANGLE
		&& hit_triangle(ray, (t_triangle *)obj->data, &t)
		&& is_valid_t(t, hit->t))
		update_hit(hit, t, obj, TRIANGLE);
}

bool	hit_objects(t_scene *scene, t_ray ray, t_hit *hit)
{
	int	i;

	hit->t = INFINITY;
	hit->object = NULL;
	hit->type = INVALID;
	i = 0;
	
	while (i < scene->object_count)
	{
		test_object(scene->objects[i], ray, hit);
		i++;
	}
	return (hit->object != NULL);
}

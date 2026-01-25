/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:30:44 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/24 16:59:49 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief TIRAR TERNARIO.
/// @param cy 
/// @param keycode 
static void	scale_cylinder(t_cylinder *cy, int keycode)
{
	double s;

	if (keycode == 106 || keycode == 107)
	{
		s = (keycode == 107)
			? 1.0 * g_scale_edit
			: -1.0 * g_scale_edit;

		cy->diameter += s;
		if (cy->diameter < 0.01)
			cy->diameter = 0.01;
	}
	else
	{
		s = (keycode == 109)
			?  1 * g_scale_edit
			: -1 - g_scale_edit;

		cy->height += s;
		if (cy->height < 0.01)
			cy->height = 0.01;
	}
}


void scale_triangle(t_triangle *tr, int keycode)
{
	double s;
	t_vec3 center;

	if (keycode == 107)
		s = 1.0 + g_scale_edit;
	else if (keycode == 106)
		s = 1.0 - g_scale_edit;
	else
		return ;

	if (s <= 0.01)
		return ;

	center = (t_vec3){
		(tr->a.x + tr->b.x + tr->c.x) / 3.0,
		(tr->a.y + tr->b.y + tr->c.y) / 3.0,
		(tr->a.z + tr->b.z + tr->c.z) / 3.0
	};

	tr->a = vec3_add(center,
		vec3_scale(vec3_sub(tr->a, center), s));
	tr->b = vec3_add(center,
		vec3_scale(vec3_sub(tr->b, center), s));
	tr->c = vec3_add(center,
		vec3_scale(vec3_sub(tr->c, center), s));
}


void	size_obj(t_scene *scene, t_object *obj_edit, int keycode)
{
	if (obj_edit->type == SPHERE)
	{
		t_sphere *sp = obj_edit->data;
		if (keycode == 106)
			sp->diameter *= (1.0 - g_scale_edit);
		else
			sp->diameter *= (1.0 + g_scale_edit);

		if (sp->diameter < 0.01)
			sp->diameter = 0.01;
	}
	else if (obj_edit->type == CYLINDER)
		scale_cylinder(obj_edit->data, keycode);
	else if (obj_edit->type == TRIANGLE)
		scale_triangle((t_triangle *)obj_edit->data, keycode);
	else if (obj_edit->type == LIGHT)
	{
		t_light *l = obj_edit->data;
		if (keycode == 106)
			l->ratio -= g_scale_edit;
		else
			l->ratio +=  g_scale_edit;

		if (l->ratio < 0.01)
			l->ratio = 0.01;
	}

	low_render_scene(scene);
	draw_hud_obj(scene, obj_edit->type, obj_edit->data);
}


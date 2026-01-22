/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angule_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:47:12 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/22 11:55:09 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	triangle_center(t_triangle *tr)
{
	return ((t_vec3){
		(tr->a.x + tr->b.x + tr->c.x) / 3.0,
		(tr->a.y + tr->b.y + tr->c.y) / 3.0,
		(tr->a.z + tr->b.z + tr->c.z) / 3.0
	});
}


static t_vec3	rotate_vec3_xyz(t_vec3 v, t_vec3 rot)
{
	t_vec3 r = v;

	// X
	if (rot.x != 0)
	{
		double c = cos(rot.x);
		double s = sin(rot.x);
		r = (t_vec3){r.x, r.y * c - r.z * s, r.y * s + r.z * c};
	}
	// Y
	if (rot.y != 0)
	{
		double c = cos(rot.y);
		double s = sin(rot.y);
		r = (t_vec3){r.x * c + r.z * s, r.y, -r.x * s + r.z * c};
	}
	// Z
	if (rot.z != 0)
	{
		double c = cos(rot.z);
		double s = sin(rot.z);
		r = (t_vec3){r.x * c - r.y * s, r.x * s + r.y * c, r.z};
	}
	return (r);
}


void	move_obj_angule(t_scene *scene, t_object *obj_edit, int keycode)
{
	t_vec3 rot = (t_vec3){0, 0, 0};

	// igual câmera
	if (keycode == 65364) rot.x -= g_scale_edit; // → 
	if (keycode == 65362) rot.x += g_scale_edit; // ← 
	if (keycode == 65363) rot.y += g_scale_edit; // ↑
	if (keycode == 65361) rot.y -= g_scale_edit; // ↓ 
	if (keycode == 99)   rot.z += g_scale_edit; // z 
	if (keycode == 122)    rot.z -= g_scale_edit; // c 

	if (obj_edit->type == PLANE)
	{
		t_plane *pl = obj_edit->data;
		pl->normal = rotate_vec3_xyz(pl->normal, rot);
		pl->normal = vec3_normalize(pl->normal);
	}
	else if (obj_edit->type == CYLINDER)
	{
		t_cylinder *cy = obj_edit->data;
		cy->normal = rotate_vec3_xyz(cy->normal, rot);
		cy->normal = vec3_normalize(cy->normal);
	}
	else if (obj_edit->type == TRIANGLE)
	{
		t_triangle *tr = obj_edit->data;
		t_vec3 center = triangle_center(tr);

		tr->a = vec3_add(center,
			rotate_vec3_xyz(vec3_sub(tr->a, center), rot));
		tr->b = vec3_add(center,
			rotate_vec3_xyz(vec3_sub(tr->b, center), rot));
		tr->c = vec3_add(center,
			rotate_vec3_xyz(vec3_sub(tr->c, center), rot));
	}

	low_render_scene(scene);
	draw_hud_obj(scene, obj_edit->type, obj_edit->data);
}

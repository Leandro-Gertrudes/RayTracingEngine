/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:19:54 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/16 16:35:10 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_move_delta(int keycode, double *dx, double *dy)
{

	*dx = 0;
	*dy = 0;

	if (keycode == KEY_W)
		*dy = g_scale_edit;
	else if (keycode == KEY_S)
		*dy = -g_scale_edit;
	else if (keycode == KEY_D)
		*dx = -g_scale_edit;
	else if (keycode == KEY_A)
		*dx = g_scale_edit;
}

static void zero_between_one(double *num)
{
	if(*num > 1.0)
		*num = 1.0;
	else if (*num < 0.0)
		*num = 0.0;
}

void reflectivity_update(t_scene *scene, t_object *obj_edit, int keycode)
{
	double new;

	new = 0.0;

	if(keycode == KEY_O)
		new += g_scale_edit;
	else if (keycode == KEY_I)
		new -= g_scale_edit;

	if (obj_edit->type == SPHERE)
	{
		t_sphere *sp = obj_edit->data;
		sp->reflectivity += new;
		zero_between_one(&sp->reflectivity);
	}
	else if (obj_edit->type == PLANE)
	{
		t_plane *pl = obj_edit->data;
		pl->reflectivity += new;
		zero_between_one(&pl->reflectivity);
	}
	else if (obj_edit->type == CYLINDER)
	{
		t_cylinder *cy = obj_edit->data;
		cy->reflectivity += new;
		if(cy->reflectivity < 0)
			cy->reflectivity = 0;
		zero_between_one(&cy->reflectivity);
	}
	else if (obj_edit->type == TRIANGLE)
	{
		t_triangle *tr = obj_edit->data;
		tr->reflectivity += new;
		if(tr->reflectivity < 0)
			tr->reflectivity = 0;
		zero_between_one(&tr->reflectivity);
	}
	low_render_scene(scene);
	draw_hud_obj(scene, obj_edit->type, obj_edit->data);
}

void	move_obj_xy(t_scene *scene, t_object *obj_edit, int keycode)
{
	double dx;
	double dy;

	get_move_delta(keycode, &dx, &dy);

	if (dx == 0 && dy == 0)
		return ;

	if (obj_edit->type == SPHERE)
	{
		t_sphere *sp = obj_edit->data;
		sp->center.x += dx;
		sp->center.y += dy;
	}
	else if (obj_edit->type == PLANE)
	{
		t_plane *pl = obj_edit->data;
		pl->point.x += dx;
		pl->point.y += dy;
	}
	else if (obj_edit->type == CYLINDER)
	{
		t_cylinder *cy = obj_edit->data;
		cy->center.x += dx;
		cy->center.y += dy;
	}
	else if (obj_edit->type == TRIANGLE)
	{
		t_triangle *tr = obj_edit->data;

		tr->a.x += dx;
		tr->a.y += dy;
		tr->b.x += dx;
		tr->b.y += dy;
		tr->c.x += dx;
		tr->c.y += dy;
	}
	else if (obj_edit->type == LIGHT)
	{
		t_light *l = obj_edit->data;

		l->position.x += dx;
		l->position.y += dy;
	}

	low_render_scene(scene);
	draw_hud_obj(scene, obj_edit->type, obj_edit->data);
}

void	move_obj_z(t_scene *scene, t_object *obj_edit, int button)
{
	double dz = g_scale_edit;

	if (button == 5)
		dz = -dz;

	if (obj_edit->type == SPHERE)
	{
		t_sphere *sp = obj_edit->data;
		sp->center.z += dz;
	}
	else if (obj_edit->type == PLANE)
	{
		t_plane *pl = obj_edit->data;
		pl->point.z += dz;
	}
	else if (obj_edit->type == CYLINDER)
	{
		t_cylinder *cy = obj_edit->data;
		cy->center.z += dz;
	}
	else if (obj_edit->type == TRIANGLE)
	{
		t_triangle *tr = obj_edit->data;

		tr->a.z += dz;
		tr->b.z += dz;
		tr->c.z += dz;
	}
	else if (obj_edit->type == LIGHT)
	{
		t_light *l = obj_edit->data;

		l->position.z += dz;
	}
	

	low_render_scene(scene);
	draw_hud_obj(scene, obj_edit->type, obj_edit->data);
}

void update_move(int keycode)
{
	if(keycode == KEY_PLUS)
		g_scale_edit += 0.2;
	if(keycode == KEY_MINUS)
		g_scale_edit -= 0.2;
		
	if(g_scale_edit <= 0.1)
		g_scale_edit = 0.1;
	if (g_scale_edit >= 1000000.0)
		g_scale_edit = 1000000.0;
}
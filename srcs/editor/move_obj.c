/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:19:54 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/21 17:48:46 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_move_delta(int keycode, double *dx, double *dy)
{

	*dx = 0;
	*dy = 0;

	if (keycode == 119)
		*dy = g_move;
	else if (keycode == 115)
		*dy = -g_move;
	else if (keycode == 100)
		*dx = -g_move;
	else if (keycode == 97)
		*dx = g_move;
}


void	move_obj(t_scene *scene, t_object *obj_edit, int keycode)
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

	low_render_scene(scene);
	draw_hud_obj(scene, obj_edit->type, obj_edit->data);
}
void update_move(int keycode)
{
	if(keycode == 61)
		g_move += 0.2;
	if(keycode == 45)
		g_move -= 0.2;
		
	if(g_move <= 0.1)
		g_move = 0.1;
	if (g_move >= 1000000.0)
		g_move = 1000000.0;
}
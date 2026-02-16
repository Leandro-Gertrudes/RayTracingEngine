/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:25:06 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/16 16:31:06 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	find_light_index(t_scene *scene, t_light *light)
{
	int	i;

	if (!light)
		return (-1);

	for (i = 0; i < scene->light_count; i++)
	{
		if (scene->lights[i] == light)
			return (i);
	}
	return (-1);
}


void	select_light(t_scene *scene, int keycode)
{
	int	cur;
	int	next;

	if (!scene || scene->light_count == 0)
		return;

	if(keycode == KEY_P)
		return (position_light(scene));

	if (scene->light_count == 1)
		return;

	cur = find_light_index(scene, g_low_light);

	if (cur == -1)
	{
		g_low_light = scene->lights[0];
		return;
	}

	if (keycode == 91)          // [
		next = cur - 1;
	else                        // ]
		next = cur + 1;

	if (next < 0)
		next = scene->light_count - 1;
	else if (next >= scene->light_count)
		next = 0;

	g_low_light = scene->lights[next];
	scene->obj_edit.data = scene->lights[next];
	low_render_scene(scene);
	draw_hud_obj(scene, scene->obj_edit.type, scene->obj_edit.data);
}

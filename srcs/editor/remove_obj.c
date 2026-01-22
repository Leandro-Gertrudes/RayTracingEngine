/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:03:57 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/22 16:16:59 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_object(t_object *obj)
{
	if (!obj)
		return ;

	if (obj->data)
		free(obj->data);

	free(obj);
}


void	remove_object_at(t_scene *scene, int index)
{
	int	i;

	if (index < 0 || index >= scene->object_count)
		return ;

	free_object(scene->objects[index]);

	i = index;
	while (i < scene->object_count - 1)
	{
		scene->objects[i] = scene->objects[i + 1];
		i++;
	}

	scene->object_count--;

	if (scene->object_count == 0)
	{
		free(scene->objects);
		scene->objects = NULL;
	}
}


int	find_object_index(t_scene *scene, t_object *obj)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i] == obj)
			return (i);
		i++;
	}
	return (-1);
}


void remove_obj(t_scene *scene)
{
	int index;
	
	if (!g_edit)
		return ;

	index = find_object_index(scene, scene->obj_edit);
	if (index == -1)
		return ;
	remove_object_at(scene, index);

	g_edit = false;

	low_render_scene(scene);
	draw_hud(scene);
	
}

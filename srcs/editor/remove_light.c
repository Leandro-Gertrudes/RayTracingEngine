/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:59:01 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/23 13:05:36 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_light_index(t_scene *scene, t_light *li)
{
	int	i = 0;

	while (i < scene->light_count)
	{
		if (scene->lights[i] == li)
			return (i);
		i++;
	}
	return (-1);
}


void	remove_light_at(t_scene *scene, int index)
{
	int	i;

	if (index < 0 || index >= scene->light_count)
		return ;

	free(scene->lights[index]);

	i = index;
	while (i < scene->light_count - 1)
	{
		scene->lights[i] = scene->lights[i + 1];
		i++;
	}

	scene->light_count--;

	if (scene->light_count == 0)
	{
		free(scene->lights);
		scene->lights = NULL;
	}
}


void	remove_light(t_scene *scene)
{
	int	index;

	if (!g_edit_light)
		return ;

	index = find_light_index(scene, scene->obj_edit.data);
	if (index == -1)
		return ;

	remove_light_at(scene, index);

	g_edit = false;

	low_render_scene(scene);
	draw_hud(scene);
}

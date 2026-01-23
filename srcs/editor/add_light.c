/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:54:59 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/23 11:55:45 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_spawn_position(t_camera *cam, double dist);

t_light	*create_light(t_camera *cam)
{
	t_light *li;

	li = malloc(sizeof(t_light));
	if (!li)
		return (NULL);

	li->position = get_spawn_position(cam, 3.0);
	li->color = (t_rgb){255, 255, 255};
	li->ratio = 1.0;

	return (li);
}

void	add_light_to_scene(t_scene *scene, t_light *new_light)
{
	t_light **tmp;

	tmp = realloc(scene->lights,
		sizeof(t_light *) * (scene->light_count + 1));
	if (!tmp)
	{
		ft_putendl_fd("Failed to allocate memory for new light", 2);
		return ;
	}
	scene->lights = tmp;
	scene->lights[scene->light_count] = new_light;
	scene->light_count++;
}

void	add_light(t_scene *scene)
{
	t_light *li;

	li = create_light(scene->camera);
	if (!li)
		return ;

	add_light_to_scene(scene, li);

	scene->obj_edit.type = LIGHT;
	scene->obj_edit.data = li;
	g_edit = true;
	g_edit_light = true;

	low_render_scene(scene);
	draw_hud_obj(scene, LIGHT, li);
}
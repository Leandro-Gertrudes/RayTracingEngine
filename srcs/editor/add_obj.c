/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:34:27 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/16 14:28:50 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_spawn_position(t_camera *cam, double dist)
{
	return vec3_add(cam->position, vec3_scale(cam->camdata.forward, dist));
}


t_object	*create_sphere(t_camera *cam)
{
	t_object	*obj = malloc(sizeof(t_object));
	t_sphere	*sp = malloc(sizeof(t_sphere));

	sp->center = get_spawn_position(cam, 3.0); 
	sp->diameter = 1.0;
	sp->color = (t_rgb){255, 255, 255};
	sp->reflectivity = 0.2;

	obj->type = SPHERE;
	obj->data = sp;
	return obj;
}

t_object	*create_plane(t_camera *cam)
{
	t_object	*obj = malloc(sizeof(t_object));
	t_plane		*pl = malloc(sizeof(t_plane));

	pl->point = get_spawn_position(cam, 3.0);
	pl->normal = (t_vec3){0, 1, 0};
	pl->color = (t_rgb){200, 200, 200};
	pl->reflectivity = 0.0;

	obj->type = PLANE;
	obj->data = pl;
	return obj;
}

t_object	*create_cylinder(t_camera *cam)
{
	t_object	*obj = malloc(sizeof(t_object));
	t_cylinder	*cy = malloc(sizeof(t_cylinder));

	cy->center = get_spawn_position(cam, 3.0);
	cy->normal = (t_vec3){0, 1, 0};
	cy->diameter = 1.0;
	cy->height = 2.0;
	cy->color = (t_rgb){255, 255, 255};
	cy->reflectivity = 0.2;

	obj->type = CYLINDER;
	obj->data = cy;
	return obj;
}

t_object	*create_triangle(t_camera *cam)
{
	t_object	*obj = malloc(sizeof(t_object));
	t_triangle	*tr = malloc(sizeof(t_triangle));
	t_vec3		pos = get_spawn_position(cam, 3.0);

	tr->a = pos;
	tr->b = vec3_add(pos, (t_vec3){1, 0, 0});
	tr->c = vec3_add(pos, (t_vec3){0, 1, 0});
	tr->color = (t_rgb){255, 255, 255};
	tr->reflectivity = 0.2;

	obj->type = TRIANGLE;
	obj->data = tr;
	return obj;
}

void	add_object_to_scene(t_scene *scene, t_object *new_obj)
{
	t_object	**tmp;

	tmp = realloc(scene->objects, sizeof(t_object*) * (scene->object_count + 1));
	if (!tmp)
	{
		ft_putendl_fd("Failed to allocate memory for new object", 2);
		return;
	}
	scene->objects = tmp;
	scene->objects[scene->object_count] = new_obj;
	scene->object_count++;
}

void	add_object(t_scene *scene, int keycode)
{
	t_object	*obj = NULL;

	if (keycode == 49)  
		obj = create_sphere(scene->camera);
	else if (keycode == 52)
		obj = create_plane(scene->camera);
	else if (keycode == 50)
		obj = create_cylinder(scene->camera);
	else if (keycode == 51)
		obj = create_triangle(scene->camera);
	else if (keycode == 53)
		return (add_light(scene));
	else
		return ;

	if (!obj)
		return ;

	add_object_to_scene(scene, obj);

	scene->obj_edit.type = obj->type;
	scene->obj_edit.data = obj;

	low_render_scene(scene);
	draw_hud_obj(scene, obj->type, obj->data);
}

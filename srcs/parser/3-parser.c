/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:38:39 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/25 16:50:34 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*ft_parser(t_args *args)
{
	t_scene	*scene;

	scene = ft_calloc(sizeof(t_scene), 1);
	scene->light_count = args->light_count;
	scene->object_count = args->obj_count;
	scene->ambient = ft_parser_al(args->ambient_light);
	scene->camera = ft_parser_c(args->camera);
	scene->lights = ft_parser_l(args->light, scene->light_count);
	scene->objects = ft_parser_ob(args->objects, scene->object_count);
	if (scene->ambient == NULL || scene->camera == NULL
		|| (scene->light_count > 0 && scene->lights == NULL)
		|| (scene->objects == NULL))
	{
		ft_free_args(args);
		ft_free_scene(scene);
		ft_exit(ERROR_SCENE, 2);
	}
	scene->camera->camdata = ft_compute_camera(*scene->camera, WIDTH, HEIGHT);
	//init_anim_light(scene);
	//init_anim_camera(scene);
	scene->image = image_create(WIDTH, HEIGHT);
	return (scene);
}

// 1 - count parts to verified if have 3 arguments.
// 2 - if with 3 condictions:
//		first argument is 'A'.
//			parser ratio, if arguments is a float 0.0 - 1.0.
//				parser RGB xxx,xxx,xxx.
// 3 - strdup and get rgb for allocate arguments.
t_ambient_light	*ft_parser_al(char *input)
{
	t_ambient_light	*al;
	char			**args;

	if (count_parts(input, ' ') != 3)
		return (NULL);
	args = ft_split(input, ' ');
	if (ft_strncmp(args[0], "A", ft_strlen(args[0])) != 0
		|| !ft_parser_ratio(args[1], 0.0, 1.0)
		|| !ft_parser_rgb(args[2]))
	{
		ft_free_split(args);
		return (NULL);
	}
	al = ft_calloc(sizeof(t_ambient_light), 1);
	al->ratio = ft_atod(args[1]);
	al->color = ft_get_rgb(args[2]);
	ft_free_split(args);
	return (al);
}

t_camera	*ft_parser_c(char *input)
{
	t_camera	*camera;
	char		**args;

	if (count_parts(input, ' ') != 4)
		return (NULL);
	args = ft_split(input, ' ');
	if (ft_strncmp(args[0], "C", ft_strlen(args[0])) != 0
		|| !ft_parser_vec3(args[1])
		|| !ft_is_normalized(args[2])
		|| !ft_parse_fov(args[3]))
	{
		ft_free_split(args);
		return (NULL);
	}
	camera = ft_calloc(sizeof(t_camera), 1);
	camera->position = ft_get_vec3(args[1]);
	camera->vector = ft_get_vec3(args[2]);
	camera->fov = ft_atod(args[3]);
	ft_free_split(args);
	return (camera);
}

t_object	**ft_parser_ob(char **input, int count_objects)
{
	t_object	**objects;
	int			i;

	if (!input || count_objects <= 0)
		return (NULL);
	objects = (t_object **)ft_alloc_arraystruc(count_objects, sizeof(t_object));
	if (!objects)
		return (NULL);
	i = 0;
	while (i < count_objects)
	{
		if (!input[i])
			break ;
		objects[i]->type = ft_get_type(input[i]);
		if (objects[i]->type == INVALID)
			return (ft_free_objects_struc(objects, count_objects), NULL);
		objects[i]->data = ft_get_obj(objects[i]->type, input[i]);
		if (objects[i]->data == NULL)
			return (ft_free_objects_struc(objects, count_objects), NULL);
		i++;
	}
	return (objects);
}

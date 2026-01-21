/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:21:50 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/21 14:23:53 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_camera_xyz(t_scene *scene, int keycode);
static void	move_camera_vector(t_scene *scene, int keycode);

int	move_camera(t_scene *scene, int keycode)
{
	if (keycode == 119 || keycode == 115 || keycode == 97
			|| keycode == 100 || keycode == 113 || keycode == 101)
	{
		move_camera_xyz(scene, keycode);
		return (1);
	}
	 else if (keycode == 65361 || keycode == 65363 || keycode == 65362
	 		|| keycode == 65364 || keycode == 122 || keycode == 99)
	{
		move_camera_vector(scene, keycode);
		return (1);
	}
	return (0);
}


static void	move_camera_xyz(t_scene *scene, int keycode)
{
	double speed = 0.3;
	t_camera *cam = scene->camera;

	if (keycode == 119)
		cam->position = vec3_add(cam->position,
			vec3_scale(cam->camdata.forward, speed));
	if (keycode == 115)
		cam->position = vec3_sub(cam->position,
			vec3_scale(cam->camdata.forward, speed));
	if (keycode == 97)
		cam->position = vec3_sub(cam->position,
			vec3_scale(cam->camdata.right, speed));
	if (keycode == 100)
		cam->position = vec3_add(cam->position,
			vec3_scale(cam->camdata.right, speed));
	if (keycode == 113)
		cam->position.y += speed;
	if (keycode == 101)
		cam->position.y -= speed;
	low_render_scene(scene);
}

static void	move_camera_vector(t_scene *scene, int keycode)
{
	double speed = 0.05;
	t_camera *cam = scene->camera;

	if (keycode == 65363) //left
		cam->vector.x -= speed;
	else if (keycode == 65361) // right
		cam->vector.x += speed;

	if (keycode == 65362) //up 
		cam->vector.y += speed;
	else if (keycode == 65364) //down
		cam->vector.y -= speed;

	if (keycode == 122)
		cam->vector.z += speed; //rotate left
	else if (keycode == 99) 
		cam->vector.z -= speed; // rotate right

	cam->vector = vec3_normalize(cam->vector);
	cam->camdata = ft_compute_camera(*cam, WIDTH, HEIGHT);
	low_render_scene(scene);
}
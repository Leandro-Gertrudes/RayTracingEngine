/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:21:50 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/16 16:30:19 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_camera_xyz(t_scene *scene, int keycode);
static void	move_camera_vector(t_scene *scene, int keycode);

int	move_camera(t_scene *scene, int keycode)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
			|| keycode == KEY_D || keycode == KEY_Q || keycode == KEY_E)
	{
		move_camera_xyz(scene, keycode);
		return (1);
	}
	 else if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_UP
	 		|| keycode == KEY_DOWN || keycode == KEY_Z || keycode == KEY_C)
	{
		move_camera_vector(scene, keycode);
		return (1);
	}
	return (0);
}


static void	move_camera_xyz(t_scene *scene, int keycode)
{
	double		speed = 0.3;
	t_camera	*cam = scene->camera;

	if (keycode == KEY_W)
		cam->position = vec3_add(cam->position,
			vec3_scale(cam->camdata.forward, speed));
	if (keycode == KEY_S)
		cam->position = vec3_sub(cam->position,
			vec3_scale(cam->camdata.forward, speed));
	if (keycode == KEY_A)
		cam->position = vec3_sub(cam->position,
			vec3_scale(cam->camdata.right, speed));
	if (keycode == KEY_D)
		cam->position = vec3_add(cam->position,
			vec3_scale(cam->camdata.right, speed));
	if (keycode == KEY_Q)
		cam->position.y += speed;
	if (keycode == KEY_E)
		cam->position.y -= speed;
	low_render_scene(scene);
}

static void	move_camera_vector(t_scene *scene, int keycode)
{
	double		speed = 0.05;
	t_camera	*cam = scene->camera;

	if (keycode == KEY_RIGHT) //left
		cam->vector.x -= speed;
	else if (keycode == KEY_LEFT) // right
		cam->vector.x += speed;

	if (keycode == KEY_UP) //up 
		cam->vector.y += speed;
	else if (keycode == KEY_DOWN) //down
		cam->vector.y -= speed;

	if (keycode == KEY_Z)
		cam->vector.z += speed; //rotate left
	else if (keycode == KEY_C) 
		cam->vector.z -= speed; // rotate right

	cam->vector = vec3_normalize(cam->vector);
	cam->camdata = ft_compute_camera(*cam, WIDTH, HEIGHT);
	low_render_scene(scene);
}
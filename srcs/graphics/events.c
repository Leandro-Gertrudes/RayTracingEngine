/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:42:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2026/01/20 17:05:22 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	move_camera_xyz(t_scene *scene, int keycode);
static void	move_camera_vector(t_scene *scene, int keycode);

int	close_window(t_scene *scene)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;

	if (!scene)
		exit(0);
	mlx_ptr = scene->disp.mlx;
	win_ptr = scene->disp.win;
	img_ptr = scene->disp.img;
	if (img_ptr && mlx_ptr)
		mlx_destroy_image(mlx_ptr, img_ptr);
	if (win_ptr && mlx_ptr)
		mlx_destroy_window(mlx_ptr, win_ptr);
	ft_free_scene(scene);
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
	exit(0);
	return (0);
}

int	key_press(int keycode, t_scene *scene)
{
	if (keycode == 65307) // ESC
		return (close_window(scene));

	if (keycode == 32) // SPACE
	{
		low_render = !low_render;
		
		if (low_render)
			low_render_scene(scene);
		else
			render_transition(scene);
	}
	if(low_render)
		move_camera(scene, keycode);
	return (0);
}

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


void	move_camera_xyz(t_scene *scene, int keycode)
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

void	move_camera_vector(t_scene *scene, int keycode)
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

int	mouse_hook(int button,int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;

	if (!low_render)
		return (0);

	if (button == 4) // scroll up
		scene->camera->fov -= 2;
	if (button == 5) // scroll down
		scene->camera->fov += 2;

	if (scene->camera->fov < 20)
		scene->camera->fov = 20;
	if (scene->camera->fov > 120)
		scene->camera->fov = 120;

	scene->camera->camdata =
		ft_compute_camera(*scene->camera, WIDTH, HEIGHT);

	low_render_scene(scene);
	draw_hud(scene);
	return (0);
}

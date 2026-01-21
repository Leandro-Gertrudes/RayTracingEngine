/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:42:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2026/01/21 17:46:46 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (keycode == 113 && g_edit)
	{
		draw_hud(scene);
		g_edit = false;
		return (0);
	}
	if (g_edit && (keycode == 61 || keycode == 45))
	{
		update_move(keycode);
		draw_hud_obj(scene, scene->obj_edit.type, scene->obj_edit.data);
	}
	if(low_render && !g_edit)
		move_camera(scene, keycode);
	if(low_render && g_edit)
	 	move_obj(scene, &scene->obj_edit, keycode);
	return (0);
}


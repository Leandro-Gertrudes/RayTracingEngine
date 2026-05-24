/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:42:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2026/05/24 15:12:53 by lgertrud         ###   ########.fr       */
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
int	key_press(int keycode, void *param)
{
	t_scene	*scene = (t_scene *)param;
	if (keycode == KEY_ESQ)
		return (close_window(scene));

	if(keycode == KEY_F1)
	{
		mlx_destroy_image(scene->disp.mlx, scene->disp.img);
		mlx_destroy_window(scene->disp.mlx, scene->disp.win);
		mlx_loop_end(scene->disp.mlx);
		mlx_destroy_display(scene->disp.mlx);
		free(scene->disp.mlx);
		ft_free_scene(scene);
		menu();
	}
	
	if(g_edit_color)
		return (0);
	if(keycode == KEY_TAB)
		save_scene(scene);
	if(keycode == KEY_CAPSLOCK)
	{
		screenshots(scene);
	}
	if (keycode == KEY_SPACE)
	{
		low_render = !low_render;
		
		if (low_render)
		{
			if(scene->light_count > 0)
				g_low_light = scene->lights[0];
			low_render_scene(scene);
		}
		else
		{
			g_edit = false;
			g_edit_color = false;
			render_transition(scene);
		}
		return (0);
	}
	
	if (keycode == KEY_Q && g_edit)
	{
		draw_hud(scene);
		g_edit = false;
		return (0);
	}
	if (g_edit && (keycode == KEY_PLUS || keycode == KEY_MINUS))
	{
		update_move(keycode);
		draw_hud_obj(scene, scene->obj_edit.type, scene->obj_edit.data);
	}
	if (low_render && keycode == KEY_LEFT_SHIFT)
	{
		g_edit_light = !g_edit_light;
		low_render_scene(scene);
		return (0);
	}

	if(low_render && !g_edit)
		move_camera(scene, keycode);
		
	if(low_render && g_edit)
	 	edit_obj(scene, &scene->obj_edit, keycode);
		
	if(low_render && !g_edit)
		add_object(scene, keycode);

	return (0);
}


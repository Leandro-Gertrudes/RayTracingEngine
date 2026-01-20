/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:42:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2026/01/18 17:53:36 by lgertrud         ###   ########.fr       */
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

		// Tela preta
		t_rgb black = {0,0,0};
		for (int y = 0; y < HEIGHT; y++)
			for (int x = 0; x < WIDTH; x++)
				put_pixel(scene, x, y, rgb_to_int(black));

		// Atualiza a janela antes do render
		mlx_put_image_to_window(scene->disp.mlx, scene->disp.win,
			scene->disp.img, 0, 0);

		// Loading
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			WIDTH / 2 - 60, HEIGHT / 2,
			0xFFFFFF, "Loading...");
		mlx_do_sync(scene->disp.mlx);

		// Render
		if (low_render)
		{
			low_render_scene(scene);
			draw_hud(scene);
		}
		else
		{
			render_scene(scene);
		}
}

	return (0);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:33:59 by ghenriqu          #+#    #+#             */
/*   Updated: 2026/01/20 13:25:02 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void draw_hud(t_scene *scene)
{
	int x, y, w, h;
	int alpha = 150;
	t_rgb color;
	char buf[128];

	x = 10;
	y = 10;
	w = 250;
	h = 80;
	for (int j = y; j < y + h; j++)
	{
		for (int i = x; i < x + w; i++)
		{
			t_rgb old = scene->image->pixels[j * scene->image->width + i];

			color.r = (old.r * (255 - alpha)) / 255;
			color.g = (old.g * (255 - alpha)) / 255;
			color.b = (old.b * (255 - alpha)) / 255;

			scene->image->pixels[j * scene->image->width + i] = color;
		}
	}

	mlx_put_image_to_window(scene->disp.mlx, scene->disp.win,
		scene->disp.img, 0, 0);

	int line_y = y + 5;
	snprintf(buf, sizeof(buf), "Mode: PREVIEW");
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf);
	line_y += 20;

	snprintf(buf, sizeof(buf), "Camera: (%.2f, %.2f, %.2f)",
		scene->camera->position.x, scene->camera->position.y, scene->camera->position.z);
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf);
	line_y += 20;

	snprintf(buf, sizeof(buf), "Objects: %d", scene->object_count);
	mlx_string_put(scene->disp.mlx, scene->disp.win, x + 10, line_y, 0xFFFFFF, buf);
}




static void	ft_mlx_destroy_all(t_scene *scene)
{
	if (scene->disp.img)
		mlx_destroy_image(scene->disp.mlx, scene->disp.img);
	if (scene->disp.win)
		mlx_destroy_window(scene->disp.mlx, scene->disp.win);
	if (scene->disp.mlx)
	{
		mlx_destroy_display(scene->disp.mlx);
		free(scene->disp.mlx);
	}
}

static void	ft_mlx_fatal(t_scene *scene, char *msg)
{
	ft_mlx_destroy_all(scene);
	ft_free_scene(scene);
	ft_exit(msg, 1);
}

void	ft_init_graphics(t_scene *scene)
{
	scene->disp.width = WIDTH;
	scene->disp.height = HEIGHT;
	scene->disp.mlx = mlx_init();
	if (!scene->disp.mlx)
		ft_mlx_fatal(scene, "Error: MLX initialization failed");
	scene->disp.win = mlx_new_window(scene->disp.mlx, WIDTH, HEIGHT, "miniRT");
	if (!scene->disp.win)
		ft_mlx_fatal(scene, "Error: Window creation failed");
	scene->disp.img = mlx_new_image(scene->disp.mlx, WIDTH, HEIGHT);
	if (!scene->disp.img)
		ft_mlx_fatal(scene, "Error: Image creation failed");
	scene->disp.addr = mlx_get_data_addr(scene->disp.img,
			&scene->disp.bpp,
			&scene->disp.line_length,
			&scene->disp.endian);
	if (!scene->disp.addr)
		ft_mlx_fatal(scene, "Error: Image address failed");
}

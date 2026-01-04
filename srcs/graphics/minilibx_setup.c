/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:33:59 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/12/14 20:08:37 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

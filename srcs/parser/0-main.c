/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:44:29 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/04 17:06:37 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	main(int argc, char **argv)
// {
// 	t_scene	*scene;

// 	if (argc != 2 || ft_is_rt(argv[1]))
// 		ft_exit(ERROR_PARAM, 1);
// 	scene = ft_get_scene(argv[1]);
// 	if (!scene)
// 		ft_exit("Error: Failed to parse scene", 1);
// 	ft_init_graphics(scene);
// 	mlx_string_put(scene->disp.mlx, scene->disp.win,
// 		WIDTH / 2 - 60, HEIGHT / 2,
// 		0xFFFFFF, "Loading...");
// 	mlx_do_sync(scene->disp.mlx);
// 	render_scene(scene);
// 	mlx_hook(scene->disp.win, 2, 1l << 0, key_press, scene);
// 	mlx_hook(scene->disp.win, 17, 1L << 17, close_window, scene);
// 	//mlx_loop_hook(scene->disp.mlx, render_loop, scene);
// 	mlx_loop(scene->disp.mlx);
// 	return (0);
// }


int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2 || ft_is_rt(argv[1]))
		ft_exit(ERROR_PARAM, 1);
	scene = ft_get_scene(argv[1]);
	render_animation(scene);
	ft_free_scene(scene);
	return (0);
}

void	ft_exit(char *message, int code)
{
	if (message)
		ft_putendl_fd(message, 2);
	exit(code);
}

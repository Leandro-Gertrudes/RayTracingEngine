/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:44:29 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/23 11:00:40 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mode	g_mode;
int		startFrame;
int		endFrame;
bool	low_render = false;
bool	g_edit = false;
bool	g_edit_color = false;
bool	g_edit_light = false;
double	g_scale_edit = 0.3;

int	main(int argc, char **argv)
{
    if (argc < 2 || argc > 5 || ft_is_rt(argv[1]))
		ft_exit(ERROR_PARAM, 1);

    if (argc == 2)
        g_mode = DEFAULT;
    else if (!ft_strcmp(argv[2], "--animate"))
        g_mode = ANIMATE;
    else if (!ft_strcmp(argv[2], "--frames"))
	{
		if(!argv[3] ||  !argv[4] ||
				!ft_is_number(argv[3]) || !ft_is_number(argv[4]))
			ft_exit(ERROR_FRAMES, 1);
        g_mode = SAVE_FRAMES;
		startFrame = atoi(argv[3]);
		endFrame = atoi(argv[4]);
	}
	else
		ft_exit(ERROR_PARAM, 1);
	ft_minirt(argv[1]);
}

void	ft_minirt(char	*file)
{
	t_scene	*scene;

	scene = ft_get_scene(file);
	if (!scene)
		ft_exit("Error: Failed to parse scene", 1);

	if (g_mode == SAVE_FRAMES)
	{
		render_animation(scene);
		ft_free_scene(scene);
		return ;
	}

	ft_init_graphics(scene);
	mlx_string_put(scene->disp.mlx, scene->disp.win,
		WIDTH / 2 - 60, HEIGHT / 2,
		0xFFFFFF, "Loading...");
	mlx_do_sync(scene->disp.mlx);
	render_scene(scene);
	mlx_key_hook(scene->disp.win, key_press, scene);
	mlx_hook(scene->disp.win, 17, 1L << 17, close_window, scene);
	mlx_mouse_hook(scene->disp.win, mouse_hook, scene);
	if(g_mode == ANIMATE)
		mlx_loop_hook(scene->disp.mlx, render_loop, scene);
	mlx_loop(scene->disp.mlx);
}

void	ft_exit(char *message, int code)
{
	if (message)
		ft_putendl_fd(message, 2);
	exit(code);
}

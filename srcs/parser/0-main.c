/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:44:29 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/19 15:48:53 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_demo(void);

#include "minirt.h"

t_mode	g_mode;
int		startFrame;
int		endFrame;
bool	low_render = false;
bool	g_edit = false;
bool	g_edit_color = false;
bool	g_edit_light = false;
t_light	*g_low_light = NULL;
double	g_scale_edit = 0.3;

int	main(int argc, char **argv)
{
	int	i;

	if(argc == 1)
	{
		header();
		menu();
		return (0);
	}

	if (argc == 2 && !ft_strcmp(argv[1], "--help"))
		return(ft_help());

	if (argc == 2 && !ft_strcmp(argv[1], "--commands"))
		return(ft_commands());

	if (argc == 2 && !ft_strcmp(argv[1], "--demo"))
		return(ft_demo());

	if (argc > 6 || ft_is_rt(argv[1]))
	ft_exit(ERROR_PARAM, 1);

	i = 0;
	if (argc > 2 && !ft_strcmp(argv[2], "--lowRender"))
	{
		low_render = true;
		i++;
	}

	if (argc == 2 || (argc == 3 && i == 1))
		g_mode = DEFAULT;
	else if (!ft_strcmp(argv[2 + i], "--animate"))
		g_mode = ANIMATE;
	else if (!ft_strcmp(argv[2 + i], "--frames"))
	{
		if(!argv[3 + i] ||  !argv[4 + i] ||
				!ft_is_number(argv[3 + i]) || !ft_is_number(argv[4 + i]))
			ft_exit(ERROR_FRAMES, 1);
		g_mode = SAVE_FRAMES;
		startFrame = atoi(argv[3 + i]);
		endFrame = atoi(argv[4 + i]);
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
	
	if(!low_render)
		render_scene(scene);
	else
	{
		if(scene->light_count > 0)
			g_low_light = scene->lights[0];
		low_render_scene(scene);
	}
	mlx_key_hook(scene->disp.win, key_press, scene);
	mlx_hook(scene->disp.win, 17, 1L << 17, close_window, scene);
	mlx_mouse_hook(scene->disp.win, mouse_hook, scene);
	if(g_mode == ANIMATE)
		mlx_loop_hook(scene->disp.mlx, render_loop, scene);
	mlx_loop(scene->disp.mlx);
}

int	ft_help(void)
{
		printf("\nminiRT — Mini Ray Tracer (42 Project)\n\n");

	printf("Usage:\n");
	printf("  %-50s %s\n", "./miniRT",
		"Start program with default behavior");
	printf("  %-50s %s\n", "./miniRT <scene.rt>",
		"Render the given scene file");
	printf("  %-50s %s\n", "./miniRT <scene.rt> --lowRender",
		"Render scene with reduced resolution");
	printf("  %-50s %s\n", "./miniRT <scene.rt> --animate",
		"Animate scene in real time");
	printf("  %-50s %s\n",
		"./miniRT <scene.rt> --frames <first> <last>",
		"Render animation and save frames to ./frames");
	printf("  %-50s %s\n",
		"./miniRT --commands",
		"view commands");
	printf("  %-50s %s\n",
		"./miniRT --demo",
		"showcase demo");
	return (0);
}

int	ft_commands(void)
{
	printf("\nminiRT — Commands Reference\n\n");

	printf("=== GENERAL ===\n");
	printf("  %-35s %s\n", "ESC",          "Exit the program");
	printf("  %-35s %s\n", "F1",           "Return to scene menu");
	printf("  %-35s %s\n", "SPACE",        "Toggle preview / full render");
	printf("  %-35s %s\n", "TAB",   		"Screenshot");
	printf("  %-35s %s\n", "CAPSLOCK",   	"Save current scene to file");
	printf("\n");

	printf("=== CAMERA (preview mode) ===\n");
	printf("  %-35s %s\n", "W / S",        "Move forward / backward");
	printf("  %-35s %s\n", "A / D",        "Move left / right");
	printf("  %-35s %s\n", "Q / E",        "Move up / down");
	printf("  %-35s %s\n", "Arrow UP/DOWN","Rotate pitch");
	printf("  %-35s %s\n", "Arrow LEFT/RIGHT", "Rotate yaw");
	printf("  %-35s %s\n", "Z / C",        "Rotate roll");
	printf("  %-35s %s\n", "Scroll",       "Adjust FOV");
	printf("\n");

	printf("=== ADD OBJECTS (preview, no selection) ===\n");
	printf("  %-35s %s\n", "1",            "Add sphere");
	printf("  %-35s %s\n", "2",            "Add cylinder");
	printf("  %-35s %s\n", "3",            "Add triangle");
	printf("  %-35s %s\n", "4",            "Add plane");
	printf("  %-35s %s\n", "5",            "Add light");
	printf("\n");

	printf("=== EDIT OBJECT (click to select) ===\n");
	printf("  %-35s %s\n", "W / S",        "Move on Y axis");
	printf("  %-35s %s\n", "A / D",        "Move on X axis");
	printf("  %-35s %s\n", "Scroll",       "Move on Z axis");
	printf("  %-35s %s\n", "Arrow UP/DOWN","Rotate pitch");
	printf("  %-35s %s\n", "Arrow LEFT/RIGHT", "Rotate yaw");
	printf("  %-35s %s\n", "Z / C",        "Rotate roll");
	printf("  %-35s %s\n", "J / K",        "Decrease / increase size");
	printf("  %-35s %s\n", "N / M",        "Decrease / increase height (cylinder)");
	printf("  %-35s %s\n", "I / O",        "Decrease / increase reflectivity");
	printf("  %-35s %s\n", "T",            "Edit color (terminal prompt)");
	printf("  %-35s %s\n", "+ / -",        "Adjust edit sensitivity");
	printf("  %-35s %s\n", "BACKSPACE",    "Remove selected object");
	printf("  %-35s %s\n", "Q",            "Deselect object");
	printf("\n");

	printf("=== LIGHTS ===\n");
	printf("  %-35s %s\n", "LEFT SHIFT",   "Toggle light edit mode");
	printf("  %-35s %s\n", "[ / ]",        "Select previous / next light");
	printf("  %-35s %s\n", "P",            "Set light position (terminal prompt)");
	printf("  %-35s %s\n", "J / K",        "Decrease / increase intensity");
	printf("  %-35s %s\n", "T",            "Edit light color (terminal prompt)");
	printf("\n");

	return (0);
}
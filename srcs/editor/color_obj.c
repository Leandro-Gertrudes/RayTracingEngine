/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:06:53 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/16 14:30:19 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_color(t_object *obj, t_rgb color)
{
	if (obj->type == SPHERE)
		((t_sphere *)obj->data)->color = color;
	else if (obj->type == PLANE)
		((t_plane *)obj->data)->color = color;
	else if (obj->type == CYLINDER)
		((t_cylinder *)obj->data)->color = color;
	else if (obj->type == TRIANGLE)
		((t_triangle *)obj->data)->color = color;
	else if (obj->type == LIGHT)
		((t_light *)obj->data)->color = color;
}


void	insert_rgb_values(char *str, t_rgb *out)
{
	char **s;

	s = ft_split(str, ',');
	out->r = ft_atoi(s[0]);
	out->g = ft_atoi(s[1]);
	out->b = ft_atoi(s[2]);
	ft_free_split(s);
}


int	parse_color_input(char *line, t_rgb *out)
{
	char *trim;

	if (line[0] >= '1' && line[0] <= '5' && line[1] == '\n')
	{
		if (line[0] == '1' && line[1] == '\n') *out = (t_rgb){255, 0, 0};
		if (line[0] == '2' && line[1] == '\n') *out = (t_rgb){0, 255, 0};
		if (line[0] == '3' && line[1] == '\n') *out = (t_rgb){0, 0, 255};
		if (line[0] == '4' && line[1] == '\n') *out = (t_rgb){255, 255, 255};
		if (line[0] == '5' && line[1] == '\n') *out = (t_rgb){0, 0, 0};
		return (1);
	}
	trim = ft_strtrim(line, "\n");

	if (!ft_parser_rgb(trim))
	{
		ft_putendl_fd("\033[1;31m❌ Invalid color format!\033[0m\n", 2);
		return (0);
	}
	insert_rgb_values(trim, out);
	free(trim);
	return (1);
}

void	request_color_from_terminal(t_scene *scene)
{
	char	*line;
	t_rgb	color;

    printf("\033[1;37m\n=== COLOR EDIT MODE ===\033[0m\n");
    printf("\033[1;33mPresets:\033[0m\n\n");

    printf("\033[1;31m(1) Red\033[0m  ");
    printf("\033[1;32m(2) Green\033[0m  ");
    printf("\033[1;34m(3) Blue\033[0m\n");
    printf("\033[1;37m(4) White\033[0m  ");
    printf("\033[1;30m(5) Black\033[0m\n\n");
    printf("\033[1;36mtype RGB as: r,g,b or 'q' to quit\033[0m\n");
    printf("> ");

	line = get_next_line(0);
	if (!line)
		return ;

	if ((line[0] == 'q' || line[0] == 'Q') && line[1] == '\n')
		return (printf("\033[1;33mCanceled color edit.\033[0m\n"), free(line));

	if (parse_color_input(line, &color))
	{
		printf("\033[1;32m✅ Color applied: R=%d G=%d B=%d\033[0m\n",
			color.r, color.g, color.b);
		apply_color(&scene->obj_edit, color);
	}

	free(line);
}


void	render_color_prompt(t_scene *scene)
{
	draw_bw_overlay(scene, 0.6);

	mlx_put_image_to_window(scene->disp.mlx,
		scene->disp.win, scene->disp.img, 0, 0);

	mlx_string_put(scene->disp.mlx, scene->disp.win,
		WIDTH / 2 - 120, HEIGHT / 2 - 20,
		0xFFFFFF, "COLOR EDIT");

	mlx_string_put(scene->disp.mlx, scene->disp.win,
		WIDTH / 2 - 200, HEIGHT / 2 + 10,
		0xFFFFFF, "Terminal: enter RGB or preset number");

	mlx_do_sync(scene->disp.mlx);
}

void	color_obj_edit(t_scene *scene, t_object *obj_edit, int keycode)
{
	(void)keycode;
	g_edit_color = true;
	render_color_prompt(scene);
	request_color_from_terminal(scene);
	low_render_scene(scene);
	draw_hud_obj(scene, scene->obj_edit.type, scene->obj_edit.data);
	mlx_do_sync(scene->disp.mlx);
	g_edit_color = false;
	(void)obj_edit;
}
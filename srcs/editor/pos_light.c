/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:29:09 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/24 14:32:14 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_light_position(t_light *light, t_vec3 pos)
{
	if (!light)
		return;
	light->position = pos;
}


int	parse_vec3_input(char *line, t_vec3 *out)
{
	char	*trim;
	char	**s;

	trim = ft_strtrim(line, "\n");

	if (!ft_parser_vec3(trim))
	{
		ft_putendl_fd("\033[1;31m❌ Invalid format (use x,y,z)\033[0m", 2);
		free(trim);
		return (0);
	}
	s = ft_split(trim, ',');
	out->x = ft_atod(s[0]);
	out->y = ft_atod(s[1]);
	out->z = ft_atod(s[2]);
	ft_free_split(s);
	free(trim);
	return (1);
}


void	request_light_position_from_terminal(t_scene *scene)
{
	char	*line;
	t_vec3	pos;
	t_light	*l;

	if (scene->obj_edit.type != LIGHT)
		return;

	l = scene->obj_edit.data;

	printf("\033[1;37m\n=== LIGHT POSITION EDIT ===\033[0m\n");
	printf("\033[1;36mCurrent: %.2f %.2f %.2f\033[0m\n\n",
		l->position.x, l->position.y, l->position.z);
	printf("type position as: x,y,z or 'q' to quit\n");
	printf("> ");

	line = get_next_line(0);
	if (!line)
		return;

	if ((line[0] == 'q' || line[0] == 'Q') && line[1] == '\n')
	{
		printf("\033[1;33mCanceled position edit.\033[0m\n");
		free(line);
		return;
	}

	if (parse_vec3_input(line, &pos))
	{
		apply_light_position(l, pos);
		printf("\033[1;32m✅ Light moved to %.2f %.2f %.2f\033[0m\n",
			pos.x, pos.y, pos.z);
	}

	free(line);
}


void	render_position_prompt(t_scene *scene)
{
	draw_bw_overlay(scene, 0.6);

	mlx_put_image_to_window(scene->disp.mlx,
		scene->disp.win, scene->disp.img, 0, 0);

	mlx_string_put(scene->disp.mlx, scene->disp.win,
		WIDTH / 2 - 140, HEIGHT / 2 - 20,
		0xFFFFFF, "LIGHT POSITION EDIT");

	mlx_string_put(scene->disp.mlx, scene->disp.win,
		WIDTH / 2 - 220, HEIGHT / 2 + 10,
		0xFFFFFF, "Terminal: enter x,y,z");

	mlx_do_sync(scene->disp.mlx);
}

void	position_light(t_scene *scene)
{
	if (!scene || scene->obj_edit.type != LIGHT)
		return;

	g_edit_color = true;
	render_position_prompt(scene);
	request_light_position_from_terminal(scene);

	low_render_scene(scene);
	draw_hud_obj(scene, scene->obj_edit.type, scene->obj_edit.data);
	mlx_do_sync(scene->disp.mlx);

	g_edit_color = false;
}

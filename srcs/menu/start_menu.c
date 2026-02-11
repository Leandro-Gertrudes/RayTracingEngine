/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:33:54 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/11 14:48:26 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_menu(t_menu *m)
{
	int	i;

	i = 0;
	while (i < m->scene_count)
	{
		free(m->scenes[i]);
		i++;
	}
	free(m->scenes);
	mlx_destroy_window(m->mlx, m->win);
	mlx_destroy_display(m->mlx);
	free(m->mlx);
	free(m);
}


void	start_render_from_menu(t_menu *m)
{
	char	fullpath[512];

	if (m->mode_selected == 0)
		g_mode = DEFAULT;
	else if (m->mode_selected == 1)
		g_mode = ANIMATE;
	else
	{
		g_mode = SAVE_FRAMES;
		startFrame = 0;
		endFrame = 300;
	}

	sprintf(fullpath, "./scenes/%s", m->scenes[m->scene_selected]);

	mlx_loop_end(m->mlx);
	free_menu(m);

	ft_minirt(fullpath);
}


int	menu_render(t_menu *m)
{
	int	y = 120;
	int	start;
	int	end;

	mlx_clear_window(m->mlx, m->win);
	mlx_string_put(m->mlx, m->win, 250, 30, 0xFFFFFF, "miniRT");

	start = m->current_page * m->scenes_per_page;
	end = start + m->scenes_per_page;
	if (end > m->scene_count)
		end = m->scene_count;

	for (int i = start; i < end; i++)
	{
		if (i == m->scene_selected)
			mlx_string_put(m->mlx, m->win, 250, y, 0x00FF00, m->scenes[i]);
		else
			mlx_string_put(m->mlx, m->win, 250, y, 0xFFFFFF, m->scenes[i]);
		y += 20;
	}

	// PAGE
	int total_pages;

	total_pages= m->scene_count / m->scenes_per_page;
	if (m->scene_count % m->scenes_per_page > 0) {
		total_pages++;
	}

	char page_str[50];
	sprintf(page_str, "Page %d/%d",
		m->current_page + 1, total_pages);
	mlx_string_put(m->mlx, m->win, 230, 90, 0xAAAAAA, page_str);

	mlx_string_put(m->mlx, m->win, 220, 190, 0xAAAAAA, "/\\");
	mlx_string_put(m->mlx, m->win, 220, 220, 0xAAAAAA, "\\/");
	mlx_string_put(m->mlx, m->win, 280, 325, 0xAAAAAA, "< >");
	
	// MODE
	mlx_string_put(m->mlx, m->win, 505, 360, 0xFFFFFF, "MODE (+ / -)");

	mlx_string_put(m->mlx, m->win, 490, 380,
		m->mode_selected == 0 ? 0x00FF00 : 0xFFFFFF, "DEFAULT");
	mlx_string_put(m->mlx, m->win, 540, 380,
		m->mode_selected == 1 ? 0x00FF00 : 0xFFFFFF, "ANIMATE");

	return (0);
}


int	menu_key_hook(int key, t_menu *m)
{
	int	max_page;

	max_page = (m->scene_count - 1) / m->scenes_per_page;


	if (key == KEY_UP && m->scene_selected > 0)
		m->scene_selected--;
	else if (key == KEY_DOWN && m->scene_selected < m->scene_count - 1)
		m->scene_selected++;
	else if (key == KEY_RIGHT && m->current_page < max_page)
		m->current_page++;
	else if (key == KEY_LEFT && m->current_page > 0)
		m->current_page--;
		
	if (m->scene_selected < m->current_page * m->scenes_per_page)
		m->scene_selected = m->current_page * m->scenes_per_page;

	if (m->scene_selected >= (m->current_page + 1) * m->scenes_per_page)
		m->scene_selected = m->current_page * m->scenes_per_page;
		
	if (key == KEY_PLUS && m->mode_selected < 1)
		m->mode_selected++;
	else if (key == KEY_MINUS && m->mode_selected > 0)
		m->mode_selected--;
	else if (key == KEY_ENTER)
		start_render_from_menu(m);
	
	if (key == KEY_ESQ) // ESC
	{
		mlx_loop_end(m->mlx);
		free_menu(m);
		exit(0);
	}

	return (0);
}


void	menu()
{
	t_menu	*menu;

	menu = malloc(sizeof(t_menu));
	if (!menu)
		return;

	menu->mlx = mlx_init();
	menu->win = mlx_new_window(menu->mlx, 600, 400, "miniRT");

	menu->scenes = load_scenes("./scenes", &menu->scene_count);
	menu->scene_selected = 0;
	menu->current_page = 0;
	menu->mode_selected = 0;
	menu->scenes_per_page = 10;

	mlx_key_hook(menu->win, menu_key_hook, menu);
	mlx_loop_hook(menu->mlx, menu_render, menu);
	mlx_loop(menu->mlx);
}

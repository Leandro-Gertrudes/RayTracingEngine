/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:28:01 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/20 16:50:34 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_bw_overlay(t_scene *scene, double strength);

void	render_transition(t_scene *scene)
{
	draw_bw_overlay(scene, 0.6);

	mlx_put_image_to_window(scene->disp.mlx,
			scene->disp.win, scene->disp.img, 0, 0);

	mlx_string_put(scene->disp.mlx, scene->disp.win,
		WIDTH / 2 - 70, HEIGHT / 2,
		0xFFFFFF, "Rendering...");

	mlx_do_sync(scene->disp.mlx);

	render_scene(scene);
}

t_rgb	get_pixel(t_scene *scene, int x, int y)
{
	char	*src;
	t_rgb	c;

	src = scene->disp.addr
		+ (y * scene->disp.line_length
		+ x * (scene->disp.bpp / 8));

	c.b = (unsigned char)src[0];
	c.g = (unsigned char)src[1];
	c.r = (unsigned char)src[2];
	return (c);
}


void	draw_bw_overlay(t_scene *scene, double strength)
{
	int		x;
	int		y;
	int		gray;
	t_rgb	c;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c = get_pixel(scene, x, y);

			gray = (int)(
				0.299 * c.r +
				0.587 * c.g +
				0.114 * c.b
			);

			gray = (int)(gray * strength);
			if (gray > 255)
				gray = 255;
			if (gray < 0)
				gray = 0;

			put_pixel(scene, x, y,
				rgb_to_int((t_rgb){gray, gray, gray}));

			x++;
		}
		y++;
	}
}





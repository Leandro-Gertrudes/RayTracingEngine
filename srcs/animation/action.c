/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:05:20 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/16 14:20:54 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// --save frames mode
void	render_animation(t_scene *sc)
{
	int		frame;
	char	name[64];

	frame = startFrame;
	while (frame <= endFrame)
	{
		update_time(sc);

		update_scene(sc); // <--- when you move your scene

		image_clear(sc->image);

		if(low_render)
			low_render_scene(sc);
		else
			render_scene(sc);

		sprintf(name, "frames/frame_%04d.ppm", frame);
		save_image_ppm(sc->image, name);

		printf("frame %d done\n", frame);
		frame++;
	}
}

// --animate mode
int	render_loop(void *param)
{
	t_scene	*sc;

	sc = (t_scene *)param;
	if(low_render)
		low_render_scene(sc);
	else
		render_scene(sc);

	update_scene(sc);

	return (0);
}

void	update_scene(t_scene *sc)
{
	update_time(sc);

	//update_diamond_rotation(sc); // run with ./miniRT scene/diamond.rt --animate or --frames
	//update_rain(sc); // run with ./miniRT scene/rain.rt --animate or --frames
	//update_billiard(sc); // run with ./miniRT scene/billard.rt --animate or --frames
	//update_falling_sphere(sc); // run with ./miniRT scene/spheres.rt --animate or --frames
	//update_anim_spheres(sc); // run with ./miniRT scene/losangle.rt --animate or --frames
	update_dragon(sc); //(HEAVY!) run with ./miniRT scene/dragon.rt --animate or --frames 

	sc->camera->camdata = ft_compute_camera(
		*sc->camera,
		WIDTH,
		HEIGHT
	);
}

void	update_time(t_scene *sc)
{
    sc->time.delta = 1.0 / 24.0;
    sc->time.current += sc->time.delta;
}
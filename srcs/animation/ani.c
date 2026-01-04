/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ani.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:10:46 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/30 19:04:09 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/time.h>



void	update_time(t_scene *sc)
{
	static double	last = 0;
	double			now;

	now = get_time_sec();
	if (last == 0)
		last = now;
	sc->time.delta = now - last;
	sc->time.current += sc->time.delta;
	last = now;
}
void	init_anim_light(t_scene *sc)
{
	sc->anim_light.light = sc->lights[0];
	sc->anim_light.radius = 5.0;
	sc->anim_light.speed = 1;
	sc->anim_light.center = sc->anim_light.light->position;
}


double	get_time_sec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec * 0.000001);
}

void	update_anim_light(t_scene *sc)
{
	double	t;

	t = sc->time.current * sc->anim_light.speed;
	sc->anim_light.light->position.x =
		sc->anim_light.center.x + cos(t) * sc->anim_light.radius;
	sc->anim_light.light->position.z =
		sc->anim_light.center.z + sin(t) * sc->anim_light.radius;
}


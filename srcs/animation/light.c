/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:10:46 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/18 16:08:28 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/time.h>

void	update_time(t_scene *sc)
{
    sc->time.delta = 1.0 / 24.0;   // ou 1.0 / 30.0
    sc->time.current += sc->time.delta;
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


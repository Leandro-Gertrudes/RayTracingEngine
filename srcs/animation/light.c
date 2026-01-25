/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:10:46 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/25 14:56:23 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/time.h>

void	update_time(t_scene *sc)
{
    sc->time.delta = 1.0 / 24.0;
    sc->time.current += sc->time.delta;
}
void	init_anim_light(t_scene *sc)
{
    sc->anim_light[0].light  = sc->lights[0];
    sc->anim_light[0].center = sc->lights[0]->position;
    sc->anim_light[0].radius = 20;
    sc->anim_light[0].speed  = 5.0;
    sc->anim_light[0].phase  = 0.0;

    sc->anim_light[1].light  = sc->lights[1];
    sc->anim_light[1].center = sc->lights[1]->position;
    sc->anim_light[1].radius = 20;
    sc->anim_light[1].speed  = -5.0;        // 👈 sentido oposto
    sc->anim_light[1].phase  = M_PI;         // 👈 começa oposta
}



double	get_time_sec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec * 0.000001);
}

void	update_anim_light(t_scene *sc)
{
    for (int i = 0; i < 2; i++)
    {
        t_anim_light *a = &sc->anim_light[i];
        double t = sc->time.current * a->speed + a->phase;

        a->light->position.x =
            a->center.x + cos(t) * a->radius;
        a->light->position.z =
            a->center.z + sin(t) * a->radius;
    }
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:14:28 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/18 16:11:44 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_anim_camera(t_scene *sc)
{
	sc->anim_camera.cam = sc->camera;
	sc->anim_camera.radius = 600.0;
	sc->anim_camera.speed = 0.3;
}
void update_anim_camera(t_scene *sc)
{
	double t = sc->time.current;
	t_vec3 target;

	// ===== SHOT 1 — PÉS / CHÃO =====
	if (t < 3.0)
	{
		sc->camera->position = (t_vec3){ 0, 10, -60 + t * 10 };
		target = (t_vec3){ 0, 15, 0 };
	}
	// ===== SHOT 2 — SUBINDO PELO CORPO =====
	else if (t < 6.0)
	{
		double k = (t - 3.0) / 3.0;

		sc->camera->position.x = 0;
		sc->camera->position.y = 10 + k * 20;
		sc->camera->position.z = -40 + k * 10;

		target = (t_vec3){ 0, 25, 0 };
	}
	// ===== SHOT 3 — PASSANDO PELA ASA =====
	else if (t < 9.0)
	{
		double a = (t - 6.0) * 0.6;

		sc->camera->position.x = cos(a) * 40;
		sc->camera->position.y = 30;
		sc->camera->position.z = sin(a) * 40;

		target = (t_vec3){ 0, 30, 0 };
	}
	// ===== SHOT 4 — HERO SHOT (CABEÇA) =====
	else
	{
		sc->camera->position = (t_vec3){ 0, 35, -30 };
		target = (t_vec3){ 0, 40, 20 };
	}

	sc->camera->vector = vec3_normalize(
		vec3_sub(target, sc->camera->position)
	);
}

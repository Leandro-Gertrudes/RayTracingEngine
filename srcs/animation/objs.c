/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:11:15 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/18 16:11:37 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* caida da esfera
static double velocity = 0.0;

void update_falling_sphere(t_scene *sc)
{
    t_object *obj;
    t_sphere *sp;

    double dt = 1.0 / 24.0;
    double gravity = -10.0;     // gravidade forte (fica bonito)
    double ground_y = -0.5;    // altura do chão
    double damping = 0.65;      // perda de energia no quique

    obj = sc->objects[0];
    if (obj->type != SPHERE)
        return;

    sp = (t_sphere *)obj->data;

    // aplica gravidade
    velocity += gravity * dt;

    // move a esfera
    sp->center.y += velocity * dt;

    // colisão com o chão
    if (sp->center.y - (sp->diameter / 2) <= ground_y)
    {
        sp->center.y = ground_y + (sp->diameter / 2);

        // inverte a velocidade (quique)
        velocity = -velocity * damping;

        // mata micro vibração
        if (fabs(velocity) < 1.0)
            velocity = 0.0;
    }
}*/

void update_anim_spheres(t_scene *sc)
{
	double angle, radius = 30.0;
	double center_x = 0, center_y = 0, z = 90;
	int i;
	t_object *obj;

	for (i = 0; i < sc->object_count; i++)
	{
		obj = sc->objects[i];
		if (obj->type == SPHERE)
		{
			t_sphere *sp = (t_sphere *)obj->data;
			angle = sc->time.current * 2 * M_PI / 5.0 + (i * M_PI / 2);
			sp->center.x = center_x + radius * cos(angle);
			sp->center.y = center_y + radius * sin(angle);
			sp->center.z = z;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:11:15 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/11 10:19:54 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Diamante girando====================
// Adiciona no topo do arquivo (variáveis estáticas para guardar posições originais)
static t_vec3 diamond_original[48]; // 16 triângulos x 3 vértices = 48 pontos
static int diamond_initialized = 0;

void update_diamond_rotation(t_scene *sc)
{
    double angle;
    double cos_a, sin_a;
    t_vec3 center = {0.0, 5.0, 0.0}; // centro do diamante
    int i, vertex_idx;
    
    // primeira vez: salva posições originais
    if (!diamond_initialized)
    {
        vertex_idx = 0;
        for (i = 0; i < sc->object_count; i++)
        {
            if (sc->objects[i]->type == TRIANGLE)
            {
                t_triangle *tr = (t_triangle *)sc->objects[i]->data;
                diamond_original[vertex_idx++] = tr->a;
                diamond_original[vertex_idx++] = tr->b;
                diamond_original[vertex_idx++] = tr->c;
            }
        }
        diamond_initialized = 1;
    }
    
    // velocidade de rotação (1 volta a cada 5 segundos)
    angle = sc->time.current * 2.0 * M_PI / 15.0;
    
    cos_a = cos(angle);
    sin_a = sin(angle);
    
    // aplica rotação a partir das posições originais
    vertex_idx = 0;
    for (i = 0; i < sc->object_count; i++)
    {
        if (sc->objects[i]->type == TRIANGLE)
        {
            t_triangle *tr = (t_triangle *)sc->objects[i]->data;
            t_vec3 offset;
            
            // rotaciona vértice A
            offset.x = diamond_original[vertex_idx].x - center.x;
            offset.z = diamond_original[vertex_idx].z - center.z;
            tr->a.x = center.x + (offset.x * cos_a - offset.z * sin_a);
            tr->a.z = center.z + (offset.x * sin_a + offset.z * cos_a);
            tr->a.y = diamond_original[vertex_idx].y; // Y não muda
            vertex_idx++;
            
            // rotaciona vértice B
            offset.x = diamond_original[vertex_idx].x - center.x;
            offset.z = diamond_original[vertex_idx].z - center.z;
            tr->b.x = center.x + (offset.x * cos_a - offset.z * sin_a);
            tr->b.z = center.z + (offset.x * sin_a + offset.z * cos_a);
            tr->b.y = diamond_original[vertex_idx].y;
            vertex_idx++;
            
            // rotaciona vértice C
            offset.x = diamond_original[vertex_idx].x - center.x;
            offset.z = diamond_original[vertex_idx].z - center.z;
            tr->c.x = center.x + (offset.x * cos_a - offset.z * sin_a);
            tr->c.z = center.z + (offset.x * sin_a + offset.z * cos_a);
            tr->c.y = diamond_original[vertex_idx].y;
            vertex_idx++;
        }
    }
}

//chuva de objetos.====================

// double	rand01(void)
// {
// 	return ((double)rand() / (double)RAND_MAX);
// }

// double triangle_min_y(t_triangle *tr)
// {
// 	double min = tr->a.y;
// 	if (tr->b.y < min) min = tr->b.y;
// 	if (tr->c.y < min) min = tr->c.y;
// 	return min;
// }

// void move_triangle_y(t_triangle *tr, double dy)
// {
// 	tr->a.y += dy;
// 	tr->b.y += dy;
// 	tr->c.y += dy;
// }

// void init_rain(t_scene *sc)
// {
// 	for (int i = 0; i < sc->object_count; i++)
// 	{
// 		t_anim_body *a = &sc->anim[i];

// 		a->type = sc->objects[i]->type;
// 		a->obj = sc->objects[i]->data;

// 		a->vy = 0.0;
// 		a->restitution = 0.2 + rand01() * 0.2;
// 		a->tilt = 0.0;
// 		a->tilt_speed = 0.0;
// 		a->active = 1;

// 		if (a->type == SPHERE)
// 			((t_sphere *)a->obj)->center.y = 8.0 + rand01() * 6.0;

// 		else if (a->type == CYLINDER)
// 			((t_cylinder *)a->obj)->center.y = 9.0 + rand01() * 6.0;

// 		else if (a->type == TRIANGLE)
// 			move_triangle_y(a->obj, 10.0 + rand01() * 6.0);
// 	}
// }


// void update_rain(t_scene *sc)
// {
// 	double g = 9.8;
// 	double dt = sc->time.delta;
// 	double ground = -0.5;

// 	for (int i = 0; i < sc->object_count; i++)
// 	{
// 		t_anim_body *a = &sc->anim[i];
// 		if (!a->active)
// 			continue;

// 		// gravidade
// 		a->vy -= g * dt;

// 		/* ================= ESFERA ================= */
// 		if (a->type == SPHERE)
// 		{
// 			t_sphere *sp = a->obj;

// 			sp->center.y += a->vy * dt;

// 			if (sp->center.y <= ground + sp->diameter / 2)
// 			{
// 				sp->center.y = ground + sp->diameter / 2;
// 				a->vy = -a->vy * a->restitution;

// 				if (fabs(a->vy) < 0.2)
// 				{
// 					a->vy = 0;
// 					a->active = 0;
// 				}
// 			}
// 		}

// 		/* ================= CILINDRO ================= */
// 		else if (a->type == CYLINDER)
// 		{
// 			t_cylinder *cy = a->obj;
// 			double half_h = cy->height * 0.5;

// 			cy->center.y += a->vy * dt;

// 			if (cy->center.y <= ground + half_h)
// 			{
// 				cy->center.y = ground + half_h;
// 				a->vy = -a->vy * a->restitution;

// 				// torque visual (efeito prato)
// 				a->tilt_speed += (rand01() - 0.5) * 3.0;
// 			}

// 			// aplica inclinação fake
// 			a->tilt += a->tilt_speed * dt;
// 			a->tilt_speed *= 0.97;

// 			cy->normal = vec3_normalize((t_vec3){
// 				sin(a->tilt),
// 				1.0,
// 				cos(a->tilt)
// 			});

// 			if (fabs(a->vy) < 0.2 && fabs(a->tilt_speed) < 0.05)
// 			{
// 				a->active = 0;
// 				a->vy = 0;
// 			}
// 		}

// 		/* ================= TRIÂNGULO ================= */
//         else if (a->type == TRIANGLE)
//         {
//             t_triangle *tr = a->obj;

//             // gravidade
//             move_triangle_y(tr, a->vy * dt);

//             double min_y = triangle_min_y(tr);

//             if (min_y <= ground)
//             {
//                 move_triangle_y(tr, ground - min_y);

//                 a->vy = -a->vy * a->restitution;
//                 a->vy *= 0.6;

//                 // rotação fake só no impacto
//                 double r = (rand01() - 0.5) * 0.2;
//                 tr->a.x += r; tr->a.z -= r;
//                 tr->b.x -= r; tr->b.z += r;
//                 tr->c.x += r * 0.5;
//             }

//             if (fabs(a->vy) < 0.15)
//             {
//                 a->vy = 0;
//                 a->active = 0;
//             }
//         }
// 	}
// }





/* caida da esfera=====================
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

static int phase = 0;
static double cue_speed = 8.0;

static t_vec3 vel[6];
static int impulse_done = 0;


void update_billiard(t_scene *sc)
{
    double dt = 3.0 / 24.0;
    double center_x = 4.2;

    t_sphere *cue;
    cue = (t_sphere *)sc->objects[7]->data; // bola branca

    // ===== FASE 0 — AVANÇO =====
    if (phase == 0)
    {
        cue->center.z += cue_speed * dt;

        if (cue->center.z >= 4.7)
        {
            cue_speed = 0.0;
            phase = 2;
        }
    }

    // ===== FASE 2 — ESPALHAMENTO =====
    else if (phase == 2)
    {
        // aplica impulso UMA VEZ
        if (!impulse_done)
        {
            for (int i = 0; i <= 6; i++)
            {
                t_sphere *sp = (t_sphere *)sc->objects[i]->data;

                double dx = sp->center.x - center_x;

                vel[i].x = dx * 1.8;
                vel[i].z = fmax(0.8, 3.5 - fabs(dx));
                vel[i].y = 0.0;
            }
            impulse_done = 1;
        }

        // integra movimento
        for (int i = 0; i <= 6; i++)
        {
            t_sphere *sp = (t_sphere *)sc->objects[i]->data;

            sp->center.x += vel[i].x * dt;
            sp->center.z += vel[i].z * dt;

            // atrito
            vel[i].x *= 0.96;
            vel[i].z *= 0.96;
        }

        // bola branca perde energia
        cue->center.z += 0.4 * dt;
    }

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:11:15 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/16 14:27:10 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// =======================================
// ============== DRAGON =================
// =======================================

void	explode_dragon(t_scene *scene);

t_vec3	g_proj_pos;
t_vec3	g_proj_dir;
int		g_proj_explode = 0;


void	shoot_projectile(void)
{
	t_vec3	start = vec3_new(31.8765, 18.0, 35.0956);
	t_vec3	target = vec3_new(-0.3, 11.21, 7.2);

	g_proj_pos = start;
	g_proj_dir = vec3_normalize(vec3_sub(target, start));
}

float	vec3_distance(t_vec3 a, t_vec3 b)
{
	return (vec3_len(vec3_sub(a, b)));
}

void	update_dragon(t_scene *scene)
{
    t_sphere	*sp = scene->objects[1]->data;

	g_proj_pos = vec3_add(g_proj_pos, vec3_scale(g_proj_dir, 0.8f));

	sp->center = g_proj_pos;
    if (vec3_distance(g_proj_pos, vec3_new(-0.3, 11.21, 7.2)) < 2.0f)
        g_proj_explode = 1;
    if(g_proj_explode)
    	explode_dragon(scene);
}

// explosion
t_vec3	vec3_rotate_axis(t_vec3 v, t_vec3 axis, float angle)
{
	axis = vec3_normalize(axis);

	float cosA = cos(angle);
	float sinA = sin(angle);

	t_vec3 term1 = vec3_scale(v, cosA);
	t_vec3 term2 = vec3_scale(vec3_cross(axis, v), sinA);
	t_vec3 term3 = vec3_scale(axis, vec3_dot(axis, v) * (1 - cosA));

	return vec3_add(vec3_add(term1, term2), term3);
}

void explode_dragon(t_scene *scene)
{
	t_vec3	impact = vec3_new(-0.3, 11.21, 7.2);
	float	new_radius = 6.0f;

	for (int i = 0; i < scene->object_count; i++)
	{
		if (scene->objects[i]->type == TRIANGLE)
		{
			t_triangle *tri = scene->objects[i]->data;

			t_vec3 center = vec3_scale(
				vec3_add(vec3_add(tri->a, tri->b), tri->c),
				1.0f / 3.0f);

			t_vec3 diff = vec3_sub(center, impact);
			float dist = vec3_len(diff);

			t_vec3 dir = vec3_normalize(diff);

			if (dist < new_radius)
			{
				float strength = (new_radius - dist) * 0.6f;

				tri->a = vec3_add(tri->a, vec3_scale(dir, strength));
				tri->b = vec3_add(tri->b, vec3_scale(dir, strength));
				tri->c = vec3_add(tri->c, vec3_scale(dir, strength));

				float angle = 0.25f;

				t_vec3 local1 = vec3_sub(tri->a, center);
				t_vec3 local2 = vec3_sub(tri->b, center);
				t_vec3 local3 = vec3_sub(tri->c, center);

				local1 = vec3_rotate_axis(local1, dir, angle);
				local2 = vec3_rotate_axis(local2, dir, angle);
				local3 = vec3_rotate_axis(local3, dir, angle);

				tri->a = vec3_add(center, local1);
				tri->b = vec3_add(center, local2);
				tri->c = vec3_add(center, local3);
			}

			else
			{
				float strength = 2.0f / (dist + 1.0f);

				tri->a = vec3_add(tri->a, vec3_scale(dir, strength));
				tri->b = vec3_add(tri->b, vec3_scale(dir, strength));
				tri->c = vec3_add(tri->c, vec3_scale(dir, strength));

				float angle = 0.1f;

				t_vec3 local1 = vec3_sub(tri->a, center);
				t_vec3 local2 = vec3_sub(tri->b, center);
				t_vec3 local3 = vec3_sub(tri->c, center);

				local1 = vec3_rotate_axis(local1, dir, angle);
				local2 = vec3_rotate_axis(local2, dir, angle);
				local3 = vec3_rotate_axis(local3, dir, angle);

				tri->a = vec3_add(center, local1);
				tri->b = vec3_add(center, local2);
				tri->c = vec3_add(center, local3);
			}
		}
	}
}

// =======================================
// ============== DIAMOND ================
// =======================================

// 16 triangles x 3 vertices = 48 points
static	t_vec3 diamond_original[48]; 
static	int diamond_initialized = 0;

void update_diamond_rotation(t_scene *sc)
{
	double	angle;
	double	cos_a, sin_a;
	t_vec3	center = {0.0, 5.0, 0.0}; // center of the diamond
	int		i,	vertex_idx;

	// first time: save original position
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

	// speed
	angle = sc->time.current * 2.0 * M_PI / 15.0;

	cos_a = cos(angle);
	sin_a = sin(angle);

	vertex_idx = 0;
	for (i = 0; i < sc->object_count; i++)
	{
		if (sc->objects[i]->type == TRIANGLE)
		{
			t_triangle *tr = (t_triangle *)sc->objects[i]->data;
			t_vec3 offset;
			
			// vertice A
			offset.x = diamond_original[vertex_idx].x - center.x;
			offset.z = diamond_original[vertex_idx].z - center.z;
			tr->a.x = center.x + (offset.x * cos_a - offset.z * sin_a);
			tr->a.z = center.z + (offset.x * sin_a + offset.z * cos_a);
			tr->a.y = diamond_original[vertex_idx].y;
			vertex_idx++;
			
			// vertice B
			offset.x = diamond_original[vertex_idx].x - center.x;
			offset.z = diamond_original[vertex_idx].z - center.z;
			tr->b.x = center.x + (offset.x * cos_a - offset.z * sin_a);
			tr->b.z = center.z + (offset.x * sin_a + offset.z * cos_a);
			tr->b.y = diamond_original[vertex_idx].y;
			vertex_idx++;
			
			// vertice C
			offset.x = diamond_original[vertex_idx].x - center.x;
			offset.z = diamond_original[vertex_idx].z - center.z;
			tr->c.x = center.x + (offset.x * cos_a - offset.z * sin_a);
			tr->c.z = center.z + (offset.x * sin_a + offset.z * cos_a);
			tr->c.y = diamond_original[vertex_idx].y;
			vertex_idx++;
		}
	}
}


// =======================================
// =========== FALLING SPHERE ============
// =======================================

static double velocity = 0.0;

void update_falling_sphere(t_scene *sc)
{
	t_object	*obj;
	t_sphere	*sp;
	double		dt = 1.0 / 24.0;
	double		gravity = -10.0;
	double		ground_y = -0.5;
	double		damping = 0.65;

	obj = sc->objects[0];
	if (obj->type != SPHERE)
		return;

	sp = (t_sphere *)obj->data;

	// applies gravity
	velocity += gravity * dt;

	// move sphere
	sp->center.y += velocity * dt;

	// collision with the ground
	if (sp->center.y - (sp->diameter / 2) <= ground_y)
	{
		sp->center.y = ground_y + (sp->diameter / 2);

		// reverses speed (bounce)
		velocity = -velocity * damping;

		// no micro vibration
		if (fabs(velocity) < 1.0)
			velocity = 0.0;
	}
}


// =======================================
// =========== LOSANGLE SPHERES ==========
// =======================================

void update_anim_spheres(t_scene *sc)
{
	double	angle, radius = 30.0;
	double	center_x = 0, center_y = 0, z = 90;
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

// =======================================
// ============== BILLARD ================
// =======================================

static int		phase = 0;
static double	cue_speed = 8.0;

static t_vec3	vel[6];
static int		impulse_done = 0;

void update_billiard(t_scene *sc)
{
	double	dt = 3.0 / 24.0;
	double	center_x = 4.2;

	t_sphere *cue;
	cue = (t_sphere *)sc->objects[7]->data; // white ball

	// ===== phase 0 — white ball Boost =====
	if (phase == 0)
	{
		cue->center.z += cue_speed * dt;

		if (cue->center.z >= 4.7)
		{
			cue_speed = 0.0;
			phase = 1;
		}
	}

	// ===== phase 2 — spread =====
	else if (phase == 1)
	{
		// impulse
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

		// integrates movement
		for (int i = 0; i <= 6; i++)
		{
			t_sphere *sp = (t_sphere *)sc->objects[i]->data;

			sp->center.x += vel[i].x * dt;
			sp->center.z += vel[i].z * dt;

			// atrito
			vel[i].x *= 0.96;
			vel[i].z *= 0.96;
		}

		// white ball loses energy
		cue->center.z += 0.4 * dt;
	}
}

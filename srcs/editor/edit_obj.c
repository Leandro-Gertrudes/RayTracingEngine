/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:22:04 by lgertrud          #+#    #+#             */
/*   Updated: 2026/05/24 15:13:56 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const char *obj_type_to_str(t_obj_type type)
{
	if (type == SPHERE)
		return ("SPHERE");
	if (type == PLANE)
		return ("PLANE");
	if (type == CYLINDER)
		return ("CYLINDER");
	if (type == TRIANGLE)
		return ("TRIANGLE");
	if (type == LIGHT)
		return ("LIGHT");
	return ("UNKNOWN");
}

void	draw_hud_obj(t_scene *scene, t_obj_type type, void *data)
{
	int x = 10, y = 10;
	char buf[128];

	mlx_put_image_to_window(scene->disp.mlx, scene->disp.win,
		scene->disp.img, 0, 0);

	int line_y = y + 15;

	mlx_string_put(scene->disp.mlx, scene->disp.win,
		x + 10, line_y, 0xFFD700, "MiniRaytracer");
	line_y += 22;

	mlx_string_put(scene->disp.mlx, scene->disp.win,
		x + 10, line_y, 0xAAAAAA, "=== Selection ===");
	line_y += 18;

	snprintf(buf, sizeof(buf), "Type: %s",
		obj_type_to_str(type));
	mlx_string_put(scene->disp.mlx, scene->disp.win,
		x + 10, line_y, 0xFFFFFF, buf);
	line_y += 18;

	// ===== INFO ===== //
	show_infos(scene, type, data, x, line_y);
}

void	show_infos(t_scene *scene, t_obj_type type,
	void *data, int x, int line_y)
{
	char	buf[128];

	if (type == SPHERE)
	{
		t_sphere *sp = data;

		snprintf(buf, sizeof(buf),
			"Center: %.2f %.2f %.2f",
			sp->center.x, sp->center.y, sp->center.z);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 18;

		snprintf(buf, sizeof(buf),
			"Diameter: %.2f", sp->diameter);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;

		snprintf(buf, sizeof(buf),
			"Reflectivity: %.1f",
			sp->reflectivity);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;
	}
	else if (type == PLANE)
	{
		t_plane *pl = data;

		snprintf(buf, sizeof(buf),
			"Point: %.2f %.2f %.2f",
			pl->point.x, pl->point.y, pl->point.z);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 18;

		snprintf(buf, sizeof(buf),
			"Normal: %.2f %.2f %.2f",
			pl->normal.x, pl->normal.y, pl->normal.z);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;

		snprintf(buf, sizeof(buf),
			"Reflectivity: %.1f",
			pl->reflectivity);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;
	}
	else if (type == CYLINDER)
	{
		t_cylinder *cy = data;

		snprintf(buf, sizeof(buf),
			"Center: %.2f %.2f %.2f",
			cy->center.x, cy->center.y, cy->center.z);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 18;

		snprintf(buf, sizeof(buf),
			"Height: %.2f  Diameter: %.2f",
			cy->height, cy->diameter);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;

		snprintf(buf, sizeof(buf),
			"Reflectivity: %.1f",
			cy->reflectivity);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;

	}
	else if (type == TRIANGLE)
	{
		t_triangle *tr = data;

		snprintf(buf, sizeof(buf),
			"A: %.1f %.1f %.1f",
			tr->a.x, tr->a.y, tr->a.z);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;

		snprintf(buf, sizeof(buf),
			"B: %.1f %.1f %.1f",
			tr->b.x, tr->b.y, tr->b.z);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;

		snprintf(buf, sizeof(buf),
			"C: %.1f %.1f %.1f",
			tr->c.x, tr->c.y, tr->c.z);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;
		
		snprintf(buf, sizeof(buf),
			"Reflectivity: %.1f",
			tr->reflectivity);
		mlx_string_put(scene->disp.mlx, scene->disp.win,
			x + 10, line_y, 0xFFFFFF, buf);
		line_y += 16;
	}
	else if (type == LIGHT)
	{
	t_light *li = data;

	snprintf(buf, sizeof(buf),
		"Position: %.2f %.2f %.2f",
		li->position.x, li->position.y, li->position.z);
	mlx_string_put(scene->disp.mlx, scene->disp.win,
		x + 10, line_y, 0xFFFFFF, buf);
	line_y += 18;

	snprintf(buf, sizeof(buf),
		"Color: %d %d %d",
		li->color.r, li->color.g, li->color.b);
	mlx_string_put(scene->disp.mlx, scene->disp.win,
		x + 10, line_y, 0xFFFFFF, buf);
	line_y += 16;

	snprintf(buf, sizeof(buf),
		"Intensity: %.2f",
		li->ratio);
	mlx_string_put(scene->disp.mlx, scene->disp.win,
		x + 10, line_y, 0xFFFFFF, buf);
	line_y += 16;
	}

	snprintf(buf, sizeof(buf),
			"Edit sensitivity : %.1f", g_scale_edit);
	mlx_string_put(scene->disp.mlx, scene->disp.win,
		x + 10, line_y + 16, 0xFFFFFF, buf);
		
	mlx_string_put(scene->disp.mlx, scene->disp.win,
		x + 100, line_y + 54, 0xAAAAAA, "press Q to return");
}



static int	click(int x, int y, t_scene *scene)
{
	t_ray	ray;
	t_hit	hit;

	if(g_edit_color)
		return (0);
	ray = make_ray(x, y, scene);
	if (hit_objects(scene, ray, &hit))
	{
		scene->obj_edit.data = hit.object;
		scene->obj_edit.type = hit.type;
		if(hit.type == LIGHT)
			g_low_light = hit.object;
		low_render_scene(scene);
		draw_hud_obj(scene, hit.type, hit.object);
		g_edit = true;
	}
	else
	{
		g_edit = false;
		draw_hud(scene);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_scene	*scene = (t_scene *)param;
	(void)x;
	(void)y;

	if (!low_render)
		return (0);

	if(button == 1)
		return(click(x, y, scene));
	
	if ((button == 4 || button == 5) && g_edit)
	{
		move_obj_z(scene, &scene->obj_edit, button);
		return (0);
	}

	if (button == 4) // scroll up
		scene->camera->fov -= 2;
	if (button == 5) // scroll down
		scene->camera->fov += 2;

	if (scene->camera->fov < 20)
		scene->camera->fov = 20;
	if (scene->camera->fov > 120)
		scene->camera->fov = 120;

	scene->camera->camdata =
		ft_compute_camera(*scene->camera, WIDTH, HEIGHT);

	low_render_scene(scene);
	return (0);
}

void	edit_obj(t_scene *scene, t_object *obj_edit, int keycode)
{
	//printf("%d\n", keycode);
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
			|| keycode == KEY_D)
		return (move_obj_xy(scene, obj_edit, keycode));
		
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_UP
	 		|| keycode == KEY_DOWN || keycode == KEY_Z || keycode == KEY_C)
		return (move_obj_angule(scene, obj_edit, keycode));

	else if (keycode == KEY_J || keycode == KEY_K || keycode == KEY_N
				|| keycode == KEY_M)
		return (size_obj(scene, obj_edit, keycode));

	else if (keycode == KEY_T)
		color_obj_edit(scene, obj_edit, keycode);
		
	else if (keycode == KEY_I || keycode == KEY_O)
		return (reflectivity_update(scene, obj_edit, keycode));

	else if(g_edit_light && (keycode == 65105 || keycode == 91 || keycode == KEY_P))
		select_light(scene, keycode);
	
	else if (keycode == KEY_BACKSPACE)
		remove_obj(scene);
}
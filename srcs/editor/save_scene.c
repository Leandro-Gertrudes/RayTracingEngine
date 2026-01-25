/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:57:31 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/25 15:43:49 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*get_filename(void)
{
	char	buf[256];
	int		i = 0;
	int		r;

	write(1, "\nNome do ficheiro (.rt): ", 25);
	r = read(0, buf, 255);
	if (r <= 1)
		return (NULL);
	buf[r - 1] = '\0';

	while (buf[i])
		i++;
	if (i < 3 || buf[i - 3] != '.' || buf[i - 2] != 'r' || buf[i - 1] != 't')
		return (ft_strjoin(buf, ".rt"));
	return (ft_strdup(buf));
}

void	write_cylinder(int fd, t_object *cy)
{
	t_cylinder *o = cy->data;

	dprintf(fd,
		"cy %.2f,%.2f,%.2f %.2f,%.2f,%.2f %.2f %.2f %d,%d,%d %f\n",
		o->center.x, o->center.y, o->center.z,
		o->normal.x, o->normal.y, o->normal.z,
		o->diameter,
		o->height,
		o->color.r, o->color.g, o->color.b,
		o->reflectivity);
}


void	write_plane(int fd, t_object *pl)
{
	t_plane *o = pl->data;

	dprintf(fd, "pl %.2f,%.2f,%.2f %.2f,%.2f,%.2f %d,%d,%d %f\n",
		o->point.x, o->point.y, o->point.z,
		o->normal.x, o->normal.y, o->normal.z,
		o->color.r, o->color.g, o->color.b, 
		o->reflectivity);
}


void	write_sphere(int fd, t_object *sp)
{
	t_sphere *o = sp->data;

	dprintf(fd, "sp %.2f,%.2f,%.2f %.2f %d,%d,%d %f\n",
		o->center.x, o->center.y, o->center.z,
		o->diameter,
		o->color.r, o->color.g, o->color.b,
		o->reflectivity);
}

void	write_triangle(int fd, t_object *tr)
{
	t_triangle *o = tr->data;

	dprintf(fd, "tr %.2f,%.2f,%.2f %.2f,%.2f,%.2f %.2f,%.2f,%.2f %d,%d,%d %f\n",
		o->a.x, o->a.y, o->a.z,
		o->b.x, o->b.y, o->b.z,
		o->c.x, o->c.y, o->c.z,
		o->color.r, o->color.g, o->color.b,
		o->reflectivity);
}

void	write_objects(int fd, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i])
		{
			if (scene->objects[i]->type == SPHERE)
				write_sphere(fd, scene->objects[i]);
			else if (scene->objects[i]->type == PLANE)
				write_plane(fd, scene->objects[i]);
			else if (scene->objects[i]->type == CYLINDER)
				write_cylinder(fd, scene->objects[i]);
			else if (scene->objects[i]->type == TRIANGLE)
				write_triangle(fd, scene->objects[i]);
		}
		i++;
	}
}

void	write_lights(int fd, t_light **l, int count)
{
	int i;
	
	i = 0;
	while (i < count)
	{
		dprintf(fd, "L %.2f,%.2f,%.2f %.2f %d,%d,%d\n",
			l[i]->position.x, l[i]->position.y, l[i]->position.z,
			l[i]->ratio,
			l[i]->color.r, l[i]->color.g, l[i]->color.b);
		i++;
	}
}

void	write_camera(int fd, t_camera *c)
{
	dprintf(fd, "C %.2f,%.2f,%.2f %.2f,%.2f,%.2f %d\n",
		c->position.x, c->position.y, c->position.z,
		c->vector.x, c->vector.y, c->vector.z,
		c->fov);
}

void	write_ambient(int fd, t_ambient_light *a)
{
	if (!a)
		return ;
	dprintf(fd, "A %.2f %d,%d,%d\n",
		a->ratio,
		a->color.r, a->color.g, a->color.b);
}


void	write_scene(int fd, t_scene *scene)
{
	write_camera(fd, scene->camera);
	write_ambient(fd, scene->ambient);
	write_lights(fd, scene->lights, scene->light_count);
	write_objects(fd, scene);
}


void	save_scene(t_scene *scene)
{
	int		fd;
	char	*filename;

	filename = get_filename();
	if (!filename)
		return ;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(filename);
		return ;
	}

	write_scene(fd, scene);

	close(fd);
	free(filename);
	write(1, "Cena salva com sucesso!\n", 25);
}

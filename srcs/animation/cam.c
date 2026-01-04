/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:14:28 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/03 17:50:19 by lgertrud         ###   ########.fr       */
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


void	render_animation(t_scene *sc)
{
	int		frame;
	char	name[64];

	frame = 500;
	while (frame <= 600)
	{
		sc->time.current = frame * (1.0 / 24.0);

		update_anim_light(sc);
		//update_anim_camera(sc);
		//update_falling_sphere(sc);
		//update_anim_spheres(sc);

		sc->camera->camdata = ft_compute_camera(
			*sc->camera,
			WIDTH,
			HEIGHT
		);

		image_clear(sc->image);
		render_scene(sc);

		sprintf(name, "frames/frame_%04d.ppm", frame);
		save_image_ppm(sc->image, name);

		printf("frame %d done\n", frame);
		frame++;
	}
}

void	save_image_ppm(t_image *img, char *filename)
{
	int				fd;
	int				x;
	int				y;
	unsigned char	rgb[3];
	t_rgb			c;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return ;

	dprintf(fd, "P6\n%d %d\n255\n", img->width, img->height);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			c = img->pixels[y * img->width + x];
			rgb[0] = (unsigned char)c.r;
			rgb[1] = (unsigned char)c.g;
			rgb[2] = (unsigned char)c.b;
			write(fd, rgb, 3);
			x++;
		}
		y++;
	}
	close(fd);
}

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




void	update_scene(t_scene *sc)
{
	update_time(sc);
	update_anim_light(sc);
	//update_anim_camera(sc);

	sc->camera->camdata = ft_compute_camera(
		*sc->camera,
		WIDTH,
		HEIGHT
	);
}


int	render_loop(void *param)
{
	t_scene	*sc;

	sc = (t_scene *)param;
	update_scene(sc);
	render_scene(sc);
	return (0);
}

t_image	*image_create(int width, int height)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->width = width;
	img->height = height;
	img->pixels = malloc(sizeof(t_rgb) * width * height);
	if (!img->pixels)
	{
		free(img);
		return (NULL);
	}
	return (img);
}

void	image_clear(t_image *img)
{
	int	i;

	i = 0;
	while (i < img->width * img->height)
	{
		img->pixels[i].r = 0;
		img->pixels[i].g = 0;
		img->pixels[i].b = 0;
		i++;
	}
}

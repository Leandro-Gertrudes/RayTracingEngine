/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:05:20 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/18 16:15:09 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_animation(t_scene *sc)
{
	int		frame;
	char	name[64];

	frame = startFrame;
	while (frame <= endFrame)
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

// --animate
int	render_loop(void *param)
{
	t_scene	*sc;

	sc = (t_scene *)param;
	update_scene(sc);
	render_scene(sc);
	return (0);
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
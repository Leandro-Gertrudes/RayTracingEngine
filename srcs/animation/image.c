/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:12:39 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/16 14:13:26 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
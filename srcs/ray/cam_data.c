/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:42:02 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/13 21:16:53 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camdata	ft_compute_camera(t_camera cam, int width, int height)
{
	t_camdata	c;
	t_vec3		world_up;

	world_up = ft_get_vec3("0,1,0");
	c.forward = vec3_normalize(cam.vector);
	if (fabs(vec3_dot(c.forward, world_up)) > 0.999)
		world_up = ft_get_vec3("0,0,1");
	c.right = vec3_normalize(vec3_cross(c.forward, world_up));
	c.up = vec3_cross(c.right, c.forward);
	c.fov_rad = cam.fov * M_PI / 180.0;
	c.viewport_height = 2 * tan(c.fov_rad / 2);
	c.viewport_width = c.viewport_height * ((double)width / height);
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:45:39 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/23 11:00:08 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_valid_t(double t, double current);

bool	hit_light(t_ray ray, t_light *light, double *t)
{
	t_sphere	tmp;

	tmp.center = light->position;
	tmp.diameter = 0.3;
	return (hit_sphere(ray, &tmp, t));
}


void low_light(t_scene *scene, t_hit *hit, t_ray ray, double *t)
{
	int	i;

	i = 0;
	while (i < scene->light_count)
	{
		if (hit_light(ray, scene->lights[i], t)
			&& is_valid_t(*t, hit->t))
		{
			hit->t = *t;
			hit->object = scene->lights[i];
			hit->type = LIGHT;
		}
		i++;
	}
}
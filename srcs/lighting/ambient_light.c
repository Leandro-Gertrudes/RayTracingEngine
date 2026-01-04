/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiente_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:50:40 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/13 15:14:11 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	apply_ambient(t_scene *sc, t_rgb obj_color)
{
	t_rgb	res;

	res.r = obj_color.r * sc->ambient->ratio * (sc->ambient->color.r / 255.0);
	res.g = obj_color.g * sc->ambient->ratio * (sc->ambient->color.g / 255.0);
	res.b = obj_color.b * sc->ambient->ratio * (sc->ambient->color.b / 255.0);
	return (res);
}

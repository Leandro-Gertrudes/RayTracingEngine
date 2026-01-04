/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:28:05 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/12/13 21:16:31 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_normalize(t_vec3 vec)
{
	double	len;

	len = vec3_len(vec);
	if (len < 1e-10)
		return (vec3_new(0, 0, 1));
	return (vec3_scale(vec, 1.0 / len));
}

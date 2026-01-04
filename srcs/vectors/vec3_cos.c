/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:58:24 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/12/02 15:20:24 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vec3_cos(t_vec3 vec1, t_vec3 vec2)
{
	double	dot;
	double	len;

	dot = vec3_dot(vec1, vec2);
	len = vec3_len(vec1) * vec3_len(vec2);
	return (dot / len);
}

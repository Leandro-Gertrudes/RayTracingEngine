/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:29:21 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/12/02 15:21:18 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_scale(t_vec3 vec1, double scalar)
{
	return (vec3_new(vec1.x * scalar, vec1.y * scalar, vec1.z * scalar));
}

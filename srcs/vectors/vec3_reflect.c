/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_reflect_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:28:43 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/29 16:47:21 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 reflect(t_vec3 l, t_vec3 n)
{
    return vec3_sub(
        vec3_scale(n, 2.0 * vec3_dot(n, l)),
        l
    );
}


t_vec3	vec3_reflect(t_vec3 dir, t_vec3 normal)
{
	return (vec3_sub(dir,
			vec3_scale(normal, 2.0 * vec3_dot(dir, normal))));
}

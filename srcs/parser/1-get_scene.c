/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:20:41 by lgertrud          #+#    #+#             */
/*   Updated: 2025/11/18 15:39:00 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 1 - fill Args struct with user input
// 2 - Arguments Parser, if all is ok, return struct scene
t_scene	*ft_get_scene(char *file)
{
	t_args	*args;
	t_scene	*scene;

	args = ft_allocate_args(file);
	scene = ft_parser(args);
	ft_free_args(args);
	return (scene);
}

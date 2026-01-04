/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.4-parser_obj_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:55:35 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/30 16:03:46 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*ft_parser_triangle(char *line)
{
	t_triangle	*tr;
	char		**args;
	int			count;

	count = count_parts(line, ' ');
	if (count != 5 && count != 6)
		return (NULL);

	args = ft_split(line, ' ');
	if (!args)
		return (NULL);

	if (ft_strncmp(args[0], "tr", 3) != 0
		|| !ft_parser_vec3(args[1])
		|| !ft_parser_vec3(args[2])
		|| !ft_parser_vec3(args[3])
		|| !ft_parser_rgb(args[4])
		|| (count == 6 && !ft_parser_ratio(args[5], 0, 1)))
	{
		ft_free_split(args);
		return (NULL);
	}

	tr = ft_calloc(1, sizeof(t_triangle));
	tr->a = ft_get_vec3(args[1]);
	tr->b = ft_get_vec3(args[2]);
	tr->c = ft_get_vec3(args[3]);
	tr->color = ft_get_rgb(args[4]);
	tr->reflectivity = ft_atod(args[5]);

	ft_free_split(args);
	return (tr);
}


void	*ft_parser_sphere(char *line)
{
	t_sphere	*sp;
	char		**args;

	if (count_parts(line, ' ') != 4 && count_parts(line, ' ') != 5)
		return (NULL);
	args = ft_split(line, ' ');
	if (!args)
		return (NULL);
	if (ft_strncmp(args[0], "sp", 3) != 0
		|| !ft_parser_vec3(args[1])
		|| !ft_float_format(args[2])
		|| !ft_parser_rgb(args[3])
		|| (count_parts(line, ' ') == 5
			&& !ft_parser_ratio(args[4], 0, 1)))
	{
		ft_free_split(args);
		return (NULL);
	}
	sp = ft_calloc(1, sizeof(t_sphere));
	sp->center = ft_get_vec3(args[1]);
	sp->diameter = ft_atod(args[2]);
	sp->color = ft_get_rgb(args[3]);
	sp->reflectivity = ft_atod(args[4]);
	ft_free_split(args);
	return (sp);
}

void	*ft_parser_plane(char *line)
{
	t_plane	*pl;
	char	**args;

	if (count_parts(line, ' ') != 4 && count_parts(line, ' ') != 5)
		return (NULL);
	args = ft_split(line, ' ');
	if (!args)
		return (NULL);
	if (ft_strncmp(args[0], "pl", 3) != 0
		|| !ft_parser_vec3(args[1])
		|| !ft_is_normalized(args[2]) || !ft_parser_rgb(args[3])
		|| (count_parts(line, ' ') == 5
			&& !ft_parser_ratio(args[4], 0, 1)))
	{
		ft_free_split(args);
		return (NULL);
	}
	pl = ft_calloc(1, sizeof(t_plane));
	pl->point = ft_get_vec3(args[1]);
	pl->normal = ft_get_vec3(args[2]);
	pl->normal = vec3_normalize(pl->normal);
	pl->color = ft_get_rgb(args[3]);
	pl->reflectivity = ft_atod(args[4]);
	ft_free_split(args);
	return (pl);
}

void	*ft_parser_cylinder(char *line)
{
	t_cylinder	*cy;
	char		**args;

	if (count_parts(line, ' ') != 6 && count_parts(line, ' ') != 7)
		return (NULL);
	args = ft_split(line, ' ');
	if (!args)
		return (NULL);
	if (ft_strncmp(args[0], "cy", 3) != 0
		|| !ft_parser_vec3(args[1])
		|| !ft_is_normalized(args[2])
		|| !ft_float_format(args[3]) || !ft_float_format(args[4])
		|| !ft_parser_rgb(args[5]) || (count_parts(line, ' ') == 7
			&& !ft_parser_ratio(args[6], 0, 1)))
		return (ft_free_split(args), NULL);
	cy = ft_calloc(1, sizeof(t_cylinder));
	cy->center = ft_get_vec3(args[1]);
	cy->normal = ft_get_vec3(args[2]);
	cy->normal = vec3_normalize(cy->normal);
	cy->diameter = ft_atod(args[3]);
	cy->height = ft_atod(args[4]);
	cy->color = ft_get_rgb(args[5]);
	cy->reflectivity = ft_atod(args[6]);
	ft_free_split(args);
	return (cy);
}

// return struct according to type.
void	*ft_get_obj(t_obj_type type, char *line)
{
	if (type == SPHERE)
		return (ft_parser_sphere(line));
	if (type == PLANE)
		return (ft_parser_plane(line));
	if (type == CYLINDER)
		return (ft_parser_cylinder(line));
	if (type == TRIANGLE)
		return (ft_parser_triangle(line));
	return (NULL);
}

// define the type of the object
t_obj_type	ft_get_type(char *line)
{
	if (!ft_strncmp(line, "sp ", 3))
		return (SPHERE);
	if (!ft_strncmp(line, "pl ", 3))
		return (PLANE);
	if (!ft_strncmp(line, "cy ", 3))
		return (CYLINDER);
	if (!ft_strncmp(line, "tr ", 3))
		return (TRIANGLE);
	return (INVALID);
}

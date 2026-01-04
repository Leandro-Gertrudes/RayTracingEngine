/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.3-parser_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:02:49 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/27 19:07:34 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// split str and return struct RGB.
t_rgb	ft_get_rgb(char *str)
{
	t_rgb	rgb;
	char	**vals;

	vals = ft_split(str, ',');
	rgb.r = ft_atoi(vals[0]);
	rgb.g = ft_atoi(vals[1]);
	rgb.b = ft_atoi(vals[2]);
	ft_free_split(vals);
	return (rgb);
}

// return a vector with 3 values.
t_vec3	ft_get_vec3(char *str)
{
	t_vec3	v;
	char	**parts;

	parts = ft_split(str, ',');
	v.x = ft_atod(parts[0]);
	v.y = ft_atod(parts[1]);
	v.z = ft_atod(parts[2]);
	ft_free_split(parts);
	return (v);
}

// translate \t to ' '
char	*ft_tab_to_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
	return (str);
}

double	ft_get_reflectivity(t_obj_type type, char *line)
{
	char	**args;
	int		count;
	double	reflect;

	args = ft_split(line, ' ');
	count = count_parts(line, ' ');
	if ((type == SPHERE && (count != 5 && count != 4))
		|| (type == PLANE && (count != 5 && count != 4))
		|| (type == CYLINDER && (count != 7 && count != 6))
		|| (type == TRIANGLE && (count != 5 && count != 6)))
	{
		ft_free_split(args);
		return (-1);
	}
	if ((type == SPHERE && count == 5)
		|| (type == PLANE && count == 5)
		|| (type == CYLINDER && count == 7)
		|| (type == TRIANGLE && count == 6))
	{
		if (!ft_parser_ratio(args[count - 1], 0, 1))
			return (ft_free_split(args), -1);
		reflect = ft_atod(args[count - 1]);
		ft_free_split(args);
		return (reflect);
	}
	ft_free_split(args);
	return (0.0);
}

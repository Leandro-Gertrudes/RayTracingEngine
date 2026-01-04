/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.1-parser_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:20:22 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/21 14:52:18 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// verified if all str value is a number
int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// 1 - verified if have 3 parts when we split with ","
// 2 - check if each part is a number and if it are between 0 - 255. 
int	ft_parser_rgb(char *str)
{
	char	**s;
	int		i;
	int		value;

	if (!str || str[ft_strlen(str) - 1] == ',')
		return (0);
	s = ft_split(str, ',');
	if (!s || count_parts(str, ',') != 3)
		return (ft_free_split(s), 0);
	i = -1;
	while (++i < 3)
	{
		if (!ft_is_number(s[i]))
			return (ft_free_split(s), 0);
		value = ft_atoi(s[i]);
		if (value < 0 || value > 255)
			return (ft_free_split(s), 0);
	}
	ft_free_split(s);
	return (1);
}

// 1- call float format for check if the argument is a float
// 2 - check if value are between min and max
int	ft_parser_ratio(char *str, double min, double max)
{
	float	value;

	if (!ft_float_format(str))
		return (0);
	value = ft_atod(str);
	if (value < min || value > max)
		return (0);
	return (1);
}

// 1 - verify if have 3 parts when we split with ",".
// 2 - check if all parts are in float format.
int	ft_parser_vec3(char *str)
{
	char	**p;

	if (!str || str[ft_strlen(str) - 1] == ',')
		return (0);
	p = ft_split(str, ',');
	if (!p || count_parts(str, ',') != 3 || !p[0] || !p[1] || !p[2])
	{
		ft_free_split(p);
		return (0);
	}
	if (!ft_float_format(p[0])
		|| !ft_float_format(p[1])
		|| !ft_float_format(p[2]))
	{
		ft_free_split(p);
		return (0);
	}
	ft_free_split(p);
	return (1);
}

// 1 - call parser vec3 for verify if str is a vector with 3 argument
// 2 - call parser ratio, check if is a float and between -1 and 1.
int	ft_is_normalized(char *str)
{
	char	**args;
	double	x;
	double	y;
	double	z;

	if (!ft_parser_vec3(str))
		return (0);
	args = ft_split(str, ',');
	if (!args)
		return (0);
	if (!ft_parser_ratio(args[0], -1, 1)
		|| !ft_parser_ratio(args[1], -1, 1)
		|| !ft_parser_ratio(args[2], -1, 1))
	{
		ft_free_split(args);
		return (0);
	}
	x = ft_atod(args[0]);
	y = ft_atod(args[1]);
	z = ft_atod(args[2]);
	ft_free_split(args);
	if (x == 0.0 && y == 0.0 && z == 0.0)
		return (0);
	return (1);
}

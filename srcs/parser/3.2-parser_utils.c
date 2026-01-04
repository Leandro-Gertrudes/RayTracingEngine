/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.2-parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:13:09 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/15 17:00:18 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// verify if is a float and if are between 0 - 180.
int	ft_parse_fov(char *str)
{
	float	fov;

	if (!ft_float_format(str))
		return (0);
	fov = ft_atod(str);
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}

// verify if is a digit and if have 0 or 1 point
static int	ft_float_format_util(const char *str)
{
	int	i;
	int	digits;
	int	dots;

	i = 0;
	digits = 0;
	dots = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digits++;
		else if (str[i] == '.')
		{
			if (++dots > 1 || !str[i + 1])
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (digits > 0);
}

// verify if have a signal, and call util
int	ft_float_format(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	return (ft_float_format_util(&str[i]));
}

// used for free scructs
void	**ft_alloc_arraystruc(int count, size_t type_size)
{
	void	**arr;
	int		i;

	if (count <= 0)
		return (NULL);
	arr = ft_calloc(count + 1, sizeof(void *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		arr[i] = ft_calloc(1, type_size);
		if (!arr[i])
		{
			while (--i >= 0)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		i++;
	}
	arr[count] = NULL;
	return (arr);
}

char	*ft_is_double(t_args *args, char *target, char *line, int fd)
{
	if (target)
	{
		free(line);
		ft_free_args(args);
		close(fd);
		ft_exit(ERROR_SCENE, 2);
	}
	return (ft_strdup(line));
}

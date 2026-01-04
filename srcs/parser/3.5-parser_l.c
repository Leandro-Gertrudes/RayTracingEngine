/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.5-parser_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:30:56 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/12/14 16:32:44 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_valid_light_line(char *line)
{
	char	**args;

	if (count_parts(line, ' ') != 4)
		return (0);
	args = ft_split(line, ' ');
	if (!args || !args[0] || !args[1] || !args[2] || !args[3]
		|| ft_strncmp(args[0], "L", ft_strlen(args[0])) != 0
		|| !ft_parser_vec3(args[1])
		|| !ft_parser_ratio(args[2], 0, 1)
		|| !ft_parser_rgb(args[3]))
	{
		ft_free_split(args);
		return (0);
	}
	ft_free_split(args);
	return (1);
}

static void	fill_light(t_light *light, char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	light->position = ft_get_vec3(args[1]);
	light->ratio = ft_atod(args[2]);
	light->color = ft_get_rgb(args[3]);
	ft_free_split(args);
}

t_light	**ft_parser_l(char **input, int count_light)
{
	t_light	**light;
	int		i;

	light = (t_light **)ft_alloc_arraystruc(count_light, sizeof(t_light));
	if (!light)
		return (NULL);
	i = 0;
	while (i < count_light && input[i])
	{
		if (!is_valid_light_line(input[i]))
			return (ft_free_arraystruc((void **)light, count_light), NULL);
		fill_light(light[i], input[i]);
		i++;
	}
	return (light);
}

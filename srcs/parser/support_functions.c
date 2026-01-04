/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_functions_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:46:12 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/21 14:57:17 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_is_rt(char *file)
{
	size_t	len;

	if (!file)
		return (1);
	len = ft_strlen(file);
	if (len < 3)
		return (1);
	if (ft_strncmp(file + len - 3, ".rt", 3) != 0)
		return (1);
	return (0);
}

int	ft_get_fd(char *file, int *count)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(count);
		ft_exit(ERROR_FILE, 2);
	}
	return (fd);
}

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_args(t_args *args)
{
	if (args->ambient_light)
		free(args->ambient_light);
	if (args->camera)
		free(args->camera);
	if (args->light)
		ft_free_split(args->light);
	if (args->objects)
		ft_free_split(args->objects);
	free(args);
}

void	init_counts(t_args *args, int *count)
{
	args->ambient_light = NULL;
	args->camera = NULL;
	args->light_count = count[0];
	args->obj_count = count[1];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-allocate_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:08:27 by lgertrud          #+#    #+#             */
/*   Updated: 2025/12/29 18:12:39 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_is_object(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] == ' ')
		i++;
	if (!ft_strncmp(&line[i], "sp ", 3))
		return (1);
	if (!ft_strncmp(&line[i], "pl ", 3))
		return (1);
	if (!ft_strncmp(&line[i], "cy ", 3))
		return (1);
	if (!ft_strncmp(&line[i], "tr ", 3))
		return (1);
	return (0);
}

static void	ft_count_line(char *line, int *count)
{
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(line, " \t\r\b\n");
	if (!trimmed)
		return ;
	ft_tab_to_space(trimmed);
	i = 0;
	while (trimmed[i] == ' ')
		i++;
	if (!ft_strncmp(&trimmed[i], "L ", 2))
		count[0]++;
	else if (ft_is_object(trimmed))
		count[1]++;
	free(trimmed);
}

static int	*ft_count(char *file)
{
	int		*count;
	int		fd;
	char	*line;

	count = ft_calloc(2, sizeof(int));
	if (!count)
		ft_exit(ERROR_MALLOC, 2);
	fd = ft_get_fd(file, count);
	line = get_next_line(fd);
	while (line)
	{
		ft_count_line(line, count);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

// 1 - set args NULL
// 2 - strtrim for erase spaces
// 3 - fill scruct according the type of the lines
// 4 - Cam and ambient light can't duplicate
// if invalid argument, call ft_is_double for free and exit
void	ft_put_argument(t_args *args, int fd)
{
	int		i;
	int		k;
	char	*line;
	char	*trimmed;

	i = 0;
	k = 0;
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\r\b\n");
		ft_tab_to_space(trimmed);
		if (!ft_strncmp(trimmed, "A ", 2))
			args->ambient_light = ft_is_double(args,
					args->ambient_light, trimmed, fd);
		else if (!ft_strncmp(trimmed, "C ", 2))
			args->camera = ft_is_double(args, args->camera, trimmed, fd);
		else if (!ft_strncmp(trimmed, "L ", 2))
			args->light[k++] = ft_strdup(trimmed);
		else if (ft_is_object(trimmed))
			args->objects[i++] = ft_strdup(trimmed);
		else if (trimmed[0] != '\n' && trimmed[0] != '#' && trimmed[0] != '\0')
			ft_is_double(args, "invalid", trimmed, fd);
		line = free_and_getline(line, trimmed, fd);
	}
}

// 1- call ft_count to get number of the Lights and objets
// 2 - allocate memory for struct and arrays-arrays
// 3 - call ft_put_argument to fill struct
t_args	*ft_allocate_args(char *file)
{
	t_args	*args;
	int		*count;
	int		fd;

	count = ft_count(file);
	args = ft_calloc(sizeof(t_args), 1);
	if (!args)
		ft_exit(ERROR_MALLOC, 2);
	init_counts(args, count);
	free(count);
	args->objects = ft_calloc(sizeof(char *), (args->obj_count + 1));
	if (!args->objects)
		ft_exit(ERROR_MALLOC, 2);
	args->objects[args->obj_count] = NULL;
	if (args->light_count > 0)
	{
		args->light = ft_calloc(sizeof(char *), (args->light_count + 1));
		if (!args->light_count)
			ft_exit(ERROR_MALLOC, 2);
		args->light[args->light_count] = NULL;
	}
	fd = ft_get_fd(file, NULL);
	ft_put_argument(args, fd);
	close(fd);
	return (args);
}

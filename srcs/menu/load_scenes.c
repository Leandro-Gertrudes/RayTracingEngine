/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:49:48 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/11 10:51:47 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_rt_file(char *name)
{
	int	len;

	len = strlen(name);
	if (len < 4)
		return (0);
	return (strcmp(name + len - 3, ".rt") == 0);
}


static int	count_rt_files(char *path)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(path);
	if (!dir)
		return (0);
	while ((entry = readdir(dir)))
	{
		if (is_rt_file(entry->d_name))
			count++;
	}
	closedir(dir);
	return (count);
}


char	**load_scenes(char *path, int *scene_count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**scenes;
	int				i;

	*scene_count = count_rt_files(path);
	if (*scene_count == 0)
		return (NULL);

	scenes = malloc(sizeof(char *) * (*scene_count));
	if (!scenes)
		return (NULL);

	dir = opendir(path);
	if (!dir)
		return (NULL);

	i = 0;
	while ((entry = readdir(dir)))
	{
		if (is_rt_file(entry->d_name))
		{
			scenes[i] = strdup(entry->d_name);
			i++;
		}
	}
	closedir(dir);
	return (scenes);
}

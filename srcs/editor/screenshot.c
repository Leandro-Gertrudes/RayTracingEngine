/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:36:32 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/19 13:03:32 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

#include <unistd.h>
#include <sys/stat.h>

void screenshots(t_scene *scene)
{
    char filename[100];
    int id = 0;

    mkdir("screenshots", 0777);

    while (1)
    {
        sprintf(filename, "screenshots/screenshot_%04d.ppm", id);
        if (access(filename, F_OK) != 0)
            break;
        id++;
    }

    save_image_ppm(scene->image, filename);
    printf("Screenshot saved: %s\n", filename);
}

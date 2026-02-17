/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:54:40 by lgertrud          #+#    #+#             */
/*   Updated: 2026/02/17 17:42:14 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int close_window_demo(void *mlx_ptr, void *win_ptr)
{
    if (win_ptr)
        mlx_destroy_window(mlx_ptr, win_ptr);
    if (mlx_ptr)
    {
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
    }
    return (0);
}

void execute_scene(char *file_path, void *mlx, void *win)
{
    t_scene *scene;

    scene = ft_get_scene(file_path);
    if (!scene)
        return;

    scene->disp.mlx = mlx;
    scene->disp.win = win;

    scene->disp.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    scene->disp.addr = mlx_get_data_addr(
            scene->disp.img,
            &scene->disp.bpp,
            &scene->disp.line_length,
            &scene->disp.endian);

    render_scene(scene);

    mlx_put_image_to_window(mlx, win, scene->disp.img, 0, 0);

    sleep(3);

    mlx_destroy_image(mlx, scene->disp.img);
    ft_free_scene(scene);
}

void ft_demo(void)
{
	void	*mlx;
    void	*win;
    DIR             *dir;
    struct dirent   *entry;
    char            full_path[1024];

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT demo");
    dir = opendir("scenes/.demo");
    if (!dir)
    {
        perror("cannot open /scene/.demo/");
        return;
    }

	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 ||
			strcmp(entry->d_name, "..") == 0)
			continue;

		if (strstr(entry->d_name, ".rt"))
		{
			printf("running: %s\n", entry->d_name);

			snprintf(full_path, sizeof(full_path),
					"scenes/.demo/%s", entry->d_name);

			execute_scene(full_path, mlx, win);
		}
	}
	closedir(dir);
	close_window_demo(mlx, win);
	printf("running: demo video\n");
	system("vlc --quiet videos/demo.mp4 > /dev/null 2>&1 &");
	printf("\n");
	printf("=====================================\n");
	printf("        Thanks!\n");
	printf("\n");
	printf("        miniRT by Leandro Gertrudes\n");
	printf("        github.com/leandro-gertrudes\n");
	printf("=====================================\n\n");

}

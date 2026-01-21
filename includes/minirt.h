/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:42:30 by lgertrud          #+#    #+#             */
/*   Updated: 2026/01/21 17:40:50 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "libft.h"
# include <pthread.h>
# include <stdbool.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../X11/X.h"
# include "../X11/keysym.h"

# define M_PI	3.14159265358979323846
# define ERROR_PARAM "Error\nUsage: ./minirt <file.rt>"
# define ERROR_FRAMES "Error\nUsage: ./minirt <file.rt> --frames <numFirstFrame> <numLastFrame>"
# define ERROR_FILE "Error\nCannot open this found."
# define ERROR_MALLOC "Error\nCannot allocate memmory."
# define ERROR_SCENE "Error\ninvalid scene."
# define THREAD_COUNT 20
# define WIDTH 1400
# define HEIGHT 800

# define KEYPRESS        2
# define KEYRELEASE      3
# define BUTTONPRESS     4
# define BUTTONRELEASE   5
# define MOTIONNOTIFY    6
# define DESTROYNOTIFY   17
# define EXPOSE          12

typedef enum e_mode {
    DEFAULT,
    ANIMATE,
    SAVE_FRAMES
} t_mode;

extern t_mode 			g_mode;
extern int				startFrame;
extern int				endFrame;
extern bool				low_render;
extern bool				g_edit;
extern double			g_move;


enum e_event_mask
{
	KEYPRESSMASK = 1L << 0,
	KEYRELEASEMASK = 1L << 1,
	BUTTONPRESSMASK = 1L << 2,
	STRUCNOTIFYMASK = 1L << 17
};

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_camdata
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	double	fov_rad;
	double	viewport_width;
	double	viewport_height;
}	t_camdata;

typedef struct s_args
{
	char	*ambient_light;
	char	*camera;
	char	**light;
	int		light_count;
	char	**objects;
	int		obj_count;
}	t_args;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_ambient_light
{
	double	ratio;
	t_rgb	color;
}	t_ambient_light;

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		vector;
	t_camdata	camdata;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	double	ratio;
	t_rgb	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3		center;
	double		diameter;
	t_rgb		color;
	double		reflectivity;
}	t_sphere;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_rgb		color;
	double		reflectivity;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		normal;
	double		diameter;
	double		height;
	t_rgb		color;
	double		reflectivity;
}	t_cylinder;

typedef struct s_triangle
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_rgb	color;
	double	reflectivity;
}	t_triangle;


typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	TRIANGLE,
	INVALID
}	t_obj_type;

typedef struct s_object
{
	t_obj_type	type;
	void		*data;
}	t_object;

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_length;
	int		endian;
}	t_graphics;

typedef struct s_time
{
	double	current;
	double	delta;
}	t_time;


typedef struct s_anim_light
{
	t_light	*light;
	double	radius;
	double	speed;
	t_vec3	center;
}	t_anim_light;


typedef struct s_anim_camera
{
	t_camera	*cam;
	double		radius;
	double		speed;
}	t_anim_camera;

typedef struct s_image
{
	int		width;
	int		height;
	t_rgb	*pixels;
}	t_image;

typedef struct s_scene
{
	t_ambient_light	*ambient;
	t_camera		*camera;
	t_light			**lights;
	int				light_count;
	t_object		**objects;
	int				object_count;
	t_graphics		disp;
	t_time			time;
	t_anim_light	anim_light;
	t_anim_camera	anim_camera;
	t_image			*image;
	t_object		obj_edit;
}	t_scene;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

// -----Object intersection

typedef struct s_hcy
{
	t_vec3	oc;
	t_vec3	d;
	t_vec3	n;
	double	a;
	double	b;
	double	c;
	double	discr;
}	t_cycalc;

typedef struct s_hsp
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sqrt_d;
	double	t0;
	double	t1;

}	t_hsp;

typedef struct s_hit
{
	double		t;
	void		*object;
	int			type;
}	t_hit;

typedef struct s_sphere_hit
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sqrt_d;
	double	t0;
	double	t1;
}	t_sphere_hit;

typedef struct s_cylinder_hit
{
	t_vec3	oc;
	t_vec3	d;
	t_vec3	w;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	t_vec3	p;
	double	h;
}	t_cylinder_hit;

typedef struct s_render_st
{
	t_vec3	point;
	t_vec3	normal;
	t_rgb	local_color;
	t_rgb	reflected_color;
	t_ray	reflected_ray;
}	t_render_st;

typedef struct s_thread_data
{
	t_scene	*scene;
	int		y_start;
	int		y_end;
}	t_thread_data;

void	ft_minirt(char	*file);

// ============ Parser ============

void			ft_exit(char *message, int code);
int				ft_is_rt(char *file);
t_scene			*ft_get_scene(char *file);
int				ft_get_fd(char *file, int *count);
void			ft_put_argument(t_args *args, int fd);
void			init_counts(t_args *args, int *count);
void			ft_free_args(t_args *args);
t_scene			*ft_parser(t_args *args);
t_args			*ft_allocate_args(char *file);
char			*ft_is_double(t_args *args, char *target, char *line, int fd);
char			*free_and_getline(char *line, char *trimmed, int fd);
t_ambient_light	*ft_parser_al(char *input);
t_camera		*ft_parser_c(char *input);
t_light			**ft_parser_l(char **input, int count_light);
t_object		**ft_parser_ob(char **input, int count_objects);
t_rgb			ft_get_rgb(char *str);
int				ft_parser_rgb(char *str);
t_camera		*ft_parser_c(char *input);
int				ft_parser_ratio(char *str, double min, double max);
int				ft_is_normalized(char *str);
int				ft_is_number(char *str);
int				ft_parser_vec3(char *str);
t_vec3			ft_get_vec3(char *str);
int				ft_float_format(const char *str);
int				ft_parse_fov(char *str);
void			**ft_alloc_arraystruc(int count, size_t type_size);
void			ft_free_arraystruc(void **arr, int count);
void			ft_free_scene(t_scene *scene);
void			ft_free_object(t_object *obj);
void			ft_free_split(char **arr);
void			*ft_get_obj(t_obj_type type, char *line);
t_obj_type		ft_get_type(char *line);
char			*ft_tab_to_space(char *str);
void			ft_free_objects_struc(t_object **arr, int count);
double			ft_get_reflectivity(t_obj_type type, char *line);

// ============ Vectors ============

t_vec3			vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3			atovec3(char **vec);
bool			vec3_cmp(t_vec3 vec1, t_vec3 vec2);
double			vec3_cos(t_vec3 vec1, t_vec3 vec2);
t_vec3			vec3_cross(t_vec3 vec1, t_vec3 vec2);
double			vec3_dot(t_vec3 vec1, t_vec3 vec2);
double			vec3_len(t_vec3 vec);
t_vec3			vec3_new(double x, double y, double z);
t_vec3			vec3_normalize(t_vec3 vec);
t_vec3			vec3_scale(t_vec3 vec1, double scalar);
t_vec3			vec3_sub(t_vec3 vec1, t_vec3 vec2);
t_vec3			reflect(t_vec3 l, t_vec3 n);

// ============ ray ============
t_camdata		ft_compute_camera(t_camera cam, int width, int height);
t_ray			ft_ray(t_vec3 o, t_vec3 d);
t_ray			make_ray(int x, int y, t_scene *scene);

// ==== object intersection ====
bool			hit_cylinder(t_ray ray, t_cylinder *cy, double *t);
bool			hit_plane(t_ray ray, t_plane *pl, double *t);
bool			hit_sphere(t_ray ray, t_sphere *sp, double *t);
bool			hit_objects(t_scene *scene, t_ray ray, t_hit *hit);
bool			hit_triangle(t_ray ray, t_triangle *tr, double *t);
t_vec3			triangle_normal(t_triangle *tr);

// ==== lighting ====
t_rgb			apply_ambient(t_scene *sc, t_rgb obj_color);
bool			is_in_shadow(t_scene *sc, t_vec3 point, t_light *light);
t_rgb			apply_diffuse(t_vec3 normal, t_vec3 light_dir,
					t_light *light, t_rgb obj_color);
t_rgb			rgb_add(t_rgb a, t_rgb b);
t_rgb			rgb_clamp(t_rgb c);
int				rgb_to_int(t_rgb color);
t_rgb			shade_hit(t_scene *sc, t_hit *hit, t_vec3 point, t_vec3 normal);
t_rgb			vec3_rgb_scale(t_rgb c, double s);
t_vec3			vec3_reflect(t_vec3 dir, t_vec3 normal);

// ==== normal ====
t_vec3			get_normal(t_hit *hit, t_vec3 point);

// ==== render ====
void			put_pixel(t_scene *scene, int x, int y, int color);
void			render_scene(t_scene *scene);
double			get_reflectivity(t_hit *hit);
void			*render_thread(void *arg);
t_rgb			compute_pixel_color(t_scene *scene, t_ray ray, int depth);
t_rgb			apply_specular(
				t_vec3 normal,
				t_vec3 light_dir,
				t_vec3 view_dir,
				t_light *light,
				double shininess);
void			display_image(t_scene *scene);
void			low_render_scene(t_scene *scene);
void			render_transition(t_scene *scene);
t_rgb			get_pixel(t_scene *scene, int x, int y);

// ==== graphics ====
int				key_press(int keycode, t_scene *scene);
int				close_window(t_scene *scene);
void			ft_init_graphics(t_scene *scene);

// ==== animation ====

void	update_time(t_scene *sc);
void	init_anim_light(t_scene *sc);
double	get_time_sec(void);
void	update_anim_light(t_scene *sc);
int		render_loop(void *param);
void	update_scene(t_scene *sc);
void	update_anim_camera(t_scene *sc);
void	init_anim_camera(t_scene *sc);
int		render_loop(void *param);
void	save_image_ppm(t_image *img, char *filename);
void	render_animation(t_scene *sc);
t_image	*image_create(int width, int height);
void	image_clear(t_image *img);


// ==== edit ====

void			move_obj(t_scene *scene, t_object *obj_edit, int keycode);
void			draw_hud_obj(t_scene *scene, t_obj_type type, void *data);
void			show_infos(t_scene *scene, t_obj_type type,
					void *data, int x, int line_y);
int				mouse_hook(int button,int x, int y, t_scene *scene);
void			draw_hud(t_scene *scene);
int				move_camera(t_scene *scene, int keycode);
void 			update_move(int keycode);

#endif

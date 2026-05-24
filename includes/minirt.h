/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:42:30 by lgertrud          #+#    #+#             */
/*   Updated: 2026/05/24 15:14:21 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRTH
# define MINIRTH

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <math.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"
# include "../X11/X.h"
# include "../X11/keysym.h"

# define ERROR_PARAM "Error: wrong params\nUsage: ./minirt --help"
# define ERROR_FRAMES "Error\nUsage: ./minirt <file.rt> --frames <numFirstFrame> <numLastFrame>"
# define ERROR_FILE "Error\nCannot open this found."
# define ERROR_MALLOC "Error\nCannot allocate memmory."
# define ERROR_SCENE "Error\ninvalid scene."

# define M_PI	3.14159265358979323846
# define THREAD_COUNT 16
# define WIDTH 1400
# define HEIGHT 800

# define KEYPRESS        2
# define KEYRELEASE      3
# define BUTTONPRESS     4
# define BUTTONRELEASE   5

#define KEY_ESQ				65307
#define KEY_UP				65362
#define KEY_F1				65470
#define KEY_DOWN			65364
#define KEY_LEFT			65361
#define KEY_RIGHT			65363
#define KEY_ENTER			65293
#define KEY_RIGTH_ENTER		65421
#define KEY_LEFT_SHIFT		65505
#define KEY_LEFT_CTRL		65507
#define KEY_CAPSLOCK		65509 
#define KEY_TAB				65289 
#define KEY_BACKSPACE		65288
#define KEY_PLUS			61
#define KEY_MINUS			45
#define KEY_SPACE			32
#define KEY_W				119
#define KEY_A				97
#define KEY_S				115
#define KEY_D				100
#define KEY_Q				113
#define KEY_E				101
#define KEY_NUMBER1			49
#define KEY_NUMBER2			50
#define KEY_NUMBER3			51
#define KEY_NUMBER4			52
#define KEY_NUMBER5			53
#define KEY_Z				122
#define KEY_C				99
#define KEY_I				105
#define KEY_O				111
#define KEY_J				106
#define KEY_K				107
#define KEY_N				110
#define KEY_M				109
#define KEY_T				116
#define KEY_P				112

// ----Global variables
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
extern bool				g_edit_color;
extern bool				g_edit_light;
extern double			g_scale_edit;

// ----structs scene

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

extern t_light			*g_low_light;

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
	LIGHT,
	INVALID
}	t_obj_type;

typedef struct s_object
{
	t_obj_type	type;
	void		*data;
}	t_object;


// ----mlx
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


// --animation
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
	double	phase;
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

// ---scene, main struct
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


// --render structs
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

//menu
typedef struct s_menu
{
	void	*mlx;
	void	*win;

	char	**scenes;
	int		scene_count;

	int		scene_selected;

	int		current_page;
	int		scenes_per_page;

	int		mode_selected;
}	t_menu;



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
int				ft_help(void);
int				ft_commands(void);

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
void			draw_bw_overlay(t_scene *scene, double strength);
t_rgb			get_pixel(t_scene *scene, int x, int y);
void			image_put_pixel(t_image *img, int x, int y, t_rgb color);

// ==== graphics ====
int				key_press(int keycode, void *scene);
int				close_window(t_scene *scene);
void			ft_init_graphics(t_scene *scene);

// ==== animation ====

int				render_loop(void *param);
void			update_scene(t_scene *sc);
int				render_loop(void *param);
void			save_image_ppm(t_image *img, char *filename);
void			render_animation(t_scene *sc);
void			update_time(t_scene *sc);
t_image			*image_create(int width, int height);
void			image_clear(t_image *img);
void			update_dragon(t_scene *scene);
void			update_diamond_rotation(t_scene *sc);
void			update_billiard(t_scene *sc);
void			update_falling_sphere(t_scene *sc);
void			update_anim_spheres(t_scene *sc);

// ==== edit mode ====

void			edit_obj(t_scene *scene, t_object *obj_edit, int keycode);
void			add_object(t_scene *scene, int keycode);
void 			remove_obj(t_scene *scene);
void			move_obj_xy(t_scene *scene, t_object *obj_edit, int keycode);
void			move_obj_z(t_scene *scene, t_object *obj_edit, int button);
void			move_obj_angule(t_scene *scene, t_object *obj_edit, int button);
void			size_obj(t_scene *scene, t_object *obj_edit, int keycode);
void			color_obj_edit(t_scene *scene, t_object *obj_edit, int keycode);
void			add_light(t_scene *scene);
void			remove_light(t_scene *scene);
void 			reflectivity_update(t_scene *scene, t_object *obj_edit, int keycode);
void			draw_hud_obj(t_scene *scene, t_obj_type type, void *data);
void			show_infos(t_scene *scene, t_obj_type type,
					void *data, int x, int line_y);
int				mouse_hook(int button,int x, int y, void *scene);
void			draw_hud(t_scene *scene);
int				move_camera(t_scene *scene, int keycode);
void 			update_move(int keycode);
void 			low_light(t_scene *scene, t_hit *hit, t_ray ray, double *t);
void			select_light(t_scene *scene, int keycode);
void			position_light(t_scene *scene);
void			save_scene(t_scene *scene);
void			screenshots(t_scene *scene);

// ==== menu ====

void	menu(void);
char	**load_scenes(char *path, int *scene_count);
void    header(void);

#endif
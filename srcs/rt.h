/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:10:09 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/23 20:07:43 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define PRESET_HEIGHT 800
# define PRESET_WIDTH 1600
# define PRESET_ANTIALIASING 1

# define OBJ_CAM "cam"
# define OBJ_LIGHT "light"
# define OBJ_SPHERE "sphere"
# define OBJ_CYLINDER "cylinder"
# define OBJ_CONE "cone"
# define OBJ_PLAN "plan"
# define OBJ_ALIASING "anti-aliasing"
# define OBJ_HEIGHT "height"
# define OBJ_WIDTH "width"

typedef enum	e_obj
{
	CAM = 1,
	SPHERE,
	CYLINDER,
	CONE,
	PLAN,
	LIGHT,
	ANTIALIASING,
	HEIGHT,
	WIDTH
}				t_obj;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img_render;
	void	*img_display;
	char	*data_render;
	char	*data_display;
	int		endian;
	int		line;
	int		bpp;
}				t_mlx;

typedef struct	s_size
{
	float	h;
	float	w;
}				t_size;

typedef struct	s_screen
{
	float	length;
	t_size	display;
	t_size	render;
	float	rayon;
	int		upscale;
}				t_screen;

typedef struct	s_pos
{
	float	x;
	float	y;
	float	z;
}				t_pos;

typedef struct	s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct	s_hsl
{
	float	hue;
	float	saturation;
	float	lightness;
}				t_hsl;

typedef struct	s_ray
{
	int		line;
	t_size	go;
	float	inter;
	float	inter_light;
	float	len;
	float	delta;
	float	delta_light;
}				t_ray;

typedef struct	s_data
{
	t_obj			obj;
	t_pos			pos;
	t_pos			angle;
	float			radius;
	t_pos			vect;
	int				rgb[3];
	struct s_data	*next;
}				t_data;

typedef struct	s_env
{
	t_mlx		*mlx;
	t_screen	screen;
	t_ray		ray;
	t_pos		pos;
	t_pos		cam;
	t_pos		normal;
	t_pos		vect;
	t_pos		shadowray;
	t_pos		inter;
	t_rgb		color;
	int			object;
	float		a;
	float		b;
	float		c;
	float		lenght;
	float		heart_sphere[3];
	float		heart_plan[4];
	float		angle[3];
	t_pos		angle_ob;
	float		light;
	float		light_bis;
}				t_env;

t_data	*get_infos(t_env *e, int fd);
t_data	*init_list_with_cam(char *line);
t_data	*collect_info_about_obj(t_data *obj, char **tab, t_obj type);
void	fill_list_with_obj(t_data **list, char **tab, t_obj obj, int line);

int		set_mlx(t_env *e, t_data *scene);

int		key_hook(int keycode);
int		expose_hook(t_env *e);
int		mlx_put_px_img_render(t_env *e, int x, int y, int color);
int		mlx_get_px_img_render(t_env *e, int x, int y);
int		mlx_put_px_img_display(t_env *e, int x, int y, int color);

int		raytracer(t_env *e, t_data **scene);
int		size_ray(t_env *e);
int		id_object(t_env *e, t_data *scene);

int		check_light(t_env *e, t_data **scene);
void	size_raylight(t_env *e, t_data *scene);
int		id_object_for_light(t_env *e, t_data **scene);

int		rt_sphere(t_env *e, t_data *scene);
int		get_inter_to_print(t_env *e, t_data *scene);
int		size_light_on_sphere(t_env *e, t_data *scene);
int		get_light_to_print(t_env *e);
void	lightsphere(t_env *e);

int		rt_plan(t_env *e, t_data *scene);
int		lightplan(t_env *e);
int		size_light_on_plan(t_env *e, t_data *scene);

void	rt_cone(t_env *e, t_data *scene);
int		get_cone_to_print(t_env *e, t_data *scene);
void	lightcone(t_env *e, t_data *scene);
int		size_light_on_cone(t_env *e, t_data *scene);

void	rt_cylinder(t_env *e, t_data *scene);
int		get_cyl_to_print(t_env *e, t_data *scene);
void	lightcylinder(t_env *e);
int		size_light_on_cyl(t_env *e, t_data *scene);

void	*safe_malloc(size_t size);
int		count_array(char **array);
char	*sanityze_str(char *str);
int		min_three(int a, int b, int c);
int		max_three(int a, int b, int c);

char	**gimme_obj_list(void);
t_obj	parse_object(char *input);
void	set_options(char **split, t_env *e, t_obj obj, int line);

void	*display_parse_error(t_obj type, int line);
void	display_ignored_line(int line);
int		return_parse_error(void);

t_data	*set_cam(char **input, int line);
t_data	*get_cam(void);

void	rt_rotate(t_data *scene, t_pos *v, t_pos *o, t_env *e);
void	downscale(t_env *e);

t_rgb	pixel_to_rgb(int pixel);
int		rgb_to_pixel(t_rgb color);

void	rt_rotate2(t_pos *v, t_pos *o, t_env *e);
void	rt_rotate_y(t_pos *a, t_pos *v, t_pos *o, t_env *e);
void	rt_rotate_x(t_pos *a, t_pos *v, t_pos *o, t_env *e);
void	rt_rotate_z(t_pos *a, t_pos *v, t_pos *o, t_env *e);

#endif /* !RT_H */

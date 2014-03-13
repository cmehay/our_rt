/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:10:09 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/13 16:01:39 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define HEIGHT 400
# define WIDTH 600

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		endian;
	int		line;
	int		bpp;
}				t_mlx;

typedef struct	s_screen
{
	float	length;
	float	width;
	float	height;
	float	rayon;
}				t_screen;

typedef struct	s_pos
{
	float	x;
	float	y;
	float	z;
}				t_pos;

typedef struct	s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

typedef struct	s_ray
{
	int		line;
	float	go_w;
	float	go_h;
	float	inter;
	float	inter_light;
	float	len;
	float	delta;
	float	delta_light;
}				t_ray;

typedef struct s_data	t_data;

struct	s_data
{
	char	*what;
	t_pos	pos;
	t_pos	angle;
	float	radius;
	t_pos	vect;
	int		rgb[3];
	t_data	*next;
};

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
	t_color		color;
	int			object;
	float		a;
	float		b;
	float		c;
	float		lenght;
	float		heart_sphere[3];
	float		heart_plan[4];
	float		angle[3];
}				t_env;

t_data	*get_infos(int fd);
t_data	*init_list_with_cam(t_data **list, char *line);
t_data	*collect_info_about_obj(t_data *node, char **tab);
int		fill_list_with_obj(t_data **list, char *line);

int		set_mlx(t_env *e, t_data *scene);
int		key_hook(int keycode);
int		expose_hook(t_env *e);
int		mlx_put_px_img(t_env *e, int x, int y, int color);

int		raytracer(t_env *e, t_data **scene);
int		size_ray(t_env *e);
int		id_object(t_env *e, t_data *scene);

int		check_light(t_env *e, t_data **scene);
void	size_raylight(t_env *e, t_data *scene);
void	id_object_for_light(t_env *e, t_data **scene);

int		rt_sphere(t_env *e, t_data *scene);
int		get_inter_to_print(t_env *e, t_data *scene);
void	size_light_on_sphere(t_env *e, t_data *scene);
void	get_light_to_print(t_env *e);
void	lightsphere(t_env *e);

int		rt_plan(t_env *e, t_data *scene);
int		lightplan(t_env *e);
void	size_light_on_plan(t_env *e, t_data *scene);

void	rt_cone(t_env *e, t_data *scene);
int		get_cone_to_print(t_env *e, t_data *scene);
void	size_light_on_cone(t_env *e, t_data *scene);

void	rt_cylinder(t_env *e, t_data *scene);
int		get_cyl_to_print(t_env *e, t_data *scene);
void	lightcylinder(t_env *e);
void	size_light_on_cyl(t_env *e, t_data *scene);

void	*safe_malloc(size_t size);


#endif /* !RT_H */

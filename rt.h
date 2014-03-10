/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:10:09 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/10 23:52:08 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

# define HEIGHT 900
# define WIDTH 1800

typedef struct		s_data
{
	char			*what;
	float			x;
	float			y;
	float			z;
	int				angle_x;
	int				angle_y;
	int				angle_z;
	float			radius;
	float			vectx;
	float			vecty;
	float			vectz;
	int				rgb[3];
	struct s_data	*next;
}					t_data;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				endian;
	int				bpp;
	int				line;
	float			go_w;
	float			go_h;
	float			inter;
	float			inter_light;
	float			len;
	float			screen_length;
	float			screen_width;
	float			screen_height;
	float			screen_rayon;
	float			delta;
	float			delta_light;
	float			x;
	float			y;
	float			z;
	float			cam_x;
	float			cam_y;
	float			cam_z;
	float			normale_x;
	float			normale_y;
	float			normale_z;
	float			vect_x;
	float			vect_y;
	float			vect_z;
	float			shadowray_x;
	float			shadowray_y;
	float			shadowray_z;
	int				red;
	int				green;
	int				blue;
	int				object;
	float			a;
	float			b;
	float			c;
	float			interx;
	float			intery;
	float			interz;
	float			lenght;
	float			heart_sphere[3];
	float			heart_plan[4];
	float			angle[3];
}					t_env;

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

#endif /* !RT_H */

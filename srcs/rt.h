/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 07:10:09 by sde-segu          #+#    #+#             */
/*   Updated: 2014/03/26 21:38:37 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "rt_structs.h"

# define PRESET_HEIGHT 800
# define PRESET_WIDTH 1600
# define PRESET_ANTIALIASING 1

# define OBJ_CAM "cam"
# define OBJ_LIGHT "light"
# define OBJ_SPHERE "sphere"
# define OBJ_CYLINDER "cylinder"
# define OBJ_CONE "cone"
# define OBJ_PLAN "plan"
# define OBJ_DSPHERE "dsphere"
# define OBJ_DCYLINDER "dcylinder"
# define OBJ_DCONE "dcone"
# define OBJ_ALIASING "anti-aliasing"
# define OBJ_HEIGHT "height"
# define OBJ_WIDTH "width"

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
int		id_object_for_light(t_env *e, t_data **scene, t_data *light);

int		rt_demi_sphere(t_env *e, t_data *scene);
int		get_demi_to_print(t_env *e, t_data *scene);
int		size_light_on_demi_sphere(t_env *e, t_data *scene, t_data light);
void	lightdemisphere(t_env *e, t_data light);
int		get_light_to_print_demi(t_env *e, t_data *scene, t_data light);

int		rt_sphere(t_env *e, t_data *scene);
int		get_inter_to_print(t_env *e, t_data *scene);
int		size_light_on_sphere(t_env *e, t_data *scene, t_data light);
int		get_light_to_print(t_env *e, t_data light);
void	lightsphere(t_env *e, t_data light);

int		rt_plan(t_env *e, t_data *scene);
int		lightplan(t_env *e, t_data light);
int		size_light_on_plan(t_env *e, t_data *scene, t_data light);

void	rt_cone(t_env *e, t_data *scene);
int		get_cone_to_print(t_env *e, t_data *scene);
void	lightcone(t_env *e, t_data light);
int		size_light_on_cone(t_env *e, t_data *scene, t_data light);

void	rt_dcone(t_env *e, t_data *scene);
int		get_dcone_to_print(t_env *e, t_data *scene);
void	lightdcone(t_env *e, t_data light);
int		size_light_on_dcone(t_env *e, t_data *scene, t_data light);

void	rt_cylinder(t_env *e, t_data *scene);
int		get_cyl_to_print(t_env *e, t_data *scene);
void	lightcylinder(t_env *e, t_data light);
int		size_light_on_cyl(t_env *e, t_data *scene, t_data light);

void	rt_dcylinder(t_env *e, t_data *scene);
int		get_dcyl_to_print(t_env *e, t_data *scene);
void	lightdcylinder(t_env *e, t_data light);
int		size_light_on_dcyl(t_env *e, t_data *scene, t_data light);
int		get_light_to_demi_c(t_env *e, t_data *scene, t_data light);

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

void	display_progress(int height, int weight);
void	display_done(void);

#endif

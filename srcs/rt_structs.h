/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmehay <cmehay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:36:48 by cmehay            #+#    #+#             */
/*   Updated: 2014/03/26 21:38:20 by cmehay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

typedef enum	e_obj
{
	CAM = 1,
	SPHERE,
	CYLINDER,
	CONE,
	PLAN,
	DSPHERE,
	DCYLINDER,
	DCONE,
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
	int				min;
	int				max;
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

#endif

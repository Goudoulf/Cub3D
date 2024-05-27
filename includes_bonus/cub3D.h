/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/05/27 16:07:47 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/get_next_line.h"
# include "../lib/ft_printf/includes/ft_printf.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "my_struct.h"
#include <math.h>
#include <stdbool.h>
#define WIDTH 1920;
#define HEIGHT 1080;

typedef struct s_tex
{
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;	
	int		width;
	int		height;
}				t_tex;
typedef struct s_image
{
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;	
}				t_image;

typedef struct  s_map
{
	char	**buffer;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor;
	int		ceiling;
	char	**map;
	int		**final_map;
	int		max_X;
	int		max_Y;
}               t_map;

typedef struct s_camera
{
	float	angle;
	int		fov;
	float	fov_rad;
	t_vec	move;
	bool	no_change;
	int		oldx;
	bool	move_f;
	bool	move_b;
	bool	move_l;
	bool	move_r;
	int		width;
	int		height;
}				t_camera;

typedef struct s_texture
{
	t_tex north;
	t_tex south;
	t_tex east;
	t_tex west;
	t_tex statue;
	t_tex scream;
} t_texture;

typedef struct s_ray_en
{
		int drawStart;
		int drawEnd;
		int		side;
		float	pvector;
} t_ray_en;

typedef struct s_raycast
{
	t_vec	pos;
	float	cameraX; 
	t_vec	vector;
	t_pos	map;
	t_vec	next;
	t_vec	delta;
	float	pvector;
	t_vec	step;
	t_vec	add;
	int		w_hit;
	int		side;
	int		line;
	int		start;
	int		end;
	int		color;
	t_ray_en statue;
	int		flag_statue;

} t_raycast;

typedef struct s_mini_map
{
	t_image	img;
	t_image	img_pos;
	t_pos	last_pos;
	int		last_color;
} t_mini_map;

typedef struct  s_cub
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_image		img;
	t_raycast	*ray;
	t_camera	*cam;
	t_mini_map mini_map;
	t_texture	texture;
	int		win_y;
	int		win_x;
	char	init_view;
	int		view_ennemy;
	int		flag_die;
	float		posX_ennemy;
	float		posY_ennemy;
}		t_cub;

int		mouse_control(int button, int x, int y, t_cub *cub);
int		mouse_turn(int x, int y, t_cub *cub);
int		key_control(int keycode, t_cub *cub);
int		close_window(t_cub *cub);
void	init_all(t_cub *cub);
int		init_function(t_cub *cub, char *av);
int		ft_read(t_cub *cub, char *av);
int		attribute_init_map(int i, int max, t_map *map, t_cub *cub);
int		check_parcing(t_map *map, t_cub *cube);
void    ft_free_strarr(char **str);
int		raycast(t_cub *cub);
int		render(t_cub *cub);
int		convert_tab_char_to_int(t_cub *cub);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	check_hit_wall(t_cub *cub, int i);
int		event_loop(t_cub *cub);
int		key_release(int keysym, t_cub *cub);
void	ft_set_minimap(t_cub *cub);
int		ft_texture(int direc, char *str, t_map *map);
int		create_minimap(t_cub *cub);
void	put_position_minimap(t_cub *cub, int color);
void	ft_ennemy_move(t_cub *cub);
void	ray_draw_statue(t_cub *cub, int x, int h);
int		tex_color(t_tex *tex, int y, int x);
float set_angle(t_cub *cub);
void	texture_init(t_cub *cub);


#endif
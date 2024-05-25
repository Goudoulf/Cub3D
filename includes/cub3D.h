/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/05/25 10:02:27 by cassie           ###   ########.fr       */
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

typedef struct s_image
{
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;
}				t_image;

typedef struct s_position_value
{
	int     init_player_y;
	int     init_player_x;
	char    init_camera;
}               t_position_value;

typedef struct  s_map
{
	char				**buffer;
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	char				*floor;
	char				*ceiling;
	char				**map;
	int					**final_map;
	int					max_X;
	int					max_Y;
	t_position_value    *player;
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

typedef struct s_raycast
{
	t_vec	pos;
	float	cameraX; 
	t_vec	rayDir;
	t_pos	map;
	t_vec	sideDist;
	t_vec	deltaDist;
	float	perpWallDist;
	t_vec	step;
	t_vec	add;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;

} t_raycast;

typedef struct  s_cub
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_image		img;
	t_raycast	ray;
	t_camera	cam;
}		t_cub;

int		mouse_control(int button, int x, int y, t_cub *cub);
int		mouse_turn(int x, int y, t_cub *cub);
int		key_control(int keycode, t_cub *cub);
int		close_window(t_cub *cub);
void	init_all(t_cub *cub);
int		init_function(t_cub *cub, char *av);
int		ft_read(t_cub *cub, char *av);
int		attribute_init_map(char **str, int i, int max, t_map *map);
int		check_parcing(char **str, t_map *map);
void    ft_free_strarr(char **str);
int		raycast(t_cub *cub);
int		render(t_cub *cub);
int		convert_tab_char_to_int(t_cub *cub);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	check_hit_wall(t_cub *cub, int i);
int		event_loop(t_cub *cub);
int		key_release(int keysym, t_cub *cub);

#endif

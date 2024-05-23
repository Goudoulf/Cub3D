/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 14:12:34 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/get_next_line.h"
# include "../lib/ft_printf/includes/ft_printf.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
#include <math.h>

typedef struct s_data
{
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;
}				t_data;

typedef struct s_position_value
{
	int     init_player_y;
	int     init_player_x;
	char    init_camera;
}               t_position_value;

typedef struct  s_map
{
	char	**buffer;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
	char	**map;
	int		**final_map;
	int		max_X;
	int		max_Y;
	t_position_value    *player;
}               t_map;

typedef struct s_raycast
{

      double cameraX; 
      double rayDirX; 
      double rayDirY;
      int mapX;
      int mapY;
      double sideDistX;
      double sideDistY;
      double deltaDistX;
      double deltaDistY;
      double perpWallDist;
      int stepX;
      int stepY;
      int hit;
      int side;
      int lineHeight;
      int drawStart;
      int drawEnd;
      int color;

} t_raycast;

typedef struct  s_cube
{
	void        *mlx;
	void    *win;
	t_map   *map;
	t_data  img;
	t_raycast ray;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY; //the 2d raycaster version of camera plane
	unsigned int width;
	unsigned int height;
}		t_cube;

int     mouse_control(int button, int x, int y, t_cube *cube);
int	key_control(int keycode, t_cube *cube);
int	close_window(t_cube *cube);
void	init_all(t_cube *cube);
int	init_function(t_cube *cube, char *av);
int	ft_read(t_cube *cube, char *av);
int	attribute_init_map(char **str, int i, int max, t_map *map);
int	check_parcing(char **str, t_map *map);
void    ft_free_strarr(char **str);
int raycast(t_cube *cube);
int render(t_cube *cube);
int convert_tab_char_to_int(t_cube *cube);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
void	check_hit_wall(t_cube *cube, int i);

#endif

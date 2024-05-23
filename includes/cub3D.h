/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 16:27:36 by dvo              ###   ########.fr       */
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
	int		win_y;
	int		win_x;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	char	init_view;
	double planeY; //the 2d raycaster version of camera plane
	unsigned int width;
	unsigned int height;
}		t_cube;

int     mouse_control(int button, int x, int y, t_cube *cube);
int		mouse_camera(int x, int y, t_cube *cube);
int	key_control(int keycode, t_cube *cube);
int	close_window(t_cube *cube);
void	init_all(t_cube *cube);
int	init_function(t_cube *cube, char *av);
int	ft_read(t_cube *cube, char *av);
int	attribute_init_map(int i, int max, t_map *map, t_cube *cube);
int	check_parcing(t_map *map, t_cube *cube);
void    ft_free_strarr(char **str);
int raycast(t_cube *cube);
int render(t_cube *cube);
int convert_tab_char_to_int(t_cube *cube);
void	my_mlx_pixel_put(t_data *img, int x, int y, int color);
void	check_hit_wall(t_cube *cube, double ms, int i);

#endif

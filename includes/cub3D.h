/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/05/21 18:54:52 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/get_next_line.h"
# include "../lib/ft_printf/includes/ft_printf.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

typedef struct s_data
{
	void	*img_ptr;
	char    *buffer;
	int		bpp;
	int		line_len;
	int		endian;
}				t_data;

typedef struct  s_map
{
    char **buffer;
    char *north;
    char *south;
    char *west;
    char *east;
    char *floor;
    char *ceiling;
    char **map;
    char **final_map;

    
}               t_map;

typedef struct  s_cube
{
	void    *mlx;
	void    *win;
	t_data  img;
    t_map   *map;
	unsigned int width;
	unsigned int height;
}		t_cube;

int	mouse_control(int button, int x, int y, t_cube *cube);
int	key_control(int keycode, t_cube *cube);
int	close_window(t_cube *cube);
void	init_all(t_cube *cube);
int	init_function(t_cube *cube, char *av);
int	ft_read(t_cube *cube, char *av);
int	attribute_text_wall(t_map *map);
void    ft_test(t_cube *cube);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/05/22 15:33:26 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/includes/libft.h"
# include "../lib/gnl/get_next_line.h"
# include "../lib/ft_printf/includes/ft_printf.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

typedef struct s_data
{
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;
}				t_data;

typedef struct  s_cube
{
	void *mlx;
	void *win;
	t_data img;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY; //the 2d raycaster version of camera plane
	unsigned int width;
	unsigned int height;
}		t_cube;

int	mouse_control(int button, int x, int y, t_cube *cube);
int	key_control(int keycode, t_cube *cube);
int	close_window(t_cube *cube);
void	init_all(t_cube *cube);
int raycast(t_cube *cube);

#endif

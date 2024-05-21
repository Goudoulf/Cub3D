/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:00 by cassie            #+#    #+#             */
/*   Updated: 2024/05/21 13:31:42 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_window(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->img.img_ptr);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit(EXIT_SUCCESS);
}

int	key_control(int keycode, t_cube *cube)
{
	if (keycode == XK_Escape)
		close_window(cube);
	return (0);
}

int	mouse_control(int button, int x, int y, t_cube *cube)
{
	(void) button;
	(void) x;
	(void)y;
	(void) cube;
	return (0);
}

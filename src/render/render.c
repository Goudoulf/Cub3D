/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:54:23 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 17:34:19 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
  ((unsigned int *)(img->buffer))[x + y * 800] = color;
}

int render(t_cube *cube)
{
  ft_bzero(cube->img.buffer, 800*600*4);
  raycast(cube);
  mlx_put_image_to_window(cube->mlx, cube->win, cube->img.img_ptr, 0, 0);
  return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:54:23 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 16:30:25 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->buffer + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int render(t_cube *cube)
{
  int w = cube->win_x;
  int h = cube->win_y;
  int x = 0;
  int y = 0;
  while (x < w)
  {
    y = 0;
    while (y < h)
    {
      my_mlx_pixel_put(&cube->img, x, y, 0x000000);
      y++;
    }
    x++;
  }
  mlx_put_image_to_window(cube->mlx, cube->win, cube->img.img_ptr, 0, 0);
  raycast(cube);
  mlx_put_image_to_window(cube->mlx, cube->win, cube->img.img_ptr, 0, 0);
  return 0;
}

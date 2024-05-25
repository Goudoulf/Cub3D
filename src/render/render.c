/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:54:23 by cassie            #+#    #+#             */
/*   Updated: 2024/05/25 09:43:37 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
  ((unsigned int *)(img->buffer))[x + y * 1920] = color;
}

int render(t_cub *cub)
{
  ft_bzero(cub->img.buffer, 1920*1080*4);
  raycast(cub);
  mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img_ptr, 0, 0);
  return 0;
}

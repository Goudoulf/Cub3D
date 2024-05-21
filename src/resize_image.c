/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:31:40 by dvo               #+#    #+#             */
/*   Updated: 2024/05/21 19:04:25 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	nxt_ft_size(t_img *n_bg, t_img *o_bg)
{
	int	y;
	int	x;
	int	k;
	int	og_x;
	int	og_y;

	y = 0;
	while (y < n_bg->height)
	{
		x = 0;
		while (x < n_bg->width)
		{
			og_x = (x * o_bg->width) / n_bg->width;
			og_y = (y * o_bg->height) / n_bg->height;
			k = 0;
			while (k < n_bg->bpp / 8)
			{
				n_bg->data[y * n_bg->lline + x * (n_bg->bpp / 8) + k] = \
				o_bg->data[og_y * o_bg->lline + og_x * (o_bg->bpp / 8) + k];
				k++;
			}
			x++;
		}
		y++;
	}
}

int	resize_image(t_cube *cube, t_img *old_bg, int new_width, int new_height)
{
	t_img	*new_bg;
	void	*new_img;

new_bg->data
	new_bg = malloc(sizeof(t_img));
	new_bg->width = new_width;
	new_bg->height = new_height;
	old_bg->data = mlx_get_data_addr(old_bg->ptr, &(old_bg->bpp), \
	&(old_bg->size_line), &(old_bg->endian));
	new_img = mlx_new_image(base->mlx, new_width, new_height);
	new_bg->data = mlx_get_data_addr(new_img, &(new_bg->bpp), \
	&(new_bg->lline), &(new_bg->endian));
	nxt_ft_size(new_bg, old_bg);
	mlx_destroy_image(base->mlx, old_bg->ptr);
	old_bg->ptr = new_img;
	old_bg->width = new_width;
	old_bg->height = new_height;
	free(new_bg);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:44:21 by dvo               #+#    #+#             */
/*   Updated: 2024/05/29 18:04:44 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	nxt_ft_size(t_tex *n_bg, t_tex *o_bg)
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
				n_bg->buffer[y * n_bg->line_len + x * (n_bg->bpp / 8) + k] = \
				o_bg->buffer[og_y * o_bg->line_len + og_x * (o_bg->bpp / 8) + k];
				k++;
			}
			x++;
		}
		y++;
	}
}

int	resize_image(t_cub *cub, t_tex *old, int new_width, int new_height)
{
	t_tex	*new;
	void	*new_img;

	new = ft_calloc(1, sizeof(t_tex));
	new->width = new_width;
	new->height = new_height;
	old->buffer = mlx_get_data_addr(old->img_ptr, &(old->bpp), \
	&(old->line_len), &(old->endian));
	new_img = mlx_new_image(cub->mlx, new_width, new_height);
	new->buffer = mlx_get_data_addr(new_img, &(new->bpp), \
	&(new->line_len), &(new->endian));
	nxt_ft_size(new, old);
	mlx_destroy_image(cub->mlx, old->img_ptr);
	old->img_ptr = new_img;
	old->width = new_width;
	old->height = new_height;
	free(new);
	return (0);
}

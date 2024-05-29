/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_channel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:57:01 by dvo               #+#    #+#             */
/*   Updated: 2024/05/29 23:31:30 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

void	put_pixel_on_bg(t_cub *cub, t_tex *old, int y, int x)
{
	int offset;

	unsigned int color = tex_color(old, y, x);

	if (color == 0x000000)
	{
		offset = (cub->mini_map.floor->line_len * y) + (x * (cub->mini_map.floor->bpp / 8));
		*((unsigned int *)(offset + cub->mini_map.floor->buffer)) = cub->map->floor;
	}
}

static void	nxt_alpha(t_cub *cub, t_tex *old)
{
	int	y;
	int	x;

	y = 0;
	while (y < old->height)
	{
		x = 0;
		while (x < old->width)
		{
			put_pixel_on_bg(cub, old, y, x);
			x++;
		}
		y++;
	}
}

int	alpha_channel(t_cub *cub, t_tex *old)
{
	old->buffer = mlx_get_data_addr(old->img_ptr, &old->bpp, &old->line_len, &old->endian);
	nxt_alpha(cub, old);
	return (0);
}

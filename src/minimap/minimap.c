/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:11:16 by dvo               #+#    #+#             */
/*   Updated: 2024/05/30 09:39:28 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



void	put_minimap(t_cub *cub, int y, int x, t_tex *src)
{
	int	offset1;
	int	offset2;
	t_pos	tmp;
	t_pos	index;

	index.y = 0;
	index.x = 0;
	tmp.x = x * cub->mini_map.x_case;
	tmp.y = y * cub->mini_map.y_case;
	while (index.y < cub->mini_map.y_case)
	{
		index.x = 0;
		while (index.x < cub->mini_map.x_case)
		{
			tmp.x = x * cub->mini_map.x_case + index.x;
			tmp.y = y * cub->mini_map.y_case + index.y;
			offset1 = (cub->mini_map.img.line_len * tmp.y) + (tmp.x * (cub->mini_map.img.bpp / 8));
			offset2 = (src->line_len * index.y) + (index.x * (src->bpp / 8));
			if (*((unsigned int*)(src->buffer + offset2)) != 0x00000)
				*((unsigned int*)(cub->mini_map.img.buffer + offset1)) = *((unsigned int*)(src->buffer + offset2));
			else
				*((unsigned int*)(cub->mini_map.img.buffer + offset1)) = *((unsigned int*)(cub->mini_map.floor->buffer + offset2));
			index.x++;
		}
		index.y++;
	}
}

void	ft_set_minimap(t_cub *cub)
{
	int	x;
	int	y;
	int pos_x;
	int	pos_y;

	pos_x = (int) cub->ray->pos.x - 5;
	pos_y = (int) cub->ray->pos.y - 5;
	y = 0;
	while (y < 12)	
	{
		x = 0;
		while(x < 12)
		{
			if (y == 5 && x == 5)
				put_minimap(cub, y, x, cub->mini_map.n_bot);
			else if ((x + pos_x < cub->map->max_x) && (y + pos_y < cub->map->max_y)
					&& (x + pos_x >= 0) && (y + pos_y >= 0) && cub->map->final_map[y + pos_y][x + pos_x] == 1)
				put_minimap(cub, y, x, cub->mini_map.wall);
			else if ((x + pos_x >= cub->map->max_x) || (y + pos_y >= cub->map->max_y) || (x + pos_x < 0) || (y + pos_y < 0))
				put_minimap(cub, y, x, cub->mini_map.wall);
			else
				put_minimap(cub, y, x, cub->mini_map.floor);
			x++;
		}
		y++;
		x = 0;
	}
}

int create_minimap(t_cub *cub)
{
	cub->mini_map.img.img_ptr = mlx_new_image(cub->mlx, cub->win_x / 8, cub->win_y / 5);
	if (cub->mini_map.img.img_ptr == NULL)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	cub->mini_map.img.buffer = mlx_get_data_addr(cub->mini_map.img.img_ptr,
			&cub->mini_map.img.bpp, &cub->mini_map.img.line_len, &cub->mini_map.img.endian);
	cub->mini_map.x_case = (cub->win_x / 8) / 12;
	cub->mini_map.y_case = (cub->win_y / 5) / 12;
	init_text_map(cub);
	init_text_characters(cub);
	ft_set_minimap(cub);
	return (0);
}

void	put_position_minimap(t_cub *cub, int color)
{
	int	x;
	int	y;
	int	init_x;
	float test_y;
	float test_x;

	y = 0;
	init_x = (cub->win_x / 8);
	x = init_x;
	if (!color)
		color = (255 << 16) | (0 << 8) | 0;
	while (y < cub->win_y / 5)	
	{
		while(x - init_x < cub->win_x / 8)
		{
			test_x = (cub->map->max_x * (x - init_x)) / (float)(cub->win_x / 8.0f);
			test_y = (cub->map->max_y * y) / (float)(cub->win_y / 5.0f);
			if (cub->ray->pos.y + 0.3 > test_y && cub->ray->pos.y - 0.3 < test_y && \
			cub->ray->pos.x + 0.3 > test_x && cub->ray->pos.x - 0.3 < test_x)
				((unsigned int *)(cub->mini_map.img.buffer))[x + y * 1920 / 8] = color;
			x++;
		}
		y++;
		x = init_x;
	}
}

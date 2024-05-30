/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:11:16 by dvo               #+#    #+#             */
/*   Updated: 2024/05/30 07:50:13 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_floor_minimap(t_cub *cub, int y, int x, t_image *src)
{
	int	offset1;
	int	offset2;
	int tmp_x;
	int	tmp_y;
	int	indexy;
	int	indexx;

	indexy = 0;
	indexx = 0;
	tmp_x = x * cub->mini_map.x_case;
	tmp_y = y * cub->mini_map.y_case;
	while (indexy < cub->mini_map.y_case)
	{
		indexx = 0;
		while (indexx < cub->mini_map.x_case)
		{
			tmp_x = x * cub->mini_map.x_case + indexx;
			tmp_y = y * cub->mini_map.y_case + indexy;
			offset1 = (cub->mini_map.img.line_len * tmp_y) + (tmp_x * (cub->mini_map.img.bpp / 8));
			offset2 = (src->line_len * indexy) + (indexx * (src->bpp / 8));
			*((unsigned int*)(cub->mini_map.img.buffer + offset1)) = *((unsigned int*)(src->buffer + offset2));
			indexx++;
		}
		indexy++;
	}
}

void	put_case_minimap(t_cub *cub, int y, int x, t_tex *src)
{
	int	offset1;
	int	offset2;
	int tmp_x;
	int	tmp_y;
	int	indexy;
	int	indexx;

	indexy = 0;
	indexx = 0;
	tmp_x = x * cub->mini_map.x_case;
	tmp_y = y * cub->mini_map.y_case;
	while (indexy < cub->mini_map.y_case)
	{
		indexx = 0;
		while (indexx < cub->mini_map.x_case)
		{
			tmp_x = x * cub->mini_map.x_case + indexx;
			tmp_y = y * cub->mini_map.y_case + indexy;
			offset1 = (cub->mini_map.img.line_len * tmp_y) + (tmp_x * (cub->mini_map.img.bpp / 8));
			offset2 = (src->line_len * indexy) + (indexx * (src->bpp / 8));
			*((unsigned int*)(cub->mini_map.img.buffer + offset1)) = *((unsigned int*)(src->buffer + offset2));
			indexx++;
		}
		indexy++;
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
	if (pos_x < 0)
		pos_x = 0;
	if (pos_y < 0)
		pos_y = 0;
	if (pos_y + 10 > cub->map->max_y)
		pos_y= cub->map->max_y - 10;
	if (pos_x + 10 > cub->map->max_x)
		pos_x= cub->map->max_x - 10;
	y = 0;
	//int border = (218 << 16) | (165 << 8) | 32;
	while (y < 11)	
	{
		x = 0;
		while(x < 11)
		{
			if (y == 6 && x == 6)
				put_case_minimap(cub, y, x, cub->mini_map.n_bot);
			else if ((x + pos_x < cub->map->max_x) && (y + pos_y < cub->map->max_y) && cub->map->final_map[y + pos_y][x + pos_x] == 1)
				put_case_minimap(cub, y, x, cub->mini_map.wall);
			else
				put_floor_minimap(cub, y, x, cub->mini_map.floor);
			x++;
		}
		y++;
		x = 0;
	}
}

int create_minimap(t_cub *cub)
{
	cub->mini_map.img.img_ptr = mlx_new_image(cub->mlx, cub->win_x / 5, cub->win_y / 5);
	if (cub->mini_map.img.img_ptr == NULL)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	cub->mini_map.img.buffer = mlx_get_data_addr(cub->mini_map.img.img_ptr,
			&cub->mini_map.img.bpp, &cub->mini_map.img.line_len, &cub->mini_map.img.endian);
	cub->mini_map.x_case = (cub->win_x / 5) / 11;
	cub->mini_map.y_case = (cub->win_y / 5) / 11;
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
	init_x = (cub->win_x / 5);
	x = init_x;
	if (!color)
		color = (255 << 16) | (0 << 8) | 0;
	while (y < cub->win_y / 5)	
	{
		while(x - init_x < cub->win_x / 5)
		{
			test_x = (cub->map->max_x * (x - init_x)) / (float)(cub->win_x / 5.0f);
			test_y = (cub->map->max_y * y) / (float)(cub->win_y / 5.0f);
			if (cub->ray->pos.y + 0.3 > test_y && cub->ray->pos.y - 0.3 < test_y && \
			cub->ray->pos.x + 0.3 > test_x && cub->ray->pos.x - 0.3 < test_x)
				((unsigned int *)(cub->mini_map.img.buffer))[x + y * 1920 / 5] = color;
			x++;
		}
		y++;
		x = init_x;
	}
}

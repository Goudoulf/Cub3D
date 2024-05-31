/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:37:14 by dvo               #+#    #+#             */
/*   Updated: 2024/05/31 09:26:53 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    get_floor_minimap(t_cub *cub);

int init_text_characters(t_cub *cub)
{
	cub->mini_map.e_bot = ft_calloc(1, sizeof(t_tex));
	cub->mini_map.e_bot->img_ptr = mlx_xpm_file_to_image(cub->mlx, "./textures/hero/neutral_l.xpm", &cub->mini_map.e_bot->width, &cub->mini_map.e_bot->height);	
	if (!cub->mini_map.e_bot->img_ptr)
		return (-1);
	if (resize_image(cub, cub->mini_map.e_bot, cub->mini_map.x_case, cub->mini_map.y_case) == -1)
		return (-1);
	cub->mini_map.e_bot->buffer = mlx_get_data_addr(cub->mini_map.e_bot->img_ptr,
			&cub->mini_map.e_bot->bpp, &cub->mini_map.e_bot->line_len, &cub->mini_map.e_bot->endian);
	return (0);
}

int init_text_map(t_cub *cub)
{
	get_floor_minimap(cub);
	cub->mini_map.wall = ft_calloc(1, sizeof(t_tex));
	cub->mini_map.wall->img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->map->south, &cub->mini_map.wall->width, &cub->mini_map.wall->height); 
	if (!cub->mini_map.wall->img_ptr)
		return (-1);
	printf("old:%i, %i", cub->mini_map.wall->height, cub->mini_map.wall->width);
	if (resize_image(cub, cub->mini_map.wall, cub->mini_map.x_case, cub->mini_map.y_case) == -1)
		return (-1);
	cub->mini_map.wall->buffer = mlx_get_data_addr(cub->mini_map.wall->img_ptr,
			&cub->mini_map.wall->bpp, &cub->mini_map.wall->line_len, &cub->mini_map.wall->endian);
	return (0);
}

void    get_floor_minimap(t_cub *cub)
{
	int y;
	int x;
	int offset;

	y = 0;
	cub->mini_map.floor = ft_calloc(1, sizeof(t_tex));
	cub->mini_map.floor->img_ptr = mlx_new_image(cub->mlx, cub->mini_map.x_case, cub->mini_map.y_case);
	if (cub->mini_map.floor->img_ptr == NULL)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	cub->mini_map.floor->buffer = mlx_get_data_addr(cub->mini_map.floor->img_ptr,
			&cub->mini_map.floor->bpp, &cub->mini_map.floor->line_len, &cub->mini_map.floor->endian);
	while (y < cub->mini_map.y_case)
	{
		x = 0;
		while(x < cub->mini_map.x_case)
		{
			offset = (cub->mini_map.floor->line_len * y) + (x * (cub->mini_map.floor->bpp / 8));
			*((unsigned int *)(offset + cub->mini_map.floor->buffer)) = cub->map->floor;
			x++;
		}
		y++;
	}
}

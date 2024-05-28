/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:20:39 by dvo               #+#    #+#             */
/*   Updated: 2024/05/28 15:34:50 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_strarr(char **str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i > 0)
	{
		free(str[i]);
		i--;
	}
	free(str[i]);
	free(str);
}

void    ft_free_init_all(t_cub *cub)
{
	free (cub->ray);
	free (cub->cam);
	mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free (cub);
}

void    ft_free_text(t_map *map)
{
	if (map->north)
	{
		free (map->north);
	}
	if (map->south)
	{
		free (map->south);
	}
	if (map->east)
    {
        free (map->east);
    }
    if (map->west)
    {
        free (map->west);
    }
}

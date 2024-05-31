/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_free.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dvo <dvo@student.42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/22 14:20:39 by dvo			   #+#	  #+#			  */
/*	 Updated: 2024/05/28 19:31:02 by dvo			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_strarr(void *s)
{
	char **str;

	str = (char **)s;
	size_t	i;

	i = 0;
	if (!str || !str[0])
	{
		free(str);
		return ;
	}
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

void	ft_free_intarr(int **map, t_cub *cub)
{
	int	y;

	y = 0;
	while (y < cub->map->max_y)
	{
		free (map[y]);
		y++;
	}
	free (map);
}

void	ft_free_init_all(t_cub *cub)
{
	free (cub->ray);
	free (cub->cam);
	mlx_destroy_image(cub->mlx, cub->img.img_ptr);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free (cub);
}

void	ft_free_map_tex(t_map *map)
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

void	free_all_parse(t_cub *cub)
{
	ft_free_intarr(cub->map->final_map, cub);
	ft_free_strarr(cub->map->buffer);
	ft_free_strarr(cub->map->map);
	ft_free_map_tex(cub->map);
	free(cub->map);
}

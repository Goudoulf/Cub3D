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

void	free_str_array(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_int_array(int **map, t_cub *cub)
{
	int	y;

	y = -1;
	if (!map)
		return ;
	while (*map && ++y < cub->map->max_y)
		free (map[y]);
	free (map);
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
	free_int_array(cub->map->final_map, cub);
	free_str_array(cub->map->buffer);
	free_str_array(cub->map->map);
	ft_free_map_tex(cub->map);
	if (cub->map)
		free(cub->map);
}

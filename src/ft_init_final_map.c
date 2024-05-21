/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_final_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/21 17:05:21 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_start_map(char *str);

int	create_new_map(char **str, int i, t_map *map)
{
	int max;
	
	max = i;
	while (str[max])
		max++;
	max--;
	while (check_start_map(str[max]) == 1)
		max --;
	map->final_map = ft_calloc(max - i + 1, sizeof(char *));
	// attribute_final_map();
    return (0);
}

int	check_start_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0' || str[i] == 'N' || str[i] == 'E' || \
	str[i] == 'S' || str[i] == 'W')
		return (1);
	return (0);
}
int	ft_texture(int direc, char *str, t_map *map)
{
	int	i;

	i = 0;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	if (direc == 1)
	{
		if (map->north)
			return (-1);
		map->north = ft_strdup(str + i);
		if (!map->north)
			return (-1);
	}
	if (direc == 2)
	{
		if (map->south)
			return (-1);
		map->south = ft_strdup(str + i);
		if (!map->south)
			return (-1);
	}
	if (direc == 3)
	{
		if (map->west)
			return (-1);
		map->west = ft_strdup(str + i);
		if (!map->west)
			return (-1);
	}
	if (direc == 4)
	{
		if (map->east)
			return (-1);
		map->east = ft_strdup(str + i);
		if (!map->east)
			return (-1);
	}
    return (0);
}

int	attribute_text_wall(t_map *map)
{
	int	i;

	i = 0;
	while (check_start_map(map->buffer[i]) == 1)
	{
		if (ft_strncmp(map->buffer[i], "NO ", 3) == 0)
			ft_texture(1, map->buffer[i], map);
		if (ft_strncmp(map->buffer[i], "SO ", 3) == 0)
			ft_texture(2, map->buffer[i], map);
		if (ft_strncmp(map->buffer[i], "WE ", 3) == 0)
			ft_texture(3, map->buffer[i], map);
		if (ft_strncmp(map->buffer[i], "EA ", 3) == 0)
			ft_texture(4, map->buffer[i], map);
        if (ft_strncmp(map->buffer[i], "F ", 2) == 0)
			ft_texture(5, map->buffer[i], map);
        if (ft_strncmp(map->buffer[i], "C ", 2) == 0)
			ft_texture(6, map->buffer[i], map);
		i++;
	}
	create_new_map(map->buffer, i, map);
    return (0);
}
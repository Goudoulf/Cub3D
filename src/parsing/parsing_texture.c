/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:41:42 by dvo               #+#    #+#             */
/*   Updated: 2024/05/30 06:54:27 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	convert_char_color(char *str)
{
	int	i;
	int	first;
	int	second;
	int	third;

	if (check_valid_color(str) == -1)
	{
		free (str);
		return (-1);
	}
	i = 0;
	first = ft_atoi(str);
	while (str[++i - 1] != ',')
		;
	second = ft_atoi(str + i);
	i++;
	while (str[i - 1] != ',')
		i++;
	third = ft_atoi(str + i);
	free (str);
	i = (first << 16) | (second << 8) | third;
	return (i);
}

int	direc1(int direc, char *str, t_map *map, int i)
{
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
	return (0);
}

int	direc2(int direc, char *str, t_map *map, int i)
{
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

int	direc3(int direc, char *str, t_map *map, int i)
{
	if (direc == 5)
	{
		if (map->floor != -1)
			return (-1);
		map->floor = convert_char_color(ft_strdup(str + i));
		if (map->floor == -1)
			return (-1);
	}
	if (direc == 6)
	{
		if (map->ceiling != -1)
			return (-1);
		map->ceiling = convert_char_color(ft_strdup(str + i));
		if (map->ceiling == -1)
			return (-1);
	}
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
	if (direc1(direc, str, map, i) == -1)
		return (-1);
	if (direc2(direc, str, map, i) == -1)
		return (-1);
	if (direc3(direc, str, map, i) == -1)
		return (-1);
	return (0);
}

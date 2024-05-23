/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:41:42 by dvo               #+#    #+#             */
/*   Updated: 2024/05/23 20:01:15 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int hexCharToInt(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else
		return c - 'A' + 10;
}

int hexStrToInt(char *str) {
	int result = 0;
	int i;
	int value;

	i = 0;
	while (str[i])
	{
		value = hexCharToInt(str[i]);
		result = (result * 16) + value; // Multiplier le résultat actuel par 16 (décalage de 4 bits) et ajouter la valeur actuelle
		i++;
	}
	return result;
}

int	transform_to_hexa(int first, int second, int third)
{
	char    *str;
	char    *hexa;

	hexa = "0123456789ABCDEF";
	str = ft_calloc(7, sizeof(char));
	str[0] = hexa[first / 16];
	str[1] = hexa[first % 16];
	str[2] = hexa[second / 16];
	str[3] = hexa[second % 16];
	str[4] = hexa[third / 16];
	str[5] = hexa[third % 16];
	
	int i = hexStrToInt(str);
	printf("before:%s, int is:%i\n", str, i);
	return (i);
}

int	convert_char_color(char *str)
{
	int i;
	int first;
	int second;
	int third;

	i = 0;
	first = ft_atoi(str);
	while (str[i - 1] != ',')
		i++;
	second = ft_atoi(str + i);
	i++;
	while (str[i - 1] != ',')
		i++;
	third = ft_atoi(str + i);
	free (str);
	return (transform_to_hexa(first, second, third));
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
	if (direc == 5)
	{
		if (map->floor)
			return (-1);
		map->floor = convert_char_color(ft_strdup(str + i));
		if (!map->floor)
			return (-1);
	}
	if (direc == 6)
	{
		if (map->ceiling)
			return (-1);
		map->ceiling = convert_char_color(ft_strdup(str + i));
		if (!map->ceiling)
			return (-1);
	}
	return (0);
}

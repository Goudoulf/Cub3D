/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:41:42 by dvo               #+#    #+#             */
/*   Updated: 2024/05/31 13:16:40 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	convert_char_color(t_cub *cub, char *str)
{
	int	i;
	int	first;
	int	second;
	int	third;

	if (!str)
		return (-1);
	if (check_valid_color(cub, str) == -1)
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

int	direc1(int direc, char *str, t_cub *cub, int i)
{
	if (direc == 1)
	{
		if (cub->map->north)
			return (-1);
		cub->map->north = ft_strdup(str + i);
		if (!cub->map->north)
			return (-1);
	}
	if (direc == 2)
	{
		if (cub->map->south)
			return (-1);
		cub->map->south = ft_strdup(str + i);
		if (!cub->map->south)
			return (-1);
	}
	return (0);
}

int	direc2(int direc, char *str, t_cub *cub, int i)
{
	if (direc == 3)
	{
		if (cub->map->west)
			return (-1);
		cub->map->west = ft_strdup(str + i);
		if (!cub->map->west)
			return (-1);
	}
	if (direc == 4)
	{
		if (cub->map->east)
			return (-1);
		cub->map->east = ft_strdup(str + i);
		if (!cub->map->east)
			return (-1);
	}
	return (0);
}

int	direc3(int direc, char *str, t_cub *cub, int i)
{
	if (direc == 5)
	{
		if (cub->map->floor != -1)
			return (-1);
		cub->map->floor = convert_char_color(cub, ft_strdup(str + i));
		if (cub->map->floor == -1)
			return (-1);
	}
	if (direc == 6)
	{
		if (cub->map->ceiling != -1)
			return (-1);
		cub->map->ceiling = convert_char_color(cub, ft_strdup(str + i));
		if (cub->map->ceiling == -1)
			return (-1);
	}
	return (0);
}

int	ft_texture(int direc, char *str, t_cub *cub)
{
	int	i;

	i = 0;
	while (str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	if (direc1(direc, str, cub, i) == -1)
		return (-1);
	if (direc2(direc, str, cub, i) == -1)
		return (-1);
	if (direc3(direc, str, cub, i) == -1)
		return (-1);
	return (0);
}

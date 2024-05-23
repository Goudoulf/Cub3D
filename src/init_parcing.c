/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parcing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:29:37 by dvo               #+#    #+#             */
/*   Updated: 2024/05/23 11:47:36 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "stdio.h"

int	check_start_map(char *str);

int	create_new_map(char **str, int i, t_map *map)
{
	int max;
	
	max = i;
	while (str[max])
		max++;
	map->max_Y = max - i;
	max--;
	while (check_start_map(str[max]) == 1)
		max --;
	printf("%i\n", max - i + 1);
	map->map = ft_calloc(max - i + 2, sizeof(char *));
	map->final_map = ft_calloc(max - i + 1, sizeof(int *));
	if (attribute_init_map(str, i, max, map) == -1)
	{
		ft_free_strarr(map->map);
		return (-1);
	}
    return (0);
}

int	check_start_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0' || str[i] == 'N' || str[i] == 'E' || str[i] == '\n' || \
	str[i] == 'S' || str[i] == 'W' || str[i] == 'F' || str[i] == 'C')
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
	if (direc == 5)
	{
		if (map->floor)
			return (-1);
		map->floor = ft_strdup(str + i);
		if (!map->floor)
			return (-1);
	}
	if (direc == 6)
	{
		if (map->ceiling)
			return (-1);
		map->ceiling = ft_strdup(str + i);
		if (!map->ceiling)
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
	if (create_new_map(map->buffer, i, map) == -1)
		return (-1);
    return (0);
}

int	init_function(t_cube *cube, char *av)
{
	cube->map = ft_calloc(1, sizeof(t_map));
	if (ft_read(cube, av) == -1)
		return (-1);
	if (attribute_text_wall(cube->map) == -1)
		return (-1);
	if (convert_tab_char_to_int(cube) == -1)
		return (-1);
	return (0);
}


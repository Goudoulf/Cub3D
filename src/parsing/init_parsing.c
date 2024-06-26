/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:29:37 by dvo               #+#    #+#             */
/*   Updated: 2024/06/02 19:30:25 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_start_map(char *str, t_cub *cub, int status)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '0' && str[i] != '1' && status == 0)
		return (1);
	if (status == 0)
		return (0);
	if (str[i] == '\n' || str[i] == '\0')
		return (1);
	if (str[i] != '0' && str[i] != '1')
	{
		ft_printf(2, "Error\nProblem under the map\n");
		malloc_error(cub, true);
	}
	return (0);
}

int	create_new_map(char **str, int i, t_map *map, t_cub *cub)
{
	int	max;

	max = i;
	while (str[max])
		max++;
	max--;
	while ((check_start_map(str[max], cub, 1) == 1) && max > i)
		max --;
	if (max == i)
	{
		ft_printf(2, "Error\nProblem with the map\n");
		malloc_error(cub, true);
	}
	map->max_y = max - i + 1;
	map->map = ft_calloc(max - i + 2, sizeof(char *));
	map->final_map = ft_calloc(max - i + 1, sizeof(int *));
	if (!map->map || !map->final_map)
		malloc_error(cub, true);
	if (attribute_init_map(i, max, map, cub) == -1)
		malloc_error(cub, true);
	return (0);
}

int	check_content(t_cub *cub, t_map *map, int i)
{
	if (ft_strncmp(map->buffer[i], "NO ", 3) == 0)
		return (ft_texture(1, map->buffer[i], cub));
	else if (ft_strncmp(map->buffer[i], "SO ", 3) == 0)
		return (ft_texture(2, map->buffer[i], cub));
	else if (ft_strncmp(map->buffer[i], "WE ", 3) == 0)
		return (ft_texture(3, map->buffer[i], cub));
	else if (ft_strncmp(map->buffer[i], "EA ", 3) == 0)
		return (ft_texture(4, map->buffer[i], cub));
	else if (ft_strncmp(map->buffer[i], "F ", 2) == 0)
		return (ft_texture(5, map->buffer[i], cub));
	else if (ft_strncmp(map->buffer[i], "C ", 2) == 0)
		return (ft_texture(6, map->buffer[i], cub));
	else if (map->buffer[i][0] != '\0')
	{
		ft_printf(2, "Error\n%s didn't exist\n", map->buffer[i]);
		malloc_error(cub, true);
	}
	return (0);
}

int	attribute_text_wall(t_map *map, t_cub *cub)
{
	int	i;

	i = 0;
	map->ceiling = -1;
	map->floor = -1;
	while (check_start_map(map->buffer[i], cub, 0) == 1)
	{
		if (check_content(cub, map, i) == -1)
			malloc_error(cub, true);
		i++;
	}
	if (!map->buffer[i])
	{
		ft_printf(2, "Error\nInvalid map\n");
		malloc_error(cub, true);
	}
	if (!check_texture(map))
		malloc_error(cub, true);
	create_new_map(map->buffer, i, map, cub);
	return (0);
}

int	init_function(t_cub *cub, char *av)
{
	cub->map = ft_calloc(1, sizeof(t_map));
	if (!cub->map)
		malloc_error(cub, true);
	if (ft_read(cub, av, 0) == -1)
		malloc_error(cub, true);
	if (attribute_text_wall(cub->map, cub) == -1)
		malloc_error(cub, true);
	if (convert_tab_char_to_int(cub, 0, 0) == -1)
		malloc_error(cub, true);
	return (0);
}

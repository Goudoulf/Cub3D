/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_final_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/22 16:55:47 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	attribute_init_map(char **str, int i, int max, t_map *map)
{
	int index_f;

	map->player = ft_calloc(1, sizeof(t_position_value));
	index_f = 0;
	while (i <= max)
	{
		map->map[index_f] = ft_strdup(str[i]);
		i++;
		index_f++;
	}
	if (check_parcing(map->map, map) == -1)
	{
		free(map->player);
		return (-1);
	}
	return (0);
}

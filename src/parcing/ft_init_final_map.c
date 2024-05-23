/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_final_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/23 16:22:47 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	attribute_init_map(int i, int max, t_map *map, t_cube *cube)
{
	int	index_f;

	index_f = 0;
	while (i <= max)
	{
		map->map[index_f] = ft_strdup(map->buffer[i]);
		i++;
		index_f++;
	}
	if (check_parcing(map, cube) == -1)
		return (-1);
	return (0);
}

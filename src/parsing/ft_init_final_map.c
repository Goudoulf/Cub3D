/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_final_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/26 09:20:20 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	attribute_init_map(int i, int max, t_map *map, t_cub *cub)
{
	int	index_f;

	index_f = 0;
	while (i <= max)
	{
		map->map[index_f] = ft_strdup(map->buffer[i]);
		i++;
		index_f++;
	}
	if (check_parcing(map, cub) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_final_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:43:23 by dvo               #+#    #+#             */
/*   Updated: 2024/05/30 07:01:48 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/X.h>

/*size_t	max_len_table(char **str)
{
	size_t	len;
	size_t	x;
	size_t	y;

	len = 0;
	x = 0;
	y = 0;
	while (str[y])
	{
		while (str[y][x] != '\0')
			x++;
		if (x > len)
			len = x;
		x = 0;
		y++;
	}
	return (len);
}*/

/*int convert_tab_char_to_int(t_cub *cub)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (cub->map->map[y])
	{
		cub->map->final_map[y] = ft_calloc(cub->map->max_x, sizeof(int));
		while (cub->map->map[y][x] != '\0')
		{
			if (cub->map->map[y][x] != '0')
				cub->map->final_map[y][x] = 1;
			if (cub->map->map[y][x] == '3')
				cub->map->final_map[y][x] = -1;
			x++;
		}
		x = 0;
		y++;
	}
	ft_add_ennemy(cub);
	return (0);
}*/

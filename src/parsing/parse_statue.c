/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_statue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:54:20 by dvo               #+#    #+#             */
/*   Updated: 2024/05/28 11:24:14 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_add_ennemy(t_cub *cub)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < cub->map->max_Y)
	{
		while (x < cub->map->max_X)
		{
			if (cub->map->final_map[y][x] == 0 && check_road(cub->map->final_map, y, x))
			{
				cub->map->final_map[y][x] = 2;
				cub->posX_ennemy = x;
				cub->posY_ennemy = y;
				printf("[%i][%i]\n", y, x);
				return ;
			}
			x++;
		}
		y++;
		x = 0;
	}

}

static int	check_5(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] == '5')
			check++;
		i++;
	}
	return (check);
}

// static void	check_around(char *str, int i)
// {
// 	int	line;

// 	line = 0;
// 	while (str[line] != '\n')
// 		line++;
// 	if (str[i - 1] == '0' || str[i - 1] == 'E' || str[i - 1] == 'C')
// 		str[i - 1] = '5';
// 	if (str[i + 1] == '0' || str[i + 1] == 'E' || str[i + 1] == 'C')
// 		str[i + 1] = '5';
// 	if (str[i + line + 1] == '0' || str[i + line + 1] == 'E' \
// 	|| str[i + line + 1] == 'C')
// 		str[i + line + 1] = '5';
// 	if (str[i - line - 1] == '0' || str[i - line - 1] == 'E' \
// 	|| str[i - line - 1] == 'C')
// 		str[i - line - 1] = '5';
// 	str[i] = '6';
// }

int	check_road(char **map, int posy, int posx)
{
	int	i;
    int nbr_five;
    int x;
    int y;

    nbr_five = 1;
    map[posy][posx] = 5;
	while (nbr_five != 0)
	{
        nbr_five = 0;
		i = 0;
		while (map[y])
		{
            x = 0;
            while (map[y][x])
            {
			    if (map[y][x] == 5)
				    nbr_five += check_around(map, y, x);
                x++;
            }
			i++;
            y++;
		}
	}
	return (0);
}

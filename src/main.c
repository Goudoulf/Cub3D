/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/05/25 15:32:05 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	print_map(t_cub *cub)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(y < cub->map->max_Y)
	{
		while(x < cub->map->max_X)
		{
			printf("%d", cub->map->final_map[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

int	main(int argc, char **argv)
{
	(void) argc;
	t_cub cub;
	init_all(&cub);
	if (init_function(&cub, argv[1]) == -1)
		return (1);
	print_map(&cub);
	create_minimap(&cub);
	render(&cub);
	mlx_loop(cub.mlx);
	return (0);
}

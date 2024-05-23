/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/05/23 13:28:10 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_cube cube;
	if (init_function(&cube, argv[1]) == -1)
		return (1);
	int x = 0;
	int y = 0;
	while(y < 24)
	{
		while(x < 24)
		{
			printf("%d", cube.map->final_map[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	init_all(&cube);
	render(&cube);
	mlx_loop(cube.mlx);
	return (0);
}

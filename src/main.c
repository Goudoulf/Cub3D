/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/05/24 17:52:32 by dvo              ###   ########.fr       */
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
	while(y < cube.map->max_Y)
	{
		while(x < cube.map->max_X)
		{
			printf("%d", cube.map->final_map[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	init_all(&cube);
	create_minimap(&cube);
	mlx_mouse_move(cube.mlx ,cube.win, cube.win_x, cube.win_y);
	mlx_mouse_hide(cube.mlx ,cube.win);
	render(&cube);
	mlx_loop(cube.mlx);
	return (0);
}

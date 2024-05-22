/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/05/22 18:13:29 by dvo              ###   ########.fr       */
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
	while(y < 14)
	{
		while(x < 33)
		{
			printf("%d", cube.map->final_map[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	init_all(&cube);
	raycast(&cube);
	mlx_loop(cube.mlx);
	return (0);
}

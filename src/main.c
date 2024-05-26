/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/05/26 08:50:36 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	print_map(t_cub *cub)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(y < 24)
	{
		while(x < 24)
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
	t_cub *cub;
	cub = ft_calloc(1, sizeof(t_cub));
	init_all(cub);
	if (init_function(cub, argv[1]) == -1)
		return (1);
	print_map(cub);
	create_minimap(cub);
	render(cub);
	mlx_loop(cub->mlx);
	return (0);
}

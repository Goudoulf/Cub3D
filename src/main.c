/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/05/30 13:19:00 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < cub->map->max_y)
	{
		while (x < cub->map->max_x)
		{
			printf("%d", cub->map->final_map[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

int	free_texture_error(t_cub *cub)
{
	ft_free_text(cub->map);
	ft_free_strarr(cub->map->map);
	free(cub->map->final_map);
	free(cub->map);
	ft_free_init_all(cub);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		return (1);
	cub = ft_calloc(1, sizeof(t_cub));
	init_all(cub);
	if (init_function(cub, argv[1]) == -1)
	{
		ft_free_init_all(cub);
		return (1);
	}
	cub->mini_map.x_case = (cub->win_x / 8) / 12;
	cub->mini_map.y_case = (cub->win_y / 5) / 12;
	if (texture_init(cub) == -1)
		return (free_texture_error(cub));
	create_minimap(cub);
	cub->cam->angle = set_angle(cub);
	print_map(cub);
	render(cub);
	mlx_loop(cub->mlx);
	return (0);
}

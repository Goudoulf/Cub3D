/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/05/31 16:38:40 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
	{
		ft_printf(2, "Error\nInvalid number of arguments\n");
		return (1);
	}
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		return (1);
	init_all(cub);
	if (init_function(cub, argv[1]) == -1)
		malloc_error(cub, true);
	cub->mini_map.x_case = (cub->win_x / 8) / 12;
	cub->mini_map.y_case = (cub->win_y / 5) / 12;
	if (texture_init(cub, &cub->texture) == -1)
		malloc_error(cub, true);
	if (!create_minimap(cub))
		malloc_error(cub, true);
	cub->cam->angle = set_angle(cub);
	render(cub);
	mlx_loop(cub->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/06/01 14:33:05 by cassie           ###   ########.fr       */
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
	if (texture_init(cub, &cub->texture) == -1)
		malloc_error(cub, true);
	cub->cam->angle = set_angle(cub);
	render(cub);
	mlx_loop(cub->mlx);
	return (0);
}

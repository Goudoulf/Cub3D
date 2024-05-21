/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parcing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:29:37 by dvo               #+#    #+#             */
/*   Updated: 2024/05/21 13:33:28 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "stdio.h"

int	init_function(t_mlx *base, char *av)
{
	base->mlx = mlx_init();
	if (!base->mlx)
		return (-1);
	if (ft_read(base, av) == -1)
		return (-1);
	if (set_up_map(base) == -1)
		return (-1);
	base->win = mlx_new_window(base->mlx, \
   3800, 2000, "Cub3D");
	if (!base->win)
		return (-1);
	return (0);
}


int	cub_3d(char *av)
{
	t_mlx	*base;

	base = ft_calloc(sizeof(t_mlx), 1);
	if (!base)
		exit (1);
	if (init_function(base, av) == -1)
		return (free_mlx(base), -1);
	mlx_key_hook(base->win, f, base);
	mlx_hook(base->win, 17, (1L << 17), ft_close, base);
	mlx_loop(base->mlx);
	mlx_destroy_window(base->mlx, base->win);
	free_mlx(base);
	return (0);
}
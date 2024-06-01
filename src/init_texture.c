/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:43:28 by cassie            #+#    #+#             */
/*   Updated: 2024/06/01 14:35:46 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	texture_init(t_cub *cub, t_texture *texture)
{
	ft_bzero(texture, 1);
	if (!texture_init_mlx(cub, &texture->north, cub->map->north))
		return (-1);
	if (!texture_init_mlx(cub, &texture->south, cub->map->south))
		return (-1);
	if (!texture_init_mlx(cub, &texture->east, cub->map->east))
		return (-1);
	if (!texture_init_mlx(cub, &texture->west, cub->map->west))
		return (-1);
	init_texture_lookup(cub);
	return (1);
}

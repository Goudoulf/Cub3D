/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:19:13 by dvo               #+#    #+#             */
/*   Updated: 2024/05/30 14:27:04 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_img(t_tex *tex, t_cub *cub)
{
	mlx_destroy_image(cub->mlx, tex->img_ptr);
	free(tex);
	tex = NULL;
}

void	free_text(t_cub *cub)
{
	// if (cub->texture.north)
	// 	free_img(cub->texture.north, cub);
	// if (cub->texture.south)
	// 	free_img(cub->texture.south, cub);
	// if (cub->texture.east)
	// 	free_img(cub->texture.east, cub);
	// if (cub->texture.statue)
	// 	free_img(cub->texture.statue, cub);
	// if (cub->texture.scream)
	// 	free_img(cub->texture.scream, cub);
	// if (cub->texture.door)
	// 	free_img(cub->texture.door, cub);
	if (cub->mini_map.floor)
		free_img(cub->mini_map.floor, cub);
	if (cub->mini_map.wall)
		free_img(cub->mini_map.wall, cub);
}

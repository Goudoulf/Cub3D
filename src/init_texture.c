/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:43:28 by cassie            #+#    #+#             */
/*   Updated: 2024/05/29 21:00:12 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_texture_lookup(t_cub *cub)
{
	cub->texture.tab[0][0][0] = &cub->texture.west;
	cub->texture.tab[0][1][0] = &cub->texture.east;
	cub->texture.tab[1][0][0] = &cub->texture.south;
	cub->texture.tab[1][0][1] = &cub->texture.north;
	cub->texture.tab[0][0][1] = cub->texture.tab[0][0][0];
	cub->texture.tab[0][1][1] = cub->texture.tab[0][1][0];
	cub->texture.tab[1][1][0] = cub->texture.tab[1][0][0];
	cub->texture.tab[1][1][1] = cub->texture.tab[1][0][1];
}

static int	texture_init_mlx(t_cub *cub, t_tex *tex, char *path)
{
	tex->img_ptr
		= mlx_xpm_file_to_image(cub->mlx, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
		return (0);
	tex->buffer = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (1);
}

int	texture_init(t_cub *cub)
{
	if (!texture_init_mlx(cub, &cub->texture.north, cub->map->north))
		return (-1);
	if (!texture_init_mlx(cub, &cub->texture.south, cub->map->south))
		return (-1);
	if (!texture_init_mlx(cub, &cub->texture.east, cub->map->east))
		return (-1);
	if (!texture_init_mlx(cub, &cub->texture.west, cub->map->west))
		return (-1);
	if (!texture_init_mlx(cub, &cub->texture.statue, "./textures/statue.xpm"))
		return (-1);
	if (!texture_init_mlx(cub, &cub->texture.scream, "./textures/scream.xpm"))
		return (-1);
	if (!texture_init_mlx(cub, &cub->texture.door, "./textures/door.xpm"))
		return (-1);
	init_texture_lookup(cub);
	return (1);
}

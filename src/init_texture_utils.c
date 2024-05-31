/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:15:53 by cassie            #+#    #+#             */
/*   Updated: 2024/05/31 13:23:21 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_texture_lookup(t_cub *cub)
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

int	texture_init_mlx(t_cub *cub, t_tex *tex, char *path)
{
	tex->img_ptr
		= mlx_xpm_file_to_image(cub->mlx, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
		return (0);
	tex->buffer = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (1);
}

int	image_init_mlx(t_cub *cub, t_tex *tex, int sizex, int sizey)
{
	tex->img_ptr = mlx_new_image(cub->mlx, sizex, sizey);
	if (!tex->img_ptr)
		return (0);
	tex->buffer = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (1);
}

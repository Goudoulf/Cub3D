/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:23:15 by cassie            #+#    #+#             */
/*   Updated: 2024/06/01 14:41:44 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_texture(t_cub *cub)
{
	if (cub->texture.north.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.north.img_ptr);
	if (cub->texture.south.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.south.img_ptr);
	if (cub->texture.east.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.east.img_ptr);
	if (cub->texture.west.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.west.img_ptr);
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->img.img_ptr);
}

void	malloc_error(t_cub *cub, bool error)
{
	if (cub->map)
		free_all_parse(cub);
	destroy_texture(cub);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	if (cub->ray)
		free(cub->ray);
	if (cub->cam)
		free(cub->cam);
	free(cub);
	if (error == true)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	close_window(t_cub *cub)
{
	malloc_error(cub, false);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:23:15 by cassie            #+#    #+#             */
/*   Updated: 2024/05/31 13:22:59 by dvo              ###   ########.fr       */
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
	if (cub->texture.door.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.door.img_ptr);
	if (cub->texture.floor.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.floor.img_ptr);
	if (cub->texture.wall.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.wall.img_ptr);
	if (cub->texture.left1.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.left1.img_ptr);
	if (cub->texture.left2.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.left2.img_ptr);
	if (cub->texture.left3.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.left3.img_ptr);
	if (cub->mini_map.img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->mini_map.img.img_ptr);
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx, cub->img.img_ptr);
}

void	malloc_error(t_cub *cub, bool error)
{
	if (cub->map)
	free_all_parse(cub);
	destroy_texture(cub);
	if (cub->texture.hero)
		free_circular_list(&cub->texture.hero);
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

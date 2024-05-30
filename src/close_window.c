/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:23:15 by cassie            #+#    #+#             */
/*   Updated: 2024/05/30 17:52:00 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_mlx(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->texture.north.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.south.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.east.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.west.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.door.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.statue.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.scream.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.left1.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.left2.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.left3.img_ptr);
	mlx_destroy_image(cub->mlx, cub->mini_map.img.img_ptr);
	mlx_destroy_image(cub->mlx, cub->mini_map.floor->img_ptr);
	mlx_destroy_image(cub->mlx, cub->mini_map.wall->img_ptr);
	mlx_destroy_image(cub->mlx, cub->img.img_ptr);
}

int	close_window(t_cub *cub)
{
	t_list *temp;
	int	i;

	destroy_mlx(cub);
	temp = NULL;
	i = -1;
	while (cub->map->map[++i])
		free(cub->map->map[i]);
	free(cub->map->map);
	i = -1;
	while (++i < cub->map->max_y)
		free(cub->map->final_map[i]);
	free(cub->map->final_map);
	i = -1;
	while (cub->map->buffer[++i])
		free(cub->map->buffer[i]);
	while (cub->texture.hero != NULL)
	{
		temp = cub->texture.hero->next;
		free(cub->texture.hero);
		cub->texture.hero = temp;
	}
	//free(cub->texture.hero);
	free(cub->map->buffer);
	free(cub->map->north);
	free(cub->map->south);
	free(cub->map->east);
	free(cub->map->west);
	free(cub->mini_map.floor);
	free(cub->mini_map.wall);
	free(cub->map);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub->ray);
	free(cub->cam);
	free(cub);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:23:15 by cassie            #+#    #+#             */
/*   Updated: 2024/05/30 20:59:14 by cassie           ###   ########.fr       */
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
	mlx_destroy_image(cub->mlx, cub->texture.floor.img_ptr);
	mlx_destroy_image(cub->mlx, cub->texture.wall.img_ptr);
	mlx_destroy_image(cub->mlx, cub->img.img_ptr);
}

void	free_circular_list(t_list **list)
{
	t_list	*head;
	t_list	*temp;

	head = *list;
	temp = *list;
	while (temp->next != head)
		temp = temp->next;
	temp->next = NULL;
	temp = head;
	while (temp != NULL)
	{
		head = temp->next;
		free(temp);
		temp = head;
	}
	*list = temp;
}

int	close_window(t_cub *cub)
{
	int	i;

	destroy_mlx(cub);
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
	free_circular_list(&cub->texture.hero);
	free(cub->map->buffer);
	free(cub->map->north);
	free(cub->map->south);
	free(cub->map->east);
	free(cub->map->west);
	free(cub->map);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub->ray);
	free(cub->cam);
	free(cub);
	exit(EXIT_SUCCESS);
}

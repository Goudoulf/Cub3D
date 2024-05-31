/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:19:13 by dvo               #+#    #+#             */
/*   Updated: 2024/05/31 10:34:54 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	free_lst_hero(t_list *hero)
{
	t_list	*tmp;
	t_list	*next;

	tmp = hero;
	if (hero != NULL)
	{
		next = tmp->next;
		free(tmp);
		hero = NULL;
		tmp = next;
		while (tmp != NULL)
		{
			next = tmp->next;
			free (tmp);
			tmp = next;
		}
	}
	return (-1);
}

void	free_text(t_cub *cub)
{
	if (cub->texture.north.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.north.img_ptr);
	if (cub->texture.south.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.south.img_ptr);
	if (cub->texture.east.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.east.img_ptr);
	if (cub->texture.west.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.west.img_ptr);
	if (cub->texture.statue.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.statue.img_ptr);
	if (cub->texture.scream.img_ptr)
		mlx_destroy_image(cub->mlx, cub->texture.scream.img_ptr);
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
}

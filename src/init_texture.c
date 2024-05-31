/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:43:28 by cassie            #+#    #+#             */
/*   Updated: 2024/05/31 13:06:53 by cassie           ###   ########.fr       */
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

static int	image_init_mlx(t_cub *cub, t_tex *tex, int sizex, int sizey)
{
	tex->img_ptr = mlx_new_image(cub->mlx, sizex, sizey);
	if (!tex->img_ptr)
		return (0);
	tex->buffer = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (1);
}

int	texture_mini(t_cub *cub, t_tex *tex, char *path)
{
	tex->img_ptr
		= mlx_xpm_file_to_image(cub->mlx, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
		return (0);
	if (resize_image(cub, tex, cub->mini_map.x_case, cub->mini_map.y_case)
		== -1)
		return (0);
	tex->buffer = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (1);
}

int	init_hero_list(t_cub *cub)
{
	t_list	*temp;

	cub->texture.hero = ft_calloc(1, sizeof(t_list));
	temp = cub->texture.hero;
	if (!cub->texture.hero)
		return (free_lst_hero(temp));
	cub->texture.hero->tex = &cub->texture.left1;
	cub->texture.hero->next = ft_calloc(1, sizeof(t_list));
	if (!cub->texture.hero->next)
		return (free_lst_hero(temp));
	cub->texture.hero = cub->texture.hero->next;
	cub->texture.hero->tex = &cub->texture.left2;
	cub->texture.hero->next = ft_calloc(1, sizeof(t_list));
	if (!cub->texture.hero->next)
		return (free_lst_hero(temp));
	cub->texture.hero = cub->texture.hero->next;
	cub->texture.hero->tex = &cub->texture.left3;
	cub->texture.hero->next = ft_calloc(1, sizeof(t_list));
	if (!cub->texture.hero->next)
		return (free_lst_hero(temp));
	cub->texture.hero = cub->texture.hero->next;
	cub->texture.hero->tex = &cub->texture.left2;
	cub->texture.hero->next = temp;
	return (1);
}

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
	if (!texture_init_mlx(cub, &texture->door, "./textures/door.xpm"))
		return (-1);
	if (!image_init_mlx(cub, &texture->floor, cub->mini_map.x_case,
			cub->mini_map.y_case))
		return (-1);
	if (!image_init_mlx(cub, &cub->mini_map.img, cub->win_x / 8,
			cub->win_y / 5))
		return (-1);
	if (!texture_mini(cub, &texture->left1, "./textures/hero/left1.xpm"))
		return (-1);
	if (!texture_mini(cub, &texture->left2, "./textures/hero/left2.xpm"))
		return (-1);
	if (!texture_mini(cub, &texture->left3, "./textures/hero/left3.xpm"))
		return (-1);
	if (!texture_mini(cub, &texture->wall, cub->map->south))
		return (-1);
	init_texture_lookup(cub);
	if (init_hero_list(cub) == -1)
		return (-1);
	return (1);
}

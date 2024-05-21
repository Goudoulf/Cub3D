/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:42:56 by dvo               #+#    #+#             */
/*   Updated: 2024/05/21 19:01:00 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_w_l(t_cube *cube, t_parc *bg)
{
	t_img	*wb;

	wb = malloc(sizeof(t_img));
	if (!wb)
		return (-1);
	wb->ptr = mlx_xpm_file_to_image(base->mlx, \
	"cavern/left.xpm", &(wb->width), &(wb->height));
	if (wb->ptr == (void *)0)
		return (-1);
	if (resize_image(base, wb, base->res->w_pix, base->res->h_pix))
		return (-1);
	wb->data = mlx_get_data_addr(wb->ptr, &(wb->bpp), \
	&(wb->lline), &(wb->endian));
	bg->w_l = wb;
	return (0);
}

void    ft_test(t_cube *cube)
{
    t_img *wall;

    wall = malloc(sizeof(t_img));
    wall = mlx_xpm_file_to_image(cube->mlx, \
	"cavern/left.xpm", &(wall->width), &(wall->height));
    resize_image(cube, wall, 400, 300);
}
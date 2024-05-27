/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_ennemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:13:29 by dvo               #+#    #+#             */
/*   Updated: 2024/05/27 05:47:20 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    ft_ennemy_move(t_cub *cub)
{
    if (cub->view_ennemy == 1)
        return ;
    cub->map->final_map[(int)cub->posY_ennemy][(int)cub->posX_ennemy] = 0;
    if (cub->posX_ennemy > cub->ray->pos.x)
		cub->posX_ennemy-= 0.05;
    else
	    cub->posX_ennemy+= 0.05;
    if (cub->posY_ennemy > cub->ray->pos.y)
	    cub->posY_ennemy-= 0.05;
    else
	cub->posY_ennemy+= 0.05;
    cub->map->final_map[(int)cub->posY_ennemy][(int)cub->posX_ennemy] = 2;
    if ((int)cub->posY_ennemy == (int)(cub->ray->pos.y) && (int)(cub->posX_ennemy) == (int)(cub->ray->pos.x))
        cub->flag_die = 1;
}

void ray_draw_statue(t_cub *cub, int x, int h)
{
    t_tex *tex = &cub->texture.statue;
    int lineHeight = (int)(h / cub->ray->statue.perpWallDist);

    int drawStart = -lineHeight / 2 + h / 2;
    if (drawStart < 0)
        drawStart = 0;
    int drawEnd = lineHeight / 2 + h / 2;
    if (drawEnd >= h)
        drawEnd = h - 1;

    float wallX;
    if (cub->ray->statue.side == 0)
        wallX = cub->ray->pos.y + cub->ray->statue.perpWallDist * cub->ray->rayDir.y;
    else
        wallX = cub->ray->pos.x + cub->ray->statue.perpWallDist * cub->ray->rayDir.x;
    wallX -= floorf(wallX);

    int texX = (int)(wallX * 64);
    if (cub->ray->statue.side == 0 && cub->ray->rayDir.x > 0) texX = 64 - texX - 1;
    if (cub->ray->statue.side == 1 && cub->ray->rayDir.y < 0) texX = 64 - texX - 1;

    while (drawStart < drawEnd)
    {
        int texY = (int)(drawStart * 2 - h + lineHeight) * ((64 / 2.) / lineHeight);
        unsigned int color = get_tex_color(tex, texY, texX);

        if (color != 0x000000)
        {
            ((unsigned int *)(cub->img.buffer))[x + drawStart * 1920] = color;
        }
        drawStart++;
    }
}

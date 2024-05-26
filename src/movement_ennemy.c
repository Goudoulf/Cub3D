/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_ennemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:13:29 by dvo               #+#    #+#             */
/*   Updated: 2024/05/26 08:33:01 by cassie           ###   ########.fr       */
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

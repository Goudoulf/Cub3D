/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassie <cassie@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:52:52 by cassie            #+#    #+#             */
/*   Updated: 2024/05/29 20:56:43 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	tex_color(t_tex *tex, int y, int x)
{
	if (x >= 0 && x < tex->width && y >= 0 && y < tex->height)
		return (*(int *)(tex->buffer + (4 * tex->width * (int)y)
			+ (4 * (int)x)));
	return (0x0);
}

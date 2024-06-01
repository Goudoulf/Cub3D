/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:07:42 by cassie            #+#    #+#             */
/*   Updated: 2024/06/01 20:14:34 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	print_error(char *err, int ret)
{
	ft_printf(2, "%s\n", err);
	return (ret);
}

int	print_error_pos(char *err, int ret, int x, int y)
{
	ft_printf(2, "%s %d, %d\n", err, y, x);
	return (ret);
}

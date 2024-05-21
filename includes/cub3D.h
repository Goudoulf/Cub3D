/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/05/21 13:02:36 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/includes/libft.h"
# include "../lib/gnl/get_next_line.h"
# include "../lib/ft_printf/includes/ft_printf.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <stdio.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>


typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	char		*buf;
}				t_mlx;

#endif

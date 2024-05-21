/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:03:05 by dvo               #+#    #+#             */
/*   Updated: 2024/05/21 16:59:09 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_read(t_cube *cube, char *av)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "File not valid\n"), -1);
	cube->map->buffer = ft_calloc(2001, sizeof(char *));
	if (!cube->map->buffer)
		return (-1);
	while (1)
	{
		cube->map->buffer[i] = get_next_line(fd);
		if (!cube->map->buffer[i] || i == 2000)
			break ;
		i++;
	}
	if (i == 2000)
		return (-1);
	attribute_text_wall(cube->map);
	return (0);
}

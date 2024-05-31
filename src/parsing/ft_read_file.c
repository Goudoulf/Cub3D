/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:03:05 by dvo               #+#    #+#             */
/*   Updated: 2024/05/31 09:31:33 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_transform_nl_to_end(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
}

int	ft_read(t_cub *cub, char *av)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "File not valid\n"), -1);
	cub->map->buffer = ft_calloc(2001, sizeof(char *));
	if (!cub->map->buffer)
		return (-1);
	while (1)
	{
		cub->map->buffer[i] = get_next_line(fd);
		if (!cub->map->buffer[i] || i == 2000)
			break ;
		ft_transform_nl_to_end(cub->map->buffer[i]);
		i++;
	}
	if (i == 2000)
		return (-1);
	return (0);
}

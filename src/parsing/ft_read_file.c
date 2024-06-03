/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:03:05 by dvo               #+#    #+#             */
/*   Updated: 2024/06/03 12:39:25 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_check_file_name(char *av, char *str)
{
	int		i;
	int		j;

	i = strlen(av) - 1;
	j = 3;
	if (i < 4)
	{
		ft_printf(2, "Error\nThe file is not a .cub\n");
		return (-1);
	}
	while (j >= 0)
	{
		if (str[j] != av[i])
		{
			ft_printf(2, "Error\nThe file is not a .cub\n");
			return (-1);
		}
		j--;
		i--;
	}
	return (0);
}

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

int	print_error_fd(char * err, int ret)
{
	ft_printf(2, err);
	return (ret);
}

int	ft_read(t_cub *cub, char *av, int i)
{
	int	fd;

	if (ft_check_file_name(av, ".cub") == -1)
		return (-1);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return(print_error_fd("Error\nFile not valid\n", -1));
	cub->map->buffer = ft_calloc(2001, sizeof(char *));
	if (!cub->map->buffer)
		malloc_error(cub, true);
	while (1)
	{
		cub->map->buffer[i] = get_next_line(fd);
		if (!cub->map->buffer[i] || i == 2000)
			break ;
		ft_transform_nl_to_end(cub->map->buffer[i]);
		i++;
	}
	close(fd);
	if (i == 2000)
		return (-1);
	return (0);
}

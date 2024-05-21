/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:03:05 by dvo               #+#    #+#             */
/*   Updated: 2024/05/21 13:05:59 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_realloc(t_mlx *base, int i)
{
	int		j;
	char	*str;

	str = NULL;
	j = 0;
	if (base->buf)
	{
		str = ft_strdup(base->buf);
		if (!str)
			return (-1);
		free(base->buf);
	}
	(base->buf) = ft_calloc(1, sizeof(char) * (i * 1000 + 1));
	if (!base->buf)
		return (-1);
	while (str && str[j])
	{
		base->buf[j] = str[j];
		j++;
	}
	base->buf[j] = '\0';
	free (str);
	return (0);
}

void	ft_put_str(t_mlx *base, char *str)
{
	int	i;
	int	j;

	if (base->buf)
		i = ft_strlen(base->buf);
	else
		i = 0;
	j = 0;
	while (str[j])
	{
		(base->buf)[i] = str[j];
		i++;
		j++;
	}
	(base->buf)[i] = '\0';
}

int	ft_get_txt(t_mlx *base, int fd)
{
	int		i;
	int		read_error;
	char	str[1001];

	i = 1;
	read_error = 1;
	while (read_error != 0)
	{
		if (ft_realloc(base, i) == -1)
			return (-1);
		read_error = read(fd, str, 1000);
		if (read_error == -1)
			return (-1);
		str[read_error] = '\0';
		ft_put_str(base, str);
		i++;
		if (i == 300)
		{
			ft_fprintf(2, "The map is too big\n");
			return (-1);
		}
	}
	return (0);
}

int	ft_read(t_mlx *base, char *av)
{
	int	fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (ft_fprintf(2, "File not valid\n"), -1);
	base->buf = get_next_line(fd);
	if (!base->buf)
		return (close(fd), -1);
	close(fd);
	if (check_error_file(base, av) == -1)
		return (-1);
	return (0);
}

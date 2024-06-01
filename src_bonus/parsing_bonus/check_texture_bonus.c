/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 check_texture.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dvo <dvo@student.42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/27 07:58:19 by dvo			   #+#	  #+#			  */
/*	 Updated: 2024/05/28 19:12:32 by dvo			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	ft_isdigit_str(char *str);
static void	check_comma_rgb(t_cub *cub, char *str);

int	check_texture(t_map *map)
{
	if (!map->north || !map->east || !map->west || !map->south
		|| map->ceiling == -1 || map->floor == -1)
	{
		ft_printf(2, "Error\nInformation from texture is missing\n");
		return (0);
	}
	return (1);
}

int	check_valid_color(t_cub *cub, char *str)
{
	char	**check_rgb;

	check_comma_rgb(cub, str);
	check_rgb = ft_split(str, ',');
	if (!check_rgb)
		return (1);
	if (!check_rgb[0] || !check_rgb[1] || !check_rgb[2] || check_rgb[3])
	{
		ft_printf(2, "Error\nSyntax for RGB is incorrect for %s\n", str);
		free_str_array(check_rgb);
		malloc_error(cub, true);
	}
	if (ft_isdigit_str(check_rgb[0]) || ft_isdigit_str(check_rgb[1])
		|| ft_isdigit_str(check_rgb[2]))
	{
		ft_printf(2, "Error\ncolor RGB is not a number on %s\n", str);
		free_str_array(check_rgb);
		malloc_error(cub, true);
	}
	free_str_array(check_rgb);
	return (0);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static void	check_comma_rgb(t_cub *cub, char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] == ',')
			nbr++;
		i++;
	}
	if (nbr != 2)
	{
		ft_printf(2, "Error\nSyntax for RGB is incorrect for %s\n", str);
		malloc_error(cub, true);
	}
}

void	check_overflow_rgb(t_cub *cub, int first, int second, int third)
{
	if (first > 255 || second > 255 || third > 255)
	{
		ft_printf(2, "Error\nOverflow on color %i,%i,%i\n", first, second, third);
		malloc_error(cub, true);
	}
}
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

#include "cub3D.h"

int	ft_isdigit_str(char *str);

int	check_texture(t_map *map)
{
	if (!map->north || !map->east || !map->west || !map->south
		|| map->ceiling == -1 || map->floor == -1)
	{
		ft_printf(2, "Information from texture is missing\n");
		return (0);
	}
	return (1);
}

int	check_valid_color(char *str)
{
	char	**check_rgb;

	check_rgb = ft_split(str, ',');
	if (!check_rgb)
		return (1);
	if (!check_rgb[0] || !check_rgb[1] || !check_rgb[2] || check_rgb[3])
	{
		ft_printf(2, "Syntax for RGB is incorrect for %s\n", str);
		ft_free_strarr(check_rgb);
		return (-1);
	}
	if (ft_isdigit_str(check_rgb[0]) || ft_isdigit_str(check_rgb[1])
		|| ft_isdigit_str(check_rgb[2]))
	{
		ft_printf(2, "color RGB is not a number on %s\n", str);
		ft_free_strarr(check_rgb);
		return (-1);
	}
	ft_free_strarr(check_rgb);
	return (0);
}

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

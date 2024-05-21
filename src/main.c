/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:57:20 by cassie            #+#    #+#             */
/*   Updated: 2024/05/21 13:29:46 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "stdio.h"

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (cub_3d(argv[i]) == -1)
			return (1);
		i++;
		if (i == argc)
			printf("FINISH!!\n");
		else
			printf("NEXT LEVEL!!\n");
	}
	return (0);
}

/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   init.c						:+:	 :+:	:+:   */
/*						      +:+ +:+	      +:+     */
/*   By: cassie <cassie@student.42lyon.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2024/05/21 12:41:08 by cassie	       #+#    #+#	      */
/*   Updated: 2024/05/28 11:40:02 by cassie	      ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/X.h>
#include <stdio.h>
#define WEST 0
#define EAST 1
#define SOUTH 2
#define NORTH 3


void	init_texture_lookup(t_cub *cub)
{
	cub->texture.tab[0][0][0] = &cub->texture.west;
	cub->texture.tab[0][1][0] = &cub->texture.east;
	cub->texture.tab[1][0][0] = &cub->texture.south;
	cub->texture.tab[1][0][1] = &cub->texture.north;
	cub->texture.tab[0][0][1] = cub->texture.tab[0][0][0];
	cub->texture.tab[0][1][1] = cub->texture.tab[0][1][0];
	cub->texture.tab[1][1][0] = cub->texture.tab[1][0][0];
	cub->texture.tab[1][1][1] = cub->texture.tab[1][0][1];
}

static void	malloc_error(void)
{
	exit(EXIT_FAILURE);
}

static void	event_init(t_cub *cub)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_control, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, key_release, cub);
	mlx_hook(cub->win, ButtonPress, ButtonPressMask, mouse_control, cub);
	mlx_hook(cub->win, MotionNotify, PointerMotionMask, mouse_turn, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask, close_window, cub);
	mlx_loop_hook(cub->mlx, event_loop, cub);
}

float	set_angle(t_cub *cub)
{
	float ret;

	ret = 0;
	if (cub->init_view == 'N')
		ret = -M_PI / 2;
	if (cub->init_view == 'S')
		ret = M_PI / 2;
	if (cub->init_view == 'E')
		ret = M_PI;
	if (cub->init_view == 'W')
		ret = -M_PI;
	return (ret);
}

static void	cub_init(t_cub *cub)
{
	cub->door_m = false;
	cub->ray = ft_calloc(1, sizeof(t_raycast));
	cub->cam = ft_calloc(1, sizeof(t_camera));
	cub->cam->width = WIDTH;
	cub->cam->height = HEIGHT;
	cub->cam->oldx = cub->cam->width / 2;
	cub->cam->angle = 0;
	cub->cam->move_f = false;
	cub->cam->move_b = false;
	cub->cam->move_l = false;
	cub->cam->move_r = false;
	cub->cam->fov = 90;
	cub->cam->fov_rad = cub->cam->fov * M_PI * 0.5 / 180.0;
	cub->win_x = WIDTH;
	cub->win_y = HEIGHT;
	cub->mini_map.last_pos.x = cub->ray->pos.x;
	cub->mini_map.last_pos.y = cub->ray->pos.y;
}

int	texture_init(t_cub *cub)
{
	cub->texture.north.img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->map->north, &cub->texture.north.width, &cub->texture.north.height);	
	if (!cub->texture.north.img_ptr)
		return (-1);
	cub->texture.north.buffer = mlx_get_data_addr(cub->texture.north.img_ptr,
											   &cub->texture.north.bpp, &cub->texture.north.line_len, &cub->texture.north.endian);

	cub->texture.south.img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->map->south,&cub->texture.south.width, &cub->texture.south.height); 
	if (!cub->texture.south.img_ptr)
		return (-1);
	cub->texture.south.buffer = mlx_get_data_addr(cub->texture.south.img_ptr,
											   &cub->texture.south.bpp, &cub->texture.south.line_len, &cub->texture.south.endian);

	cub->texture.east.img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->map->east,&cub->texture.east.width, &cub->texture.east.height); 
	if (!cub->texture.east.img_ptr)
		return (-1);
	cub->texture.east.buffer = mlx_get_data_addr(cub->texture.east.img_ptr,
											  &cub->texture.east.bpp, &cub->texture.east.line_len, &cub->texture.east.endian);

	cub->texture.west.img_ptr = mlx_xpm_file_to_image(cub->mlx, cub->map->west,&cub->texture.west.width, &cub->texture.west.height); 
	if (!cub->texture.west.img_ptr)
		return (-1);
	cub->texture.west.buffer = mlx_get_data_addr(cub->texture.west.img_ptr,
											  &cub->texture.west.bpp, &cub->texture.west.line_len, &cub->texture.west.endian);

	cub->texture.statue.img_ptr = mlx_xpm_file_to_image(cub->mlx, "./textures/statue.xpm",&cub->texture.statue.width, &cub->texture.statue.height); 
	if (!cub->texture.statue.img_ptr)
		return (-1);
	cub->texture.statue.buffer = mlx_get_data_addr(cub->texture.statue.img_ptr,
												&cub->texture.statue.bpp, &cub->texture.statue.line_len, &cub->texture.statue.endian);

	cub->texture.scream.img_ptr = mlx_xpm_file_to_image(cub->mlx, "./textures/scream.xpm",&cub->texture.scream.width, &cub->texture.scream.height); 
	if (!cub->texture.scream.img_ptr)
		return (-1);
	cub->texture.scream.buffer = mlx_get_data_addr(cub->texture.scream.img_ptr,
												&cub->texture.scream.bpp, &cub->texture.scream.line_len, &cub->texture.scream.endian);
	cub->texture.door.img_ptr = mlx_xpm_file_to_image(cub->mlx, "./textures/door.xpm", &cub->texture.door.width, &cub->texture.door.height);	
	if (!cub->texture.door.img_ptr)
		return (-1);
	cub->texture.door.buffer = mlx_get_data_addr(cub->texture.door.img_ptr,
											  &cub->texture.door.bpp, &cub->texture.door.line_len, &cub->texture.door.endian);
	init_texture_lookup(cub);
	return (0);
}

void	init_all(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
		malloc_error();
	cub->win = mlx_new_window(cub->mlx, 1920, 1080, "Cub3D");
	if (cub->win == NULL)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		malloc_error();
	}
	cub->img.img_ptr = mlx_new_image(cub->mlx, 1920, 1080);
	if (cub->img.img_ptr == NULL)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		malloc_error();
	}
	cub->img.buffer = mlx_get_data_addr(cub->img.img_ptr,
									 &cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	event_init(cub);
	cub_init(cub);
}

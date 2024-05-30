/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:15:38 by cassie            #+#    #+#             */
/*   Updated: 2024/05/30 17:51:22 by cassie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/get_next_line.h"
# include "../lib/ft_printf/includes/ft_printf.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "my_struct.h"
# include <math.h>
# include <stdbool.h>
# define WIDTH 1920
# define HEIGHT 1080

typedef struct	s_list t_list;

typedef struct s_tex
{
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;	
	int		width;
	int		height;
}				t_tex;

typedef struct s_image
{
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		line_len;
	int		endian;	
}				t_image;

typedef struct s_map
{
	char	**buffer;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor;
	int		ceiling;
	char	**map;
	int		**final_map;
	int		max_x;
	int		max_y;
}			t_map;

typedef struct s_camera
{
	float	angle;
	int		fov;
	float	fov_rad;
	t_vec	move;
	bool	no_change;
	int		oldx;
	bool	move_f;
	bool	move_b;
	bool	move_l;
	bool	move_r;
	bool	cam_r;
	bool	cam_l;
	int		width;
	int		height;
}				t_camera;

typedef struct s_texture
{
	t_tex	*tab[2][2][2];
	t_tex	north;
	t_tex	south;
	t_tex	east;
	t_tex	west;
	t_tex	statue;
	t_tex	scream;
	t_tex	door;
	t_list	*hero;
	t_tex	left1;
	t_tex	left2;
	t_tex	left3;
	t_list 	*move;
}			t_texture;

typedef struct s_ray_en
{
	int		drawstart;
	int		drawend;
	int		side;
	float	pvector;
}			t_ray_en;

typedef struct s_raycast
{
	t_vec		pos;
	t_vec		vector;
	t_pos		map;
	t_vec		next;
	t_vec		delta;
	float		pvector;
	t_vec		step;
	t_vec		add;
	int			w_hit;
	int			side;
	int			line;
	int			start;
	int			end;
	int			color;
	t_ray_en	statue;
	int			flag_statue;
	t_pos		tex_pos;
	float		wall_pos;

}				t_raycast;

typedef struct	s_list
{
	t_tex			*tex;
	bool			is_last;
	t_list			*next;
}				t_list;

typedef struct s_mini_map
{
	t_image		img;
	t_image		img_pos;
	t_pos		last_pos;
	int			last_color;
	int			x_case;
	int			y_case;
	t_tex		*wall;
	t_tex		*floor;
}				t_mini_map;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_image		img;
	t_raycast	*ray;
	t_camera	*cam;
	t_mini_map	mini_map;
	t_texture	texture;
	int			win_y;
	int			win_x;
	char		init_view;
	int			view_ennemy;
	int			flag_die;
	long		fps_statue;
	float		posx_ennemy;
	float		posy_ennemy;
	bool		door_m;
	t_pos		door_p;
	bool		focus;
}				t_cub;

int		mouse_control(int button, int x, int y, t_cub *cub);
int		mouse_turn(int x, int y, t_cub *cub);
int		key_control(int keycode, t_cub *cub);
int		close_window(t_cub *cub);
void	init_all(t_cub *cub);
int		init_function(t_cub *cub, char *av);
int		ft_read(t_cub *cub, char *av);
int		attribute_init_map(int i, int max, t_map *map, t_cub *cub);
int		check_parcing(t_map *map, t_cub *cube);
void	ft_free_strarr(char **str);
int		raycast(t_cub *cub);
int		render(t_cub *cub);
int		convert_tab_char_to_int(t_cub *cub);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int		event_loop(t_cub *cub);
int		key_release(int keysym, t_cub *cub);
void	ft_set_minimap(t_cub *cub);
int		ft_texture(int direc, char *str, t_map *map);
int		create_minimap(t_cub *cub);
void	put_position_minimap(t_cub *cub, int color);
void	ft_ennemy_move(t_cub *cub);
void	ray_draw_statue(t_cub *cub, int x, int h);
int		tex_color(t_tex *tex, int y, int x);
float	set_angle(t_cub *cub);
int		texture_init(t_cub *cub);
int		check_texture(t_map *map);
int		check_valid_color(char *str);
void	ft_free_init_all(t_cub *cub);
void	ft_free_text(t_map *map);
void	ft_add_ennemy(t_cub *cub);
void	ft_sonar(t_cub *cub, int **map);
int		texture_init(t_cub *cub);
void	check_door(t_cub *cub, t_raycast *ray, t_map *map);
void	update_cam(t_cub *cub, t_raycast *ray, t_map *map);
int		close_window(t_cub *cub);
void	key_move(t_camera *cam);
int		tex_color(t_tex *tex, int y, int x);
int		print_error(char *err, int ret);
int		print_error_pos(char *err, int ret, int x, int y);
int		init_text_map(t_cub *cub);
int		resize_image(t_cub *cub, t_tex *old, int new_width, int new_height);
int		focus_out(t_cub *cub);
int		focus_in(t_cub *cub);

#endif

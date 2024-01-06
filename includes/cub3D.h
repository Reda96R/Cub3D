/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:54:28 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/06 03:30:07 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "m_get_next_line.h"
# include "structs.h"
# include "cub_macros.h"
# include "../mlx_linux/mlx.h"
// # include <mlx.h>

# include <string.h> // Will be removed with memcpy()

typedef struct s_mlx
{
	float			win_x;
	float			win_y;
	float			cub_size;
	void			*mlx_ptr;
	void			*win_ptr;
	//char			map[MAP_Y][MAP_X];  //-----> check here  <-----//
	t_img			img;
	t_player		*player;
	t_pos			*pos;
	t_rays			*rays;
	/// ********* parsing **********//
	char			**full_file;
	char			**map;
	char			**new_map;
	int				map_height;
	int				map_width;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*c_color;
	char			*f_color;
	unsigned int	c_color_int;
	unsigned int	f_color_int;
}	t_mlx;

/*::::::::::::::::::::::::::::::::::*/
void	ft_error_buster(int id);

/*::::::::::::::::PRS:::::::::::::::*/
int		get_map_size(t_mlx *mlx);
void	get_file(t_mlx *mlx, char *file);
void	get_texters(t_mlx *mlx);
void	is_deplecate(t_mlx *mlx);
void	ft_free(char **str);
void	textres_existence(t_mlx *mlx, char *str);
void	colors_existence(t_mlx *mlx);
void	ft_Error(char *str, t_mlx *mlx);
void	check_map_format(t_mlx *mlx);
void	cheack_map_borders(t_mlx *mlx);
void	check_map_is_locked(t_mlx *mlx);
void	check_colors_format(char	*str, t_mlx *mlx);
void	check_colors_range(char	*str, t_mlx *mlx);
void	ft_free_all(t_mlx *mlx);
void	enitialize(t_mlx *mlx);
void	is_palyer_deplicate(t_mlx *mlx);
void	map_height_width(t_mlx *mlx);
void	copy_map(t_mlx *mlx);
/*::::::::::::::::RAY:::::::::::::::*/

			/*---ft_starter---*/
t_mlx	*ft_data_init(void);
void	ft_player_init(t_player **player);
void	ft_rays_init(t_rays **rays, t_mlx *mlx);

			/*---ft_starter---*/
void	ft_prime_and_cast(t_mlx *mlx);
void	ft_ray_igniter(t_mlx *mlx, int color);

			/*---ft_drawer---*/
int		update(t_mlx *mlx);
void	ft_put_pixel(t_mlx *mlx, int x, int y, int color);
void	ft_clear_map(t_mlx *mlx);
void	ft_draw_map(t_mlx *mlx);
void	ft_clear_player(t_mlx *mlx, int x, int y, int size);
void	ft_draw_player(t_mlx *mlx, int x, int y);

			/*---ft_player_movements---*/
void	ft_move_front(t_mlx *mlx);
void	ft_move_back(t_mlx *mlx);
void	ft_move_left(t_mlx *mlx);
void	ft_move_right(t_mlx *mlx);

			/*---ft_shapes---*/
void	ft_draw_line(t_mlx *mlx, float c[4], int color);
void	ft_draw_circle(t_mlx *mlx, int x, int y);
void	ft_draw_square(t_mlx *mlx, int x, int y, int color);
void	ft_draw_rectangle(t_mlx *mlx, t_pos *coordinates, float w, float h);
void	ft_draw_scaled_square(t_mlx *mlx, int x, int y, int color);

			/*---ft_keylogger---*/
int		ft_cross(int key, t_mlx *mlx);
int		ft_key_press(int keycode, t_mlx *mlx);
int		ft_key_release(int keycode, t_mlx *mlx);

			/*---ft_maths_hub0---*/
int		ft_wall_colision(t_mlx *mlx);
int		ft_wall_detector(float x, float y, t_mlx *mlx);
void	ft_pos_calculator(t_mlx *mlx);
void	ft_move_calculator(t_mlx *mlx);
void	ft_turn_calculator(t_mlx *mlx);

			/*---ft_maths_hub1---*/
float	ft_hit_distance(float *coor, t_mlx *mlx);
void	ft_h_hit_calculator(t_mlx *mlx, t_rays *h);
void	ft_v_hit_calculator(t_mlx *mlx, t_rays *v);
void	ft_vertical_detector(t_mlx *mlx, t_rays *v);
void	ft_horizontal_detector(t_mlx *mlx, t_rays *h);

#endif

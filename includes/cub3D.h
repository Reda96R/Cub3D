/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:54:28 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/21 17:54:30 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "structs.h"
# include "cub_macros.h"
// # include <mlx.h>

# include <string.h> // Will be removed

typedef struct s_mlx
{
	float			win_x;
	float			win_y;
	float			cub_size;
	void			*mlx_ptr;
	void			*win_ptr;
	char			map[MAP_Y][MAP_X];
	t_img			img;
	t_player		*player;
	t_pos			*pos;
	t_rays			*rays;
}	t_mlx;

/*::::::::::::::::PRS:::::::::::::::*/

/*::::::::::::::::RAY:::::::::::::::*/

			/*---ft_starter---*/
t_mlx	*ft_data_init(void);
void	ft_player_init(t_player **player, int x, int y);
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
void	ft_draw_rectangle(t_mlx *mlx, float rect_x, float rect_y, float w, float h);

			/*---ft_player_movements---*/
void	ft_move_front(t_mlx *mlx);
void	ft_move_back(t_mlx *mlx);
void	ft_move_left(t_mlx *mlx);
void	ft_move_right(t_mlx *mlx);

			/*---ft_shapes---*/
void	ft_draw_line(t_mlx *mlx, float c[4], int color);
void	ft_draw_circle(t_mlx *mlx, int x, int y);
void	ft_draw_square(t_mlx *mlx, int x, int y, int color);
void	ft_draw_scaled_square(t_mlx *mlx, int x, int y, int color);

			/*---ft_keylogger---*/
int		ft_cross(int key, t_mlx *mlx);
int		ft_key_press(int keycode, t_mlx *mlx);
int		ft_key_release(int keycode, t_mlx *mlx);

			/*---ft_maths_hub0---*/
void	ft_pos_calculator(t_mlx *mlx);
void	ft_move_calculator(t_mlx *mlx);
void	ft_turn_calculator(t_mlx *mlx);
int		ft_wall_colision(t_mlx *mlx);
int		ft_wall_detector(float x, float y, char map[MAP_Y][MAP_X], t_mlx* mlx);

			/*---ft_maths_hub1---*/
float	ft_hit_distance(float *coor, t_mlx *mlx);
void	ft_h_hit_calculator(t_mlx *mlx, t_rays *h);
void	ft_v_hit_calculator(t_mlx *mlx, t_rays *v);
void	ft_vertical_detector(t_mlx *mlx, t_rays *v);
void	ft_horizontal_detector(t_mlx *mlx, t_rays *h);

#endif

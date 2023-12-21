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
	void			*mlx_ptr;
	void			*win_ptr;
	char			map[MAP_Y][MAP_X];
	t_img			img;
	t_player		*player;
	t_pos			*pos;
}	t_mlx;

/*::::::::::::::::PRS:::::::::::::::*/

/*::::::::::::::::RAY:::::::::::::::*/

			/*---ft_starter---*/
t_mlx	*ft_game_init(void);
void	ft_player_init(t_player **player, int x, int y);

			/*---ft_drawer---*/
void	ft_put_pixel(t_mlx *mlx, int x, int y, int color);
void	ft_clear_map(t_mlx *mlx);
void	ft_draw_map(t_mlx *mlx);
void	ft_clear_player(t_mlx *mlx, int x, int y, int size);
void	ft_draw_player(t_mlx *mlx, int x, int y);

			/*---ft_shapes---*/
void	ft_draw_line(t_mlx *mlx, float c[4]);
void	ft_draw_circle(t_mlx *mlx, int x, int y);
void	ft_draw_square(t_mlx *mlx, int x, int y, int color);

			/*---ft_keylogger---*/
int		ft_key_press(int keycode, t_mlx *mlx);
int		ft_key_release(int keycode, t_mlx *mlx);

			/*---ft_math_hub---*/
int		ft_wall_detector(float x, float y, char test[7][9]);
int		ft_pos_calculator(t_mlx *mlx);
int		update(t_mlx *mlx);

#endif

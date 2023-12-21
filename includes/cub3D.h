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

# include <string.h>

typedef struct s_mlx
{
	unsigned int	height;
	unsigned int	width;
	int				win_x;
	int				win_y;
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	t_player		*player;
	t_pos			*pos;
	char			test[MAP_Y][MAP_X];
}	t_mlx;

/*::::::::::::::::PRS:::::::::::::::*/

/*::::::::::::::::RAY:::::::::::::::*/

			/*---ft_shapes---*/
void	ft_draw_line(t_mlx *mlx, float x0, float y0, float x1, float y1);
void	ft_draw_circle(t_mlx *mlx, int x, int y);
void	ft_draw_square(t_mlx *mlx, int x, int y, int color);

			/*---ft_keylogger---*/
int		ft_key_press(int keycode, t_mlx *mlx);
int		ft_key_release(int keycode, t_mlx *mlx);

			/*---ft_drawer---*/
void	ft_put_pixel(t_mlx *mlx, int x, int y, int color);
void	ft_clear_map(t_mlx *mlx);
void	ft_draw_map(t_mlx *mlx);
void	ft_clear_player(t_mlx *mlx, int x, int y, int size);
void	ft_draw_player(t_mlx *mlx, int x, int y);

#endif

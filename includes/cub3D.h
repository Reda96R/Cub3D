#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
// # include "../mlx_linux/mlx.h"
# include <mlx.h>

typedef struct s_img
{
	void	*img;
	char	*id;
	int		endian;
	int		bpp;
	int		len;
}	t_img;

typedef struct s_player
{
	int	x;
	int	y;
	int	turn;
	int	walk;
	int	rot;
	int	spd;
}	t_player;

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
}	t_mlx;

#endif

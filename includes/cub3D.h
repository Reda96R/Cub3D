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
	int		m_f;
	int		m_b;
	int		m_r;
	int		m_l;
	int		t_r;
	int		t_l;
	float	x;
	float	y;
	float	r;
	float	turn;
	float	walk;
	float	spd;
	float	rot;
	float	rot_spd;
}	t_player;

typedef struct s_pos {
	float	x;
	float	y;
	float	rot;
}	t_pos;

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
}	t_mlx;

#endif

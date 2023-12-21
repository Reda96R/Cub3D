#include "../../includes/cub3D.h"

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (mlx->win_x > x && mlx->win_y > y && x >= 0 && y >= 0)
	{
		p = mlx->img.id + (y * mlx->img.len + x * (mlx->img.bpp / 8));
		*(int *)p = color;
	}
}

void	ft_clear_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (i < MAP_Y)
	{
		x = 0;
		j = 0;
		while (j < MAP_X)
		{
			ft_draw_square(mlx, x, y, 0x000000);
			x += CUB_SIZE;
			j++;
		}
		y += CUB_SIZE;
		i++;
	}
}

void	ft_draw_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	x;
	int	y;

	ft_clear_map(mlx);
	i = 0;
	y = 0;
	while (i < MAP_Y)
	{
		x = 0;
		j = 0;
		while (j < MAP_X)
		{
			if (mlx->test[i][j] != '0')
				ft_draw_square(mlx, x, y, 0xFFFFFF);
			else
				ft_draw_square(mlx, x, y, 0x000000);
			x += CUB_SIZE + SPACE;
			j++;
		}
		y += CUB_SIZE + SPACE;
		i++;
	}
}

void	ft_clear_player(t_mlx *mlx, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_put_pixel(mlx, x + i, y + j, 0x000000);
			j++;
		}
		i++;
	}
}

void	ft_draw_player(t_mlx *mlx, int x, int y)
{
	int	xf;
	int	yf;

	xf = x + cos (mlx->player->rot) * (mlx->player->r * 2);
	yf = y + sin (mlx->player->rot) * (mlx->player->r * 2);
	ft_draw_circle(mlx, x, y);
	ft_draw_line(mlx, x, y, xf, yf);
}

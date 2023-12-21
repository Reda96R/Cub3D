#include "../../includes/cub3D.h"

void	ft_draw_line(t_mlx *mlx, float x0, float y0, float x1, float y1)
{
	float	max;

	max = fmax(fabs(x1 - x0), fabs(y1 - y0));
	while (max >= 0)
	{
		ft_put_pixel(mlx, x0, y0, 0xFFFF00);
		x0 += (x1 - x0) / (float) max;
		y0 += (y1 - y0) / (float) max;
		max--;
	}
}

void	ft_draw_circle(t_mlx *mlx, int x, int y)
{
	int	i;
	int	j;
	int	dx;
	int	dy;

	i = x - mlx->player->r;
	while (i <= x + mlx->player->r)
	{
		j = y - mlx->player->r;
		while (j <= y + mlx->player->r)
		{
			dx = i - x;
			dy = j - y;
			if (dx * dx + dy * dy <= mlx->player->r * mlx->player->r)
				ft_put_pixel(mlx, i, j, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	ft_draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (w < CUB_SIZE)
	{
		h = 0;
		while (h < CUB_SIZE)
		{
			ft_put_pixel(mlx, x + w, y + h, color);
			h++;
		}
		w++;
	}
}

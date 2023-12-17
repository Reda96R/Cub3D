/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:26:16 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/16 15:26:19 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define MAP_X 4
#define MAP_Y 4
#define TILE 32

#define WIN_X 320
#define WIN_Y 320

int	g_size = (800 - 5 * 2) / 4;
int	g_test[][4] = {
{1, 1, 1, 1},
{1, 0, 0, 1},
{1, 0, 0, 1},
{1, 1, 1, 1}
};

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (mlx->win_x > x && mlx->win_y > y && x >= 0 && y >= 0)
	{
		p = mlx->img.id + (y * mlx->img.len + x * (mlx->img.bpp / 8));
		*(int *)p = color;
	}
}

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (w < g_size)
	{
		h = 0;
		while (h < g_size)
		{
			ft_put_pixel(mlx, x + w, y + h, color);
			h++;
		}
		w++;
	}
}

void	ft_draw_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;

	i = 0;
	y = 0;
	while (i < 4)
	{
		x = 0;
		j = 0;
		while (j < 4)
		{
			if (g_test[i][j])
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(mlx, x, y, color);
			x += g_size + 2;
			j++;
			printf("test\n");
		}
		y += g_size + 2;
		i++;
	}
}
int	ft_canvas_maker(t_mlx *mlx)

{
	mlx->win_x = 800;
	mlx->win_y = 800;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = \
			mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y, "cub3D");
	if (!mlx->win_ptr)
		return (0);
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.id = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.len, \
	&mlx->img.endian);
	ft_draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	mlx_loop(mlx->mlx_ptr);
	return (1);
}

int	main(void)
{
	t_mlx	mlx;

	for (int x = 0; x < 4; x++){
		for (int y = 0; y < 4; y++)
			printf("%d", g_test[x][y]);
		printf("\n");
	}
	if (!ft_canvas_maker(&mlx))
		return (1);
	return (0);
}

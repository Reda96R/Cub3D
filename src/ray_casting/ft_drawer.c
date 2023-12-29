/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:52:45 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/21 17:52:48 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	update(t_mlx *mlx)
{
	ft_draw_map(mlx);
	ft_pos_calculator(mlx);
	ft_prime_and_cast(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	return (0);
}

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (mlx->win_x > x && mlx->win_y > y && x >= 0 && y >= 0)
	{
		p = mlx->img.id + (y * mlx->img.len + x * (mlx->img.bpp / 8));
		*(int *)p = color;
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
			if (mlx->map[i][j] != '0')
				ft_draw_square(mlx, x, y, 0xFFFFFF);
			else
				ft_draw_square(mlx, x, y, 0xFF000000);
			x += CUB_SIZE + SPACE;
			j++;
		}
		y += CUB_SIZE + SPACE;
		i++;
	}
}

void	ft_draw_player(t_mlx *mlx, int x, int y)
{
	float	coordinates[4];
	float	xf;
	float	yf;

	xf = x + cos (mlx->player->rot) * mlx->rays->ray_size;
	yf = y + sin (mlx->player->rot) * mlx->rays->ray_size;
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = xf;
	coordinates[3] = yf;
	ft_draw_line(mlx, coordinates, 0xFFFF00);
	ft_draw_circle(mlx, x, y);
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

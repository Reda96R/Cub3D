/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shapes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:53:08 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/21 17:53:09 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_draw_line(t_mlx *mlx, float c[4], int color)
{
	float	max;

	max = fmax(fabs(c[2] - c[0]), fabs(c[3] - c[1]));
	while (max >= 0)
	{
		ft_put_pixel(mlx, c[0], c[1], color);
		c[0] += (c[2] - c[0]) / (float) max;
		c[1] += (c[3] - c[1]) / (float) max;
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

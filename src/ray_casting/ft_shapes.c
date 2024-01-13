/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shapes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:53:08 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/13 05:42:16 by maouzal          ###   ########.fr       */
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

	i = x - (mlx->player->r * MINIMAP_SCALE);
	while (i <= x + (mlx->player->r * MINIMAP_SCALE))
	{
		j = y - (mlx->player->r * MINIMAP_SCALE);
		while (j <= y + (mlx->player->r * MINIMAP_SCALE))
		{
			dx = i - x;
			dy = j - y;
			if (dx * dx + dy * dy <= (mlx->player->r) * (mlx->player->r))
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
	while (w < mlx->cub_size)
	{
		h = 0;
		while (h < mlx->cub_size)
		{
			ft_put_pixel(mlx, (x + w), (y + h), color);
			h++;
		}
		w++;
	}
}

void	ft_draw_rectangle(t_mlx *mlx, t_pos *coordinates,
		t_pos width_n_height, int color)
{
	int	x;
	int	y;

	x = coordinates->x;
	while (x < coordinates->x + width_n_height.x)
	{
		y = coordinates->y;
		while (y < coordinates->y + width_n_height.y)
			ft_put_pixel(mlx, x, y++, color);
		x++;
	}
}

void	ft_draw_textured_rectangle(t_mlx *mlx, t_pos *coordinates,
		t_pos width_n_height)
{
	int		x;
	int		y;
	int		color;
	float	scale;
	t_pos	*pos;

	pos = malloc(sizeof(t_pos));
	if (!pos)
		ft_error_buster(1);
	x = coordinates->x;
	//pos = culcul_coordinate(mlx, &width_n_height);
	while (x < coordinates->x + width_n_height.x)
	{
		if (mlx->rays->s == 'h')
		{
			pos->x = fmod((int)mlx->rays->hit_x, width_n_height.y);
			pos->y = fmod((int)mlx->rays->hit_y * (int)mlx->cub_size , width_n_height.x);
		}
		else
		{
			pos->x = fmod((int)mlx->rays->hit_y, width_n_height.y);
			pos->y = fmod((int)mlx->rays->hit_x * (int)mlx->cub_size , width_n_height.x);
		}
		// printf("hit_y = %f\n", mlx->rays->hit_y);
		// printf("hit_x = %f\n", mlx->rays->hit_x);
		// printf("pos->x = %f\n", pos->x);
		// printf("cube_size = %f\n", mlx->cub_size);
		// printf("width_n_height.x = %f\n", width_n_height.x);
		// printf("width_n_height.y = %f\n", width_n_height.y);
		// printf("---------->pos->y = %f\n", pos->y);
		y = coordinates->y;
		while (y < coordinates->y + width_n_height.y)
		{
			//TODO: finding the y coordinate aka pos->y
			scale = y - (mlx->win_y) / 2 + width_n_height.y / 2;
			pos->y = (scale * mlx->cub_size / width_n_height.y);
			// pos->y = y * (mlx->cub_size / width_n_height.y);
			color = my_mlx_pixel_get(mlx, pos->x, pos->y);
			ft_put_pixel(mlx, x, y++, color);
		}
		x++;
	}
	free (pos);
}

void	ft_draw_scaled_square(t_mlx *mlx, int x, int y, int color)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (w < mlx->cub_size)
	{
		h = 0;
		while (h < mlx->cub_size)
		{
			ft_put_pixel(mlx, (x + w) * MINIMAP_SCALE,
				(y + h) * MINIMAP_SCALE, color);
			h++;
		}
		w++;
	}
}

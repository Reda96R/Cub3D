/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <rerayyad@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:52:45 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/09 17:36:58 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	update(t_mlx *mlx)
{
	ft_scene_cleaner(mlx);
	ft_pos_calculator(mlx);
	ft_draw_map(mlx);// will be removed in mandatory
	ft_prime_and_cast(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);// will be removed in mandatory
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	return (0);
}

void	ft_scene_cleaner(t_mlx *mlx)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (w < mlx->win_x)
	{
		h = 0;
		while (h < mlx->win_y)
		{
			ft_put_pixel(mlx, w, h, 0x000000);
			h++;
		}
		w++;
	}
}

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (mlx->win_x > x && mlx->win_y > y && x >= 0 && y >= 0)
	{
		p = mlx->img.id + (y * mlx->img.len + x * (mlx->img.bpp / 8));
		*(unsigned int *)p = color;
	}
}

void	ft_draw_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (mlx->new_map[i] && i < mlx->map_height)
	{
		x = 0;
		j = 0;
		while (mlx->new_map[i][j] && j < mlx->map_width)
		{
			if (mlx->new_map[i][j] == '1')
				ft_draw_scaled_square(mlx, x, y, 0xFFFFFF);
			else if (mlx->new_map[i][j] == 'D')
				ft_draw_scaled_square(mlx, x, y, 0xCCFF00);
			else
				ft_draw_scaled_square(mlx, x, y, 0x000000);
			x += mlx->cub_size + SPACE;
			j++;
		}
		y += mlx->cub_size + SPACE;
		i++;
	}
}

void	ft_draw_player(t_mlx *mlx, int x, int y)
{
	float	coordinates[4];
	float	xf;
	float	yf;

	mlx->player->r = (mlx->cub_size * MINIMAP_SCALE) / 5;
	mlx->player->spd = SPEED * (mlx->cub_size / 40);
	mlx->player->rot_spd = (ROT_SPEED * (M_PI / 180)) * (mlx->cub_size / 40);
	xf = x + cos (mlx->player->rot) * mlx->cub_size;
	yf = y + sin (mlx->player->rot) * mlx->cub_size;
	coordinates[0] = x * MINIMAP_SCALE;
	coordinates[1] = y * MINIMAP_SCALE;
	coordinates[2] = xf * MINIMAP_SCALE;
	coordinates[3] = yf * MINIMAP_SCALE;
	ft_draw_line(mlx, coordinates, 0xFFFF00);
	ft_draw_circle(mlx, x * MINIMAP_SCALE, y * MINIMAP_SCALE);
}

// Will be removed later
void	ft_clear_map(t_mlx *mlx)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (i < mlx->map_height)
	{
		x = 0;
		j = 0;
		while (j < mlx->map_width)
		{
			ft_draw_scaled_square(mlx, x, y, 0x000000);
			x += mlx->cub_size;
			j++;
		}
		y += mlx->cub_size;
		i++;
	}
}

// Will be removed later
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

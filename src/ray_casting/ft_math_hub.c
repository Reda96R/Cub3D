/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:53:03 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/21 17:53:04 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_wall_detector(float x, float y, char test[7][9])
{
	int	map_x;
	int	map_y;

	map_x = floor(y / CUB_SIZE);
	map_y = floor(x / CUB_SIZE);
	if (test[map_x][map_y] == '0')
		return (0);
	return (1);
}

int	ft_pos_calculator(t_mlx *mlx)
{
	float	x;
	float	y;

	x = mlx->player->x;
	y = mlx->player->y;
	if (mlx->player->m_f)
	{
		mlx->player->x += cos(mlx->player->rot) * mlx->player->spd;
		mlx->player->y += sin(mlx->player->rot) * mlx->player->spd;
	}
	if (mlx->player->m_b)
	{
		mlx->player->x -= cos(mlx->player->rot) * mlx->player->spd;
		mlx->player->y -= sin(mlx->player->rot) * mlx->player->spd;
	}
	if (mlx->player->m_l)
	{
		mlx->player->x -= cos(mlx->player->rot + M_PI_2) * mlx->player->spd;
		mlx->player->y -= sin(mlx->player->rot + M_PI_2) * mlx->player->spd;
	}
	if (mlx->player->m_r)
	{
		mlx->player->x += cos(mlx->player->rot + M_PI_2) * mlx->player->spd;
		mlx->player->y += sin(mlx->player->rot + M_PI_2) * mlx->player->spd;
	}
	if (mlx->player->t_l)
		mlx->player->rot -= mlx->player->rot_spd;
	if (mlx->player->t_r)
		mlx->player->rot += mlx->player->rot_spd;
	if (ft_wall_detector(mlx->player->x, mlx->player->y, mlx->map))
	{
		mlx->player->x = x;
		mlx->player->y = y;
	}
	return (1);
}

int	update(t_mlx *mlx)
{
	ft_draw_map(mlx);
	ft_pos_calculator(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	return (0);
}

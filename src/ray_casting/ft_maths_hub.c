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

int	ft_wall_detector(float x, float y, char map[MAP_Y][MAP_X])
{
	int	map_x;
	int	map_y;

	map_x = floor(y / CUB_SIZE);
	map_y = floor(x / CUB_SIZE);
	if (map[map_x][map_y] == '0')
		return (0);
	return (1);
}

void	ft_turn_calculator(t_mlx *mlx)
{
	if (mlx->player->t_l)
		mlx->player->rot -= mlx->player->rot_spd;
	if (mlx->player->t_r)
		mlx->player->rot += mlx->player->rot_spd;
}

void	ft_move_calculator(t_mlx *mlx)
{
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
}

void	ft_pos_calculator(t_mlx *mlx)
{
	float	x;
	float	y;

	x = mlx->player->x;
	y = mlx->player->y;
	if (mlx->player->m_f || mlx->player->m_b || \
		mlx->player->m_l || mlx->player->m_r)
		ft_move_calculator(mlx);
	if (mlx->player->t_l || mlx->player->t_r)
		ft_turn_calculator(mlx);
	if (ft_wall_detector(mlx->player->x, mlx->player->y, mlx->map))
	{
		mlx->player->x = x;
		mlx->player->y = y;
	}
}

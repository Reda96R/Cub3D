/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths_hub0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <rerayyad@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:53:03 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/09 23:45:39 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_wall_detector(float x, float y, t_mlx *mlx)
{
	int	map_x;
	int	map_y;

	map_x = floor(y / mlx->cub_size);
	map_y = floor(x / mlx->cub_size);
	// here i added the condition to check if the map_x (!mlx->new_map)  is not out of bounds (it was causing a segfault)
	// you just need to check the minimap ;)
	if (map_x < 0 || map_y < 0 || map_x >= mlx->map_height || !mlx->new_map[map_x]
		|| map_y >= mlx->map_width || !mlx->new_map[map_x][map_y])
		return (1);
	if (mlx->new_map[map_x][map_y] == '0')
		return (0);
	else if (mlx->new_map[map_x][map_y] == 'D')
		return ('d');
	return (1);
}

int	ft_wall_colision(t_mlx *mlx)
{
	int	i;
	int	j;
	int	dx;
	int	dy;

	i = mlx->player->x - (mlx->player->r * MINIMAP_SCALE);
	while (i <= mlx->player->x + (mlx->player->r * MINIMAP_SCALE))
	{
		j = mlx->player->y - (mlx->player->r * MINIMAP_SCALE);
		while (j <= mlx->player->y + (mlx->player->r * MINIMAP_SCALE))
		{
			dx = i - mlx->player->x;
			dy = j - mlx->player->y;
			if (dx * dx + dy * dy <= mlx->player->r * mlx->player->r)
				if (ft_wall_detector(i, j, mlx))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
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
		ft_move_front(mlx);
	if (mlx->player->m_b)
		ft_move_back(mlx);
	if (mlx->player->m_l)
		ft_move_left(mlx);
	if (mlx->player->m_r)
		ft_move_right(mlx);
}

void	ft_pos_calculator(t_mlx *mlx)
{
	if (mlx->player->m_f || mlx->player->m_b || \
		mlx->player->m_l || mlx->player->m_r)
		ft_move_calculator(mlx);
	if (mlx->player->t_l || mlx->player->t_r)
		ft_turn_calculator(mlx);
}

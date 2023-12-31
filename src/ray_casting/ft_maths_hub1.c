/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths_hub1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:04:20 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/30 12:04:21 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float	ft_hit_distance(float *coor, t_mlx *mlx)
{
	return (sqrt((coor[0] - mlx->player->x) * (coor[0] - mlx->player->x)
			+ (coor[1] - mlx->player->y) * (coor[1] - mlx->player->y)));
}

void	ft_h_hit_calculator(t_mlx *mlx, t_rays *h)
{
	float	y;

	h->hit_y = floor (mlx->player->y / (CUB_SIZE + SPACE)) * (CUB_SIZE + SPACE);
	if (!mlx->rays->up)
		h->hit_y += (CUB_SIZE + SPACE);
	h->hit_x = ((h->hit_y - mlx->player->y) / tan(mlx->rays->ray_angle))
		+ mlx->player->x;
	while (h->hit_x >= 0 && h->hit_x <= mlx->win_x
		&& h->hit_y >= 0 && h->hit_y <= mlx->win_y)
	{
		y = h->hit_y;
		if (mlx->rays->up)
			y -= (SPACE + 3);
		if (ft_wall_detector(h->hit_x, y, mlx->map))
			break ;
		h->hit_x += h->diff[0];
		h->hit_y += h->diff[1];
	}
}

void	ft_v_hit_calculator(t_mlx *mlx, t_rays *v)
{
	float	x;

	v->hit_x = floor (mlx->player->x / (CUB_SIZE + SPACE)) * (CUB_SIZE + SPACE);
	if (mlx->rays->right)
		v->hit_x += (CUB_SIZE + SPACE);
	v->hit_y = ((v->hit_x - mlx->player->x) * tan(mlx->rays->ray_angle))
		+ mlx->player->y;
	while (v->hit_x >= 0 && v->hit_x <= mlx->win_x
		&& v->hit_y >= 0 && v->hit_y <= mlx->win_y)
	{
		x = v->hit_x;
		if (!mlx->rays->right)
			x -= (SPACE + 3);
		if (ft_wall_detector(x, v->hit_y, mlx->map))
			break ;
		v->hit_x += v->diff[0];
		v->hit_y += v->diff[1];
	}
}

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

// float	ft_wall_nspection()
// {
// }

void	ft_h_hit_calculator(t_mlx *mlx, t_rays *h, char *heading, int *door)
{
	float	y;

	h->hit_y = floor (mlx->player->y / (mlx->cub_size + SPACE))
		* (mlx->cub_size + SPACE);
	if (!mlx->rays->up)
		h->hit_y += (mlx->cub_size + SPACE);
	h->hit_x = ((h->hit_y - mlx->player->y) / tan(mlx->rays->ray_angle))
		+ mlx->player->x;
	while (h->hit_x >= 0 && h->hit_x <= mlx->win_x
		&& h->hit_y >= 0 && h->hit_y <= mlx->win_y)
	{
		y = h->hit_y;
		if (mlx->rays->up)
			y -= (SPACE + 1);
		else if (!mlx->rays->up)
			y += (SPACE + 1);
		if (ft_wall_detector(h->hit_x, y, mlx))
		{
			if (mlx->rays->up)
				*heading = 'S';
			else
				*heading = 'N';
			if (ft_wall_detector(h->hit_x, y, mlx) == 'd')
				*door = 1;
			break ;
		}
		h->hit_x += h->diff[0];
		h->hit_y += h->diff[1];
	}
}

void	ft_v_hit_calculator(t_mlx *mlx, t_rays *v, char *heading, int *door)
{
	float	x;

	v->hit_x = floor (mlx->player->x / (mlx->cub_size + SPACE))
		* (mlx->cub_size + SPACE);
	if (mlx->rays->right)
		v->hit_x += (mlx->cub_size + SPACE);
	v->hit_y = ((v->hit_x - mlx->player->x) * tan(mlx->rays->ray_angle))
		+ mlx->player->y;
	while (v->hit_x >= 0 && v->hit_x <= mlx->win_x
		&& v->hit_y >= 0 && v->hit_y <= mlx->win_y)
	{
		x = v->hit_x;
		if (!mlx->rays->right)
			x -= (SPACE + 0.05);
		if (mlx->rays->right)
			x += (SPACE + 0.05);
		if (ft_wall_detector(x, v->hit_y, mlx))
		{
			if (mlx->rays->right)
				*heading = 'W';
			else
				*heading = 'E';
			if (ft_wall_detector(x, v->hit_y, mlx) == 'd')
				*door = 1;
			break ;
		}
		v->hit_x += v->diff[0];
		v->hit_y += v->diff[1];
	}
}

void	ft_vertical_detector(t_mlx *mlx, t_rays *v)
{
	float	diff[2];
	float	coor[2];

	diff[0] = mlx->cub_size + SPACE;
	if (!mlx->rays->right)
		diff[0] *= -1;
	diff[1] = (mlx->cub_size + SPACE) * tan(mlx->rays->ray_angle);
	if ((mlx->rays->up && diff[1] > 0) || (!mlx->rays->up && diff[1] < 0))
		diff[1] *= -1;
	v->diff[0] = diff[0];
	v->diff[1] = diff[1];
	v->door = 0;
	ft_v_hit_calculator(mlx, v, &v->heading, &v->door);
	coor[0] = v->hit_x;
	coor[1] = v->hit_y;
	v->colision_distance = ft_hit_distance(coor, mlx);
	if (v->door)
		v->colision_distance += mlx->cub_size / 2;
	v->s = 'v';
}

void	ft_horizontal_detector(t_mlx *mlx, t_rays *h)
{
	float	diff[2];
	float	coor[2];

	diff[1] = mlx->cub_size + SPACE;
	if (mlx->rays->up)
		diff[1] *= -1;
	diff[0] = (mlx->cub_size + SPACE) / tan(mlx->rays->ray_angle);
	if ((mlx->rays->right && diff[0] < 0) || (!mlx->rays->right && diff[0] > 0))
		diff[0] *= -1;
	h->diff[0] = diff[0];
	h->diff[1] = diff[1];
	h->door = 0;
	ft_h_hit_calculator(mlx, h, &h->heading, &h->door);
	coor[0] = h->hit_x;
	coor[1] = h->hit_y;
	h->colision_distance = ft_hit_distance(coor, mlx);
	if (h->door)
		h->colision_distance += mlx->cub_size / 2;
	h->s = 'h';
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:43:20 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/22 10:43:22 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_ray_igniter(t_mlx *mlx, int color)
{
	float	cord[4];

	cord[0] = mlx->player->x * MINIMAP_SCALE;
	cord[1] = mlx->player->y * MINIMAP_SCALE;
	cord[2] = mlx->rays->hit_x * MINIMAP_SCALE;
	cord[3] = mlx->rays->hit_y * MINIMAP_SCALE;
	ft_draw_line(mlx, cord, color);
}

void	ft_vertical_detector(t_mlx *mlx, t_rays *v)
{
	float	diff[2];
	float	coor[2];

	diff[0] = CUB_SIZE + SPACE;
	if (!mlx->rays->right)
		diff[0] *= -1;
	diff[1] = (CUB_SIZE + SPACE) * tan(mlx->rays->ray_angle);
	if ((mlx->rays->up && diff[1] > 0) || (!mlx->rays->up && diff[1] < 0))
		diff[1] *= -1;
	v->diff[0] = diff[0];
	v->diff[1] = diff[1];
	ft_v_hit_calculator(mlx, v);
	coor[0] = v->hit_x;
	coor[1] = v->hit_y;
	v->colision_distance = ft_hit_distance(coor, mlx);
}

void	ft_horizontal_detector(t_mlx *mlx, t_rays *h)
{
	float	diff[2];
	float	coor[2];

	diff[1] = CUB_SIZE + SPACE;
	if (mlx->rays->up)
		diff[1] *= -1;
	diff[0] = (CUB_SIZE + SPACE) / tan(mlx->rays->ray_angle);
	if ((mlx->rays->right && diff[0] < 0) || (!mlx->rays->right && diff[0] > 0))
		diff[0] *= -1;
	h->diff[0] = diff[0];
	h->diff[1] = diff[1];
	ft_h_hit_calculator(mlx, h);
	coor[0] = h->hit_x;
	coor[1] = h->hit_y;
	h->colision_distance = ft_hit_distance(coor, mlx);
}

void	ft_hit_detector(t_mlx *mlx)
{
	t_rays	*h;
	t_rays	*v;

	h = malloc(sizeof (t_rays));
	v = malloc(sizeof (t_rays));
	mlx->rays->up = mlx->rays->ray_angle > 0 && mlx->rays->ray_angle > M_PI;
	mlx->rays->right = mlx->rays->ray_angle <= M_PI_2
		|| mlx->rays->ray_angle >= (3 * M_PI_2);
	ft_horizontal_detector(mlx, h);
	ft_vertical_detector(mlx, v);
	if (h->colision_distance < v->colision_distance)
	{
		mlx->rays->hit_x = h->hit_x;
		mlx->rays->hit_y = h->hit_y;
		mlx->rays->colision_distance = h->colision_distance;
	}
	else
	{
		mlx->rays->hit_x = v->hit_x;
		mlx->rays->hit_y = v->hit_y;
		mlx->rays->colision_distance = v->colision_distance;
	}
	free (h);
	free (v);
}

void	ft_3d_caster(t_mlx *mlx, int i)
{
	float	wall_height;
	float	project;

	project = (mlx->win_x / 2) / tan(mlx->player->fov / 2);
	wall_height = ((CUB_SIZE + SPACE) / mlx->rays->colision_distance) * project;
	ft_draw_rectangle(mlx, i, (mlx->win_y / 2) - (wall_height / 2), 1, wall_height);
}

void	ft_prime_and_cast(t_mlx *mlx)
{
	int		i;

	i = 0;
	mlx->rays->ray_angle = mlx->player->rot - (mlx->player->fov / 2);
	while (i < mlx->rays->rays_num)
	{
		mlx->rays->ray_angle = fmod(mlx->rays->ray_angle, (2 * M_PI));
		if (mlx->rays->ray_angle < 0)
			mlx->rays->ray_angle += (2 * M_PI);
		ft_hit_detector(mlx);
		ft_ray_igniter(mlx, 0x0000070); // color will be removed && will be removed in mandatory
		ft_3d_caster(mlx, i);
		mlx->rays->ray_angle += mlx->player->fov / mlx->rays->rays_num;
		i++;
	}
}

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

void	ft_ray_igniter(t_mlx *mlx, float ray_angle)
{
	float	cord[4];

	cord[0] = mlx->player->x;
	cord[1] = mlx->player->y;
	cord[2] = mlx->player->x + cos(ray_angle) * mlx->rays->ray_size;
	cord[3] = mlx->player->y + sin(ray_angle) * mlx->rays->ray_size;
	ft_draw_line(mlx, cord, 0xFF999980);
}

void	ft_ray_caster(t_mlx *mlx, float ray_angle)
{
	float	inter_cor[2];
	float	diff[2];
	float	next_cor[2];
	float	test[4];

	inter_cor[1] = floor(mlx->player->y / CUB_SIZE) * CUB_SIZE;
	if (!mlx->rays->up)
		inter_cor[1] += CUB_SIZE;
	inter_cor[0] = (inter_cor[1] - mlx->player->y) / tan(ray_angle) + mlx->player->x; // Check if -iy or -player->x
	diff[1] = CUB_SIZE + SPACE;
	if (mlx->rays->up)
		diff[1] *= -1;
	diff[0] = CUB_SIZE / tan(ray_angle) + SPACE;
	if ((!mlx->rays->right && diff[0] > 0) || (mlx->rays->right && diff[0] < 0))// reverify
		diff[0] *= -1;
	next_cor[0] = inter_cor[0];
	next_cor[1] = inter_cor[1];
	if (mlx->rays->up)
		next_cor[1]--;
	while (next_cor[0] >= 0 && next_cor[0] <= mlx->win_x && next_cor[1] >= 0 && next_cor[1] <= mlx->win_y)
	{
		if (ft_wall_detector(next_cor[0], next_cor[1], mlx->map))
		{
			test[0] = mlx->player->x + cos(ray_angle);
			test[1] = mlx->player->y + sin(ray_angle);
			test[2] = next_cor[0];
			test[3] = next_cor[1];
			ft_draw_line(mlx, test, 0xFF0000);
			break ;
		}
		next_cor[0] += diff[0];
		next_cor[1] += diff[1];
	}
}

void	ft_prime_and_cast(t_mlx *mlx)
{
	int		i;

	i = 0;
	mlx->rays->ray_angle = mlx->player->rot - (mlx->player->fov / 2);
	mlx->rays->ray_angle = fmod(mlx->rays->ray_angle, (2 * M_PI)); // Limiting the angle
	if (mlx->rays->ray_angle < 0)
		mlx->rays->ray_angle += (2 * M_PI);
	mlx->rays->up = mlx->rays->ray_angle > 0 && mlx->rays->ray_angle > M_PI;
	mlx->rays->right = mlx->rays->ray_angle < M_PI_2 || mlx->rays->ray_angle > (3 * M_PI_2); // Check more about ||
	if (mlx->rays->ray_angle < 0)
		mlx->rays->ray_angle += (2 * M_PI);
	while (i < 1)//mlx->rays->rays_num)
	{
		ft_ray_igniter(mlx, mlx->rays->ray_angle);
		ft_ray_caster(mlx, mlx->rays->ray_angle);
		mlx->rays->ray_angle += mlx->player->fov / mlx->rays->rays_num;
		i++;
	}
}

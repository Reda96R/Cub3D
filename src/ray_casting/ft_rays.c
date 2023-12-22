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

void	ft_prime_and_cast(t_mlx *mlx)
{
	float	ray_angle;
	int		i;

	i = 0;
	ray_angle = mlx->player->rot - (mlx->player->fov / 2);
	while (i < mlx->rays->rays_num)
	{
		ft_ray_igniter(mlx, ray_angle);
		ray_angle += mlx->player->fov / mlx->rays->rays_num;
		i++;
	}
}

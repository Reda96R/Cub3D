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
#include <math.h>
#include <stdlib.h>

void	ft_ray_igniter(t_mlx *mlx, int color)
{
	float	cord[4];

	cord[0] = mlx->player->x;
	cord[1] = mlx->player->y;
	cord[2] = mlx->rays->hit_x;
	cord[3] = mlx->rays->hit_y;
	// cord[2] = mlx->player->x + cos (mlx->rays->ray_angle) * 500;
	// cord[3] = mlx->player->y + sin (mlx->rays->ray_angle) * 500;
	ft_draw_line(mlx, cord, color);
}

// float	*ft_v_hit_calculator(t_mlx *mlx)
// {
// }
//
// void	ft_vertical_detector(t_mlx *mlx, t_rays *v)
// {
// }
//
void	ft_h_hit_calculator(t_mlx *mlx, t_rays *h)
{
	h->hit_y = (floor (mlx->player->y / (CUB_SIZE + SPACE)) * (CUB_SIZE + SPACE));
	if (!mlx->rays->up)
		h->hit_y += (CUB_SIZE + SPACE);
	h->hit_x = mlx->player->x + ((h->hit_y - mlx->player->y) / tan(mlx->rays->ray_angle));
	while (h->hit_x >= 0 && h->hit_x <= mlx->win_x
		&& h->hit_y >= 0 && h->hit_y <= mlx->win_y)
	{
		if (ft_wall_detector(h->hit_x, h->hit_y - (mlx->rays->up ? (SPACE + 3) : 0), mlx->map))
			break ;
		h->hit_x += h->diff[0];
		h->hit_y += h->diff[1];
	}
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

int	ft_hit_detector(t_mlx *mlx)
{
	t_rays	*h;
	// t_rays	*v;
	float	d[2];
	float	h_h[2];

	h = malloc(sizeof (t_rays));
	mlx->rays->up = mlx->rays->ray_angle > 0 && mlx->rays->ray_angle > M_PI;
	mlx->rays->right = mlx->rays->ray_angle <= M_PI_2 || mlx->rays->ray_angle >= (3 * M_PI_2);
	ft_horizontal_detector(mlx, h);
	// ft_vertical_detector(mlx, v);
	d[0] = mlx->player->x + cos (mlx->rays->ray_angle) * 200;
	d[1] = mlx->player->y + sin (mlx->rays->ray_angle) * 200;
	h_h[0] = h->hit_x;
	h_h[1] = h->hit_y;
	if (h->colision_distance < ft_hit_distance(d, mlx))
	{
		mlx->rays->hit_x = h_h[0];
		mlx->rays->hit_y = h_h[1];
		return (0x00FF00);
	}
	else
	{
		mlx->rays->hit_x = d[0];
		mlx->rays->hit_y = d[1];
		return (0xFF000000);
	}
	return (1);
}

void	ft_prime_and_cast(t_mlx *mlx)
{
	int		i;
	int		color;

	i = 0;
	mlx->rays->ray_angle = mlx->player->rot - (mlx->player->fov / 2);
	while (i < mlx->rays->rays_num)
	{
		mlx->rays->ray_angle = fmod(mlx->rays->ray_angle, (2 * M_PI));
		if (mlx->rays->ray_angle < 0)
			mlx->rays->ray_angle += (2 * M_PI);
		// printf("looking right--> %d\n", mlx->rays->right);
		// printf("looking up--> %d\n", mlx->rays->up);
		color = ft_hit_detector(mlx);
		ft_ray_igniter(mlx, color);
		mlx->rays->ray_angle += mlx->player->fov / mlx->rays->rays_num;
		i++;
	}
}

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

	(void)ray_angle;
	cord[0] = mlx->player->x;
	cord[1] = mlx->player->y;
	cord[2] = mlx->rays->hit_x;
	cord[3] = mlx->rays->hit_y;
	ft_draw_line(mlx, cord, 0xFF999980);
}

float	*ft_v_hit_calculator(t_mlx *mlx)
{
	float	inter_cor[2];
	float	diff[2];
	float	*ret;

	inter_cor[0] = floor (mlx->player->x / CUB_SIZE) * CUB_SIZE;
	if (!mlx->rays->up)
		inter_cor[0] += CUB_SIZE;
	inter_cor[1] = (inter_cor[0] - mlx->player->x) * tan(mlx->rays->ray_angle)
		+ mlx->player->y;
	diff[0] = CUB_SIZE + SPACE;
	if (!mlx->rays->right)
		diff[0] *= -1;
	diff[1] = CUB_SIZE * tan(mlx->rays->ray_angle) + SPACE;
	if ((mlx->rays->up && diff[1] > 0) || (!mlx->rays->up && diff[1] < 0))
		diff[1] *= -1;
	ret = malloc(sizeof(float) * 4);
	ret[0] = inter_cor[0];
	ret[1] = inter_cor[1];
	ret[2] = diff[0];
	ret[3] = diff[1];
	return (ret);
}

float	*ft_h_hit_calculator(t_mlx *mlx)
{
	float	inter_cor[2];
	float	diff[2];
	float	*ret;

	inter_cor[1] = floor (mlx->player->y / CUB_SIZE) * CUB_SIZE;
	if (!mlx->rays->up)
		inter_cor[1] += CUB_SIZE;
	inter_cor[0] = (inter_cor[1] - mlx->player->y) / tan(mlx->rays->ray_angle)
		+ mlx->player->x;
	diff[1] = CUB_SIZE + SPACE;
	if (mlx->rays->up)
		diff[1] *= -1;
	diff[0] = CUB_SIZE / tan(mlx->rays->ray_angle) + SPACE;
	if ((!mlx->rays->right && diff[0] > 0) || (mlx->rays->right && diff[0] < 0))
		diff[0] *= -1;
	ret = malloc(sizeof(float) * 4);
	ret[0] = inter_cor[0];
	ret[1] = inter_cor[1];
	ret[2] = diff[0];
	ret[3] = diff[1];
	return (ret);
}

//ft_v_hit_calculator();
//will return (hit_x, hit_y)
float	*ft_vertical_detector(t_mlx *mlx)
{
	float	next_inter_coor[2];
	float	*hit_coor;
	float	*coor_n_diff;

	coor_n_diff = ft_v_hit_calculator(mlx);
	hit_coor = malloc(sizeof(float) * 2);
	next_inter_coor[0] = coor_n_diff[0];
	next_inter_coor[1] = coor_n_diff[1];
	if (!mlx->rays->right)
		next_inter_coor[0]--;
	while (next_inter_coor[0] >= 0 && next_inter_coor[0] <= mlx->win_x
		&& next_inter_coor[1] >= 0 && next_inter_coor[1] <= mlx->win_y)
	{
		if (ft_wall_detector(next_inter_coor[0], next_inter_coor[1], mlx->map))
		{
			hit_coor[0] = next_inter_coor[0];
			hit_coor[1] = next_inter_coor[1];
			break ;
		}
		next_inter_coor[0] += coor_n_diff[2];
		next_inter_coor[1] += coor_n_diff[3];
	}
	free (coor_n_diff);
	return (hit_coor);
}

//ft_h_hit_calculator();
//will return (hit_x, hit_y)
float	*ft_horizontal_detector(t_mlx *mlx)
{
	float	next_inter_coor[2];
	float	*hit_coor;
	float	*coor_n_diff;

	coor_n_diff = ft_h_hit_calculator(mlx);
	hit_coor = malloc(sizeof(float) * 2);
	next_inter_coor[0] = coor_n_diff[0];
	next_inter_coor[1] = coor_n_diff[1];
	if (mlx->rays->up)
		next_inter_coor[1]--;
	while (next_inter_coor[0] >= 0 && next_inter_coor[0] <= mlx->win_x
		&& next_inter_coor[1] >= 0 && next_inter_coor[1] <= mlx->win_y)
	{
		if (ft_wall_detector(next_inter_coor[0], next_inter_coor[1], mlx->map))
		{
			hit_coor[0] = next_inter_coor[0];
			hit_coor[1] = next_inter_coor[1];
			break ;
		}
		next_inter_coor[0] += coor_n_diff[2];
		next_inter_coor[1] += coor_n_diff[3];
	}
	free (coor_n_diff);
	return (hit_coor);
}

float	ft_hit_distance(float *coor, t_mlx *mlx)
{
	return (sqrt((coor[0] - mlx->player->x) * (coor[0] - mlx->player->x)
			+ (coor[1] - mlx->player->y) * (coor[1] - mlx->player->y)));
}

//ft_horizontal_detector()-->detect the H_hit;
//ft_vertical_detector()-->detect the V_hit;
//will find the closest hit;
//will return the closest (rays(h_x, h_y, h_distance))
void	ft_hit_detector(t_mlx *mlx)
{
	float	*v_hit;
	float	*h_hit;

	h_hit = ft_horizontal_detector(mlx);
	v_hit = ft_vertical_detector(mlx);
	if (ft_hit_distance(h_hit, mlx) < ft_hit_distance(v_hit, mlx))
	{
		mlx->rays->hit_x = h_hit[0];
		mlx->rays->hit_y = h_hit[1];
	}
	else
	{
		mlx->rays->hit_x = v_hit[0];
		mlx->rays->hit_y = v_hit[1];
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
	while (i < 1)//mlx->rays->rays_num)
	{
		ft_ray_igniter(mlx, mlx->rays->ray_angle);
		ft_hit_detector(mlx);
		mlx->rays->ray_angle += mlx->player->fov / mlx->rays->rays_num;
		i++;
	}
}

// void	ft_ray_caster(t_mlx *mlx, float ray_angle)
// {
// 	//ft_hit_detector();
// 	float	inter_cor[2];
// 	float	diff[2];
// 	float	next_cor[2];
// 	float	test[4];
//
// 	// Intersection coordinates
// 	inter_cor[1] = floor(mlx->player->y / CUB_SIZE) * CUB_SIZE;
// 	if (!mlx->rays->up)
// 		inter_cor[1] += CUB_SIZE;
// 	inter_cor[0] = (inter_cor[1] - mlx->player->y) / tan(mlx->rays->ray_angle) + mlx->player->x; // Check if -iy or -player->x
//
// 	//  Delta x & Delta y
// 	diff[1] = CUB_SIZE + SPACE;
// 	if (mlx->rays->up)
// 		diff[1] *= -1;
// 	diff[0] = CUB_SIZE / tan(mlx->rays->ray_angle) + SPACE;
// 	if ((!mlx->rays->right && diff[0] > 0) || (mlx->rays->right && diff[0] < 0))// reverify
// 		diff[0] *= -1;
//
// 	next_cor[0] = inter_cor[0];
// 	next_cor[1] = inter_cor[1];
// 	if (mlx->rays->up)
// 		next_cor[1]--;
//
// 	while (next_cor[0] >= 0 && next_cor[0] <= mlx->win_x && next_cor[1] >= 0 && next_cor[1] <= mlx->win_y)
// 	{
// 		if (ft_wall_detector(next_cor[0], next_cor[1], mlx->map))
// 		{
// 			test[0] = mlx->player->x + cos(ray_angle);
// 			test[1] = mlx->player->y + sin(ray_angle);
// 			test[2] = next_cor[0];
// 			test[3] = next_cor[1];
// 			ft_draw_line(mlx, test, 0xFF0000);
// 			break ;
// 		}
// 		next_cor[0] += diff[0];
// 		next_cor[1] += diff[1];
// 	}
// }
//

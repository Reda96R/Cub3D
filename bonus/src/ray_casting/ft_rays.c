/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <rerayyad@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:43:20 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/17 06:18:42 by rerayyad         ###   ########.fr       */
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

void	ft_change_door_state(t_mlx *mlx, int *d, int x, int y)
{
	int	p_x;
	int	p_y;

	if (mlx->rays->colision_distance < 100)
	{
		x = floor(mlx->rays->hit_y / mlx->cub_size);
		y = floor(mlx->rays->hit_x / mlx->cub_size);
		p_y = floor(mlx->player->x / mlx->cub_size);
		p_x = floor(mlx->player->y / mlx->cub_size);
		if (p_x != x || p_y != y)
		{
			*d = 1;
			if (mlx->new_map[x][y] == 'H')
			{
				mlx->player->space = 0;
				mlx->new_map[x][y] = 'O';
			}
			else if (mlx->new_map[x][y] == 'O')
			{
				mlx->player->space = 0;
				mlx->new_map[x][y] = 'H';
			}
		}
	}
}

void	ft_hit_assigner(t_rays *ray, t_rays *hit)
{
	ray->s = hit->s;
	ray->type = hit->type;
	ray->hit_x = hit->hit_x;
	ray->hit_y = hit->hit_y;
	ray->heading = hit->heading;
	ray->colision_distance = hit->colision_distance;
	ray->door_state = 1;
}

void	ft_hit_detector(t_mlx *mlx)
{
	t_rays	*h;
	t_rays	*v;

	h = malloc(sizeof (t_rays));
	if (!h)
		ft_error_buster(1, mlx);
	v = malloc(sizeof (t_rays));
	if (!v)
	{
		free (h);
		ft_error_buster(1, mlx);
	}
	mlx->rays->up = mlx->rays->ray_angle > 0 && mlx->rays->ray_angle > M_PI;
	mlx->rays->right = mlx->rays->ray_angle <= M_PI_2
		|| mlx->rays->ray_angle >= (3 * M_PI_2);
	ft_horizontal_detector(mlx, h);
	ft_vertical_detector(mlx, v);
	if (h->colision_distance < v->colision_distance)
		ft_hit_assigner(mlx->rays, h);
	else
		ft_hit_assigner(mlx->rays, v);
	free (h);
	free (v);
}

void	ft_3d_caster(t_mlx *mlx, int i)
{
	float	wall_distance;
	float	project;
	t_pos	width_n_height;
	t_pos	coordinates;

	wall_distance = mlx->rays->colision_distance
		* cos (mlx->rays->ray_angle - mlx->player->rot);
	project = (mlx->win_x / 2) / tan(mlx->player->fov / 2);
	width_n_height.y = ((mlx->cub_size + SPACE) / wall_distance) * project;
	width_n_height.x = 1;
	ft_render_skyfloor(mlx, i, width_n_height, 0);
	coordinates.x = i;
	coordinates.y = (mlx->win_y / 2) - (width_n_height.y / 2);
	mlx->texture = ft_texture_selector(mlx);
	ft_draw_textured_wall(mlx, &coordinates, width_n_height);
	ft_render_skyfloor(mlx, i, width_n_height, 1);
}

void	ft_prime_and_cast(t_mlx *mlx)
{
	int		i;
	int		d;
	int		map_x;
	int		map_y;

	i = 0;
	d = 0;
	mlx->rays->ray_angle = mlx->player->rot - (mlx->player->fov / 2);
	while (i < mlx->rays->rays_num)
	{
		mlx->rays->ray_angle = fmod(mlx->rays->ray_angle, (2 * M_PI));
		if (mlx->rays->ray_angle < 0)
			mlx->rays->ray_angle += (2 * M_PI);
		ft_hit_detector(mlx);
		map_x = floor(mlx->rays->hit_y / mlx->cub_size);
		map_y = floor(mlx->rays->hit_x / mlx->cub_size);
		if (mlx->player->space && (mlx->new_map[map_x][map_y] == 'H'
			|| mlx->new_map[map_x][map_y] == 'O') && !d)
			ft_change_door_state(mlx, &d, map_x, map_y);
		ft_3d_caster(mlx, i);
		mlx->rays->ray_angle += mlx->player->fov / mlx->rays->rays_num;
		i++;
	}
}

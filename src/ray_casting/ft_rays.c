/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:43:20 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/09 19:34:25 by maouzal          ###   ########.fr       */
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

void	ft_hit_assigner(t_rays *ray, t_rays *hit)
{
	ray->s = hit->s;
	ray->hit_x = hit->hit_x;
	ray->hit_y = hit->hit_y;
	ray->heading = hit->heading;
	ray->colision_distance = hit->colision_distance;
}

void	ft_hit_detector(t_mlx *mlx)
{
	t_rays	*h;
	t_rays	*v;

	h = malloc(sizeof (t_rays));
	if (!h)
		ft_error_buster(1);
	v = malloc(sizeof (t_rays));
	if (!v)
	{
		free (h);
		ft_error_buster(1);
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

void	ft_render_skyfloor(t_mlx *mlx, int i, t_pos width_n_height, int n)
{
	t_pos	coordinates;
	int		color;
	char	c;

	c = mlx->rays->heading;
	if (!n)
	{
		coordinates.x = i;
		coordinates.y = 0;
		width_n_height.y = (mlx->win_y / 2) - (width_n_height.y / 2);
		color = mlx->c_color_int;
		mlx->rays->heading = 'C';
	}
	else
	{
		coordinates.x = i;
		coordinates.y = (mlx->win_y / 2) - (width_n_height.y / 2)
			+ width_n_height.y;
		width_n_height.y = (mlx->win_y - (coordinates.y));
		color = mlx->f_color_int;
		mlx->rays->heading = 'F';
	}
	ft_draw_rectangle(mlx, &coordinates, width_n_height, color);
	mlx->rays->heading = c;
}

void	ft_3d_caster(t_mlx *mlx, int i)
{
	float	wall_distance;
	float	project;
	t_pos	width_n_height;
	t_pos	coordinates;
	int		color;

	color = 0;
	if (mlx->rays->heading == 'S')
		color = 0xFF0000;
	else if (mlx->rays->heading == 'N')
		color = 0x00FF00;
	else if (mlx->rays->heading == 'W')
		color = 0x0000FF;
	else if (mlx->rays->heading == 'E')
		color = 0xFFFFFF;
	wall_distance = mlx->rays->colision_distance
		* cos (mlx->rays->ray_angle - mlx->player->rot);
	project = (mlx->win_x / 2) / tan(mlx->player->fov / 2);
	width_n_height.y = ((mlx->cub_size + SPACE) / wall_distance) * project;//wall height
	width_n_height.x = 1;//wall width
	ft_render_skyfloor(mlx, i, width_n_height, 0);
	coordinates.x = i;
	coordinates.y = (mlx->win_y / 2) - (width_n_height.y / 2);
	//ft_txtures(mlx->rays);
	ft_draw_rectangle(mlx, &coordinates, width_n_height, color);
	ft_render_skyfloor(mlx, i, width_n_height, 1);
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

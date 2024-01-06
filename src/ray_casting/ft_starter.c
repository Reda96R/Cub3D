/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_starter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:53:15 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/05 07:06:30 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_mlx	*ft_data_init(void)
{
	t_mlx	*mlx;

	mlx = malloc (sizeof (t_mlx));
	if (!mlx)
		ft_error_buster(1);
	mlx->win_x = 1337;//(CUB_SIZE + SPACE) * MAP_X;
	mlx->win_y = 800;//(CUB_SIZE + SPACE) * MAP_Y;
	mlx->cub_size = mlx->win_y / MAP_Y; //64;
	ft_player_init(&mlx->player, mlx->win_x / 5, mlx->win_y / 2);
	ft_rays_init(&mlx->rays, mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		ft_error_buster(2);
	mlx->win_ptr = \
			mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y, "cub3D");
	if (!mlx->win_ptr)
		ft_error_buster(2);
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.id = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.len, \
	&mlx->img.endian);
	return (mlx);
}

void	ft_rays_init(t_rays **rays, t_mlx *mlx)
{
	*rays = malloc (sizeof (t_rays));
	if (!rays)
		ft_error_buster(1);
	(*rays)->rays_num = mlx->win_x;
	(*rays)->ray_size = (mlx->player->r * RAY_SIZE);
	(*rays)->hit_x = 0;
	(*rays)->hit_y = 0;
	(*rays)->colision_distance = 0;
}

void	ft_player_init(t_player **player, int x, int y)
{
	(void) x;
	(void) y;
	*player = malloc (sizeof (t_player));
	if (!player)
		ft_error_buster(1);
	// (*player)->x = x;
	// (*player)->y = y;
	(*player)->fov = FOV * (M_PI / 180);
	(*player)->r = RADIUS * MINIMAP_SCALE;
	(*player)->spd = SPEED;
	(*player)->walk = 0;
	(*player)->turn = 0;
	(*player)->rot = -M_PI_2;
	(*player)->rot_spd = ROT_SPEED * (M_PI / 180);
}

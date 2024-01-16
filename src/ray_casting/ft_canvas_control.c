/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_canvas_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 10:30:17 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/16 00:09:18 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_canvas_maker(t_mlx *mlx)
{
	ft_prime_and_cast(mlx);
	ft_draw_map(mlx);// will be removed in mandatory
	mlx->player->r = (mlx->cub_size * MINIMAP_SCALE) / 5;
	mlx->player->spd = SPEED * (mlx->cub_size / 35); 
	mlx->player->rot_spd = (ROT_SPEED * (M_PI / 180)) * (mlx->cub_size / 40);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);// will be removed in mandatory
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	mlx_do_sync(mlx->mlx_ptr);
	mlx_hook(mlx->win_ptr, 17, (1L << 17), ft_cross, mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, ft_key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, ft_key_release, mlx);
	mlx_loop_hook(mlx->mlx_ptr, ft_update, mlx);
	mlx_loop(mlx->mlx_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img);
}

int	ft_update(t_mlx *mlx)
{
	ft_scene_cleaner(mlx);
	ft_pos_calculator(mlx);
	ft_prime_and_cast(mlx);
	ft_draw_map(mlx);// will be removed in mandatory
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);// will be removed in mandatory
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_starter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:53:15 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/21 17:53:16 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_mlx	*ft_data_init(void)
{
	t_mlx	*mlx;

	mlx = malloc (sizeof (t_mlx));
	// if (!mlx)
	// 	ft_janitor();
	mlx->win_x = (CUB_SIZE + SPACE) * MAP_X;
	mlx->win_y = (CUB_SIZE + SPACE) * MAP_Y;
	ft_player_init(&mlx->player, mlx->win_x / 2, mlx->win_y / 2);
	mlx->mlx_ptr = mlx_init();
	// if (!mlx->mlx_ptr)
	// 	ft_janitor();
	mlx->win_ptr = \
			mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y, "cub3D");
	// if (!mlx->win_ptr)
	// 	ft_janitor();
	mlx->img.img = mlx_new_image(mlx->mlx_ptr, mlx->win_x, mlx->win_y);
	mlx->img.id = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.len, \
	&mlx->img.endian);
	return (mlx);
}

void	ft_player_init(t_player **player, int x, int y)
{
	*player = malloc (sizeof (t_player));
	// if (!player)
	// 	ft_janitor();
	(*player)->x = x;
	(*player)->y = y;
	(*player)->r = RADIUS;
	(*player)->spd = SPEED;
	(*player)->walk = 0;
	(*player)->turn = 0;
	(*player)->rot = -M_PI_2;
	(*player)->rot_spd = ROT_SPEED * (M_PI / 180);
}

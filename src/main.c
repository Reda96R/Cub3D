/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:26:16 by rerayyad          #+#    #+#             */
/*   Updated: 2023/12/16 15:26:19 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	g_test[][9] = {
{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '0', '0', '1', '0', '0', '1'},
{'1', '1', '1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

void	ft_canvas_maker(t_mlx *mlx)
{
	memcpy(mlx->map, g_test, sizeof (g_test)); // Will be removed
	ft_draw_map(mlx);// will be removed in mandatory
	ft_prime_and_cast(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);// will be removed in mandatory
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, ft_key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, ft_key_release, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update, mlx);
	mlx_loop(mlx->mlx_ptr);
}

int	main(void)
{
	t_mlx	*mlx;

	mlx = ft_data_init();
	ft_canvas_maker(mlx);
	return (0);
}

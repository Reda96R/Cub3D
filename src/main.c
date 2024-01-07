/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:rerayyad <rerayyad@student.42.fr>            +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:26:16 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/07 16:32:49 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	g_test[][10] = {
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
{'1', '1', '1', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

char	g_test0[][4] = {
{'1', '1', '1', '1'},
{'1', '0', '0', '1'},
{'1', '0', '0', '1'},
{'1', '1', '1', '1'},
};

char	g_test1[][3] = {
{'1', '1', '1'},
{'1', '0', '1'},
{'1', '1', '1'},
};

void	ft_canvas_maker(t_mlx *mlx)
{
	// memcpy(mlx->map, mlx->map, (mlx->map)); // Will be removed
	ft_draw_map(mlx);// will be removed in mandatory
	ft_prime_and_cast(mlx);
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);// will be removed in mandatory
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img, 0, 0);
	mlx_hook(mlx->win_ptr, 17, (1L << 17), ft_cross, mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, ft_key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, ft_key_release, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update, mlx);
	mlx_loop(mlx->mlx_ptr);
}

void	arg_check(int ac, char **av)
{
	int	i;

	i = ft_strlen(av[1]) - 3;
	if (ac != 2)
	{
		printf("Error\nWrong number of arguments");
		exit(1);
	}
	if (av[1][i] != 'c' || av[1][i + 1] != 'u'
		|| av[1][i + 2] != 'b' || av[1][i + 3] != '\0')
	{
		printf("Error\nWrong file format");
		exit(1);
	}
	if (ft_strlen(av[1]) < 4)
	{
		printf("Error\nWrong file format");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;

	arg_check(ac, av);
	mlx = ft_data_init(av);
	ft_canvas_maker(mlx);
	return (0);
}

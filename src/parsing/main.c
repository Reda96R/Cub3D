/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 03:07:52 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/05 03:42:28 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	arg_check(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nWrong number of arguments");
		exit(1);
	}
	if (ft_strlen(av[1]) < 4 || ft_strnstr(av[1], ".cub", ft_strlen(av[1])) == NULL)
	{
		printf("Error\nWrong file format");
		exit(1);
	}
}

void	enitialize(t_mlx *mlx)
{
	mlx->east_texture = NULL;
	mlx->west_texture = NULL;
	mlx->south_texture = NULL;
	mlx->north_texture = NULL;
	mlx->c_color = NULL;
	mlx->f_color = NULL;
	mlx->map = NULL;
	mlx->full_file = NULL;
}

int main(int ac, char **av)
{
	t_mlx mlx;

	arg_check(ac, av);
	enitialize(&mlx);
	get_file(&mlx, av[1]);
	is_deplecate(&mlx);
	get_texters(&mlx);
	textres_existence(&mlx, "Missing texture");
	colors_existence(&mlx);
	check_colors_format(mlx.c_color, &mlx);
	check_colors_format(mlx.f_color, &mlx);
	check_map_format(&mlx);
	cheack_map_borders(&mlx);
	check_map_is_locked(&mlx);
	ft_free_all(&mlx);
	
	
	return (0);
}

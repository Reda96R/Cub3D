/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 03:08:13 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/11 07:05:46 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_all(t_mlx *mlx)
{
	if (mlx->east_texture)
		free(mlx->east_texture);
	if (mlx->west_texture)
		free(mlx->west_texture);
	if (mlx->south_texture)
		free(mlx->south_texture);
	if (mlx->north_texture)
		free(mlx->north_texture);
	if (mlx->c_color)
		free(mlx->c_color);
	if (mlx->f_color)
		free(mlx->f_color);
	if (mlx->full_file)
		ft_free(mlx->full_file);
	if (mlx->map)
		ft_free(mlx->map);
}

void	ft_Error(char *str, t_mlx *mlx)
{
	printf("Error\n%s", str);
	ft_free_all(mlx);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:34:30 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/07 16:34:37 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_map_parser(t_mlx *mlx)
{
	map_height_width(mlx);
	mlx->cub_size = fmin(mlx->win_y / mlx->map_height,
			mlx->win_x / mlx->map_width);
	check_map_format(mlx);
	cheack_map_borders(mlx);
	check_map_is_locked(mlx);
	ft_free(mlx->full_file);
	copy_map(mlx);
}

void	map_height_width(t_mlx *mlx)
{
	int	i;
	int	j;
	int	k;
	int	max_width;

	i = 0;
	max_width = 0;
	mlx->map_height = 0;
	while (mlx->map[i])
	{
		j = 0;
		k = 0;
		if (mlx->map[i][j] != '\0' && mlx->map[i][j] != '\n')
			mlx->map_height++;
		while (mlx->map[i][j])
		{
			k++;
			if (k > max_width)
				max_width = k;
			j++;
		}
		i++;
	}
	mlx->map_width = max_width;
}

void	check_map_format(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	is_palyer_deplicate(mlx);
	while (mlx->map[i] && !mlx->map[i][j])
		i++;
	if (!mlx->map[i])
		ft_Error("Map is not valid", mlx);
	while (mlx->map[i] && mlx->map[i + 1])
	{
		j = 0;
		if (!mlx->map[i][j] && mlx->map[i + 1][j] && mlx->map[i + 1][j] != '\n')
			ft_Error("Map is not valid", mlx);
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] != '1' && mlx->map[i][j] != '0' && mlx->map[i][j] != 'N'
				&& mlx->map[i][j] != 'S' && mlx->map[i][j] != 'E' && mlx->map[i][j] != 'W'
				&& mlx->map[i][j] != ' ' && mlx->map[i][j] != 'D')//the check for 'D' will be removed in mandatory
				ft_Error("Map is not valid", mlx);
			j++;
		}
		i++;
	}
}

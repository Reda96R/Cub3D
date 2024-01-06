/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:18:53 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/06 02:27:28 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void    map_height_width(t_mlx *mlx)
{
	int i;
	int j;
	int k;
	int max_width;

	i = 0;
	max_width = 0;
	mlx->map_height = 0;
	while (mlx->map[i])
	{
		j = 0;
		k = 0;
		if(mlx->map[i][j] != '\0' && mlx->map[i][j] != '\n')
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

void	copy_map(t_mlx *mlx)
{
	int i;
	int x;
	int j;

	i = 0;
	x = 0;
	j = 0;
	map_height_width(mlx);
	mlx->new_map = malloc(sizeof(char *) * (mlx->map_height + 1));
	if (!mlx->new_map)
		ft_Error("Malloc failed", mlx);
	mlx->new_map[mlx->map_height] = NULL;
	while (mlx->map[i] && (mlx->map[i][0] == '\0' || mlx->map[i][0] == '\n'))
		i++;
	while (mlx->map[i])
	{
		if (mlx->map[i][0] == '\0' || mlx->map[i][0] == '\n')
			break;
		mlx->new_map[x] = malloc(sizeof(char) * (mlx->map_width + 1));
		if (!mlx->new_map[x])
			ft_Error("Malloc failed", mlx);
		j = 0;
		while (mlx->map[i][j])
		{
			mlx->new_map[x][j] = mlx->map[i][j];
			j++;
		}
		while (j < mlx->map_width && j != 0)
			mlx->new_map[x][j++] = ' ';
		mlx->new_map[x][j] = '\0';
		i++;
		x++;
	}
	mlx->new_map[x] = NULL;
}

//-----------> don't  forget the norminette!!!!
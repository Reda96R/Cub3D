/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:24:25 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/06 00:12:55 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


int	get_map_size(t_mlx *mlx)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (mlx->full_file[i])
	{
		if(!ft_strncmp(mlx->full_file[i], "NO", 2) || !ft_strncmp(mlx->full_file[i], "SO", 2) 
			|| !ft_strncmp(mlx->full_file[i], "WE", 2) || !ft_strncmp(mlx->full_file[i], "EA", 2)
			|| !ft_strncmp(mlx->full_file[i], "C ", 2) || !ft_strncmp(mlx->full_file[i], "F ", 2)
			|| (!mlx->full_file[i][0] && size == 0))
				i++;
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

void	is_palyer_deplicate(t_mlx *mlx)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (mlx->map[i])
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'S' || mlx->map[i][j] == 'E'
				|| mlx->map[i][j] == 'W')
			{
				mlx->player->x = i;
				mlx->player->y = j;
				mlx->map[i][j] = '0';
				k++;
			}
			j++;
		}
		i++;
	}
	if (k != 1)
		ft_Error("Wrong player format", mlx);
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
				&& mlx->map[i][j] != ' ')
				ft_Error("Map is not valid", mlx);
			j++;
		}
		i++;
	}
}

void	cheack_map_borders(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mlx->map[i])
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (i == 0 || j == 0 || !mlx->map[i + 1] || !mlx->map[i][j + 1])
			{
				if (mlx->map[i][j] != '1' && mlx->map[i][j] != ' ' && mlx->map[i][j] != '\n')
					ft_Error("Map is not valid", mlx);
			}
			j++;
		}
		i++;
	}
}

void	check_map_is_locked(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 1;
	while (mlx->map[i] && mlx->map[i + 1])
	{
		j = 0;
		while (mlx->map[i][j] && mlx->map[i + 1][j])
		{
			if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'S' || mlx->map[i][j] == 'E'
				|| mlx->map[i][j] == 'W' || mlx->map[i][j] == '0')
			{
				if (mlx->map[i][j + 1] == ' ' || mlx->map[i][j - 1] == ' ' 
					|| mlx->map[i + 1][j] == ' ' || mlx->map[i - 1][j] == ' ')
					ft_Error("Map is not valid", mlx);
			}
			j++;
		}
		i++;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texter_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 03:08:06 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/15 18:09:29 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	fill_texter(t_mlx *mlx, char *str)
{
	while (*str == ' ')
		str++;
	if (ft_strnstr(str, "NO ", 3))
		mlx->north_texture = ft_substr(str, get_start(mlx, str, 1), \
		get_end(mlx, str, get_start(mlx, str, 1)));
	else if (ft_strnstr(str, "SO ", 3))
		mlx->south_texture = ft_substr(str, get_start(mlx, str, 1), \
		get_end(mlx, str, get_start(mlx, str, 1)));
	else if (ft_strnstr(str, "WE ", 3))
		mlx->west_texture = ft_substr(str, get_start(mlx, str, 1), \
		get_end(mlx, str, get_start(mlx, str, 1)));
	else if (ft_strnstr(str, "EA ", 3))
		mlx->east_texture = ft_substr(str, get_start(mlx, str, 1), \
		get_end(mlx, str, get_start(mlx, str, 1)));
	else if (ft_strnstr(str, "C ", 2))
		mlx->c_color = ft_substr(str, get_start(mlx, str, 2), \
		ft_strlen(str) - get_start(mlx, str, 2) - 1);
	else if (ft_strnstr(str, "F ", 2))
		mlx->f_color = ft_substr(str, get_start(mlx, str, 2), \
		ft_strlen(str) - get_start(mlx, str, 2) - 1);
	else
		return (1);
	if (mlx->flag == 1)
		check_map_order(mlx);
	return (0);
}

void	fill_texter_map(int i, int j, int size, t_mlx *mlx)
{
	while (mlx->full_file[i])
	{
		if (fill_texter(mlx, mlx->full_file[i]) == 1)
		{
			if (mlx->full_file[i][0] != '\0' && mlx->full_file[i][0] != '\n')
				if (!mlx->east_texture || !mlx->west_texture
					|| !mlx->south_texture || !mlx->north_texture)
					ft_error_buster(6, mlx);
			if (!mlx->full_file[i + 1])
				mlx->map[j++] = ft_substr(mlx->full_file[i], 0, \
				ft_strlen(mlx->full_file[i]));
			else
			{
				mlx->map[j++] = ft_substr(mlx->full_file[i], 0, \
				ft_strlen(mlx->full_file[i]) - 1);
				mlx->flag = 1;
			}
		}
		i++;
	}
	if (j <= size)
		mlx->map[j] = NULL;
}

void	get_texters(t_mlx *mlx)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = get_map_size(mlx);
	if (size <= 2)
		ft_error_buster(10, mlx);
	mlx->map = ft_calloc(sizeof(char *), (size + 1));
	if (!mlx->map)
		ft_error_buster(1, mlx);
	mlx->map[size] = NULL;
	fill_texter_map(i, j, size, mlx);
}

void	check_map_order(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	if (!mlx->map)
		return ;
	while(mlx->map[i])
	{
		j = 0;
		while (mlx->map[i][j])
		{
			if (mlx->map[i][j] != '\n' && mlx->map[i][j] != '\0' && mlx->map[i][j] != ' ')
				ft_error_buster(10, mlx);
			j++;
		}
		i++;
	}
}

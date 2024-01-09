/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:18:53 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/09 19:25:01 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_start(t_mlx *mlx, char *line, int type) //1 for texter 2 for color
{
	int	i;

	i = 0;
	if (type == 1)
	{
		line += 3;
		while (line[i] && line[i] == ' ')
			i++;
		i += 3;
	}
	else if (type == 2)
	{
		line += 2;
		while (line[i] && !ft_isdigit(line[i]))
			i++;
		i += 2;
	}
	if (line[i] == '\0')
	{
		if (type == 1)
			ft_Error("Wrong texture format", mlx);
		else if (type == 2)
			ft_Error("Wrong color format", mlx);
	}
	return (i);
}

void	copy_map(t_mlx *mlx)
{
	int	i;
	int	x;
	int	j;

	i = 0;
	x = 0;
	j = 0;
	mlx->new_map = malloc(sizeof(char *) * (mlx->map_height + 1));
	if (!mlx->new_map)
		ft_Error("Malloc failed", mlx);
	mlx->new_map[mlx->map_height] = NULL;
	while (mlx->map[i] && (mlx->map[i][0] == '\0' || mlx->map[i][0] == '\n'))
		i++;
	while (mlx->map[i])
	{
		if (mlx->map[i][0] == '\0' || mlx->map[i][0] == '\n')
			break ;
		mlx->new_map[x] = malloc(sizeof(char) * (mlx->map_width));
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
		mlx->new_map[x][j - 1] = '\0';
		i++;
		x++;
	}
	mlx->new_map[x] = NULL;
	i = 0;
	while(mlx->new_map[i])
	{
		printf("%s\n", mlx->new_map[i]);
		i++;
	}
}

//-----------> don't  forget the norminette!!!!

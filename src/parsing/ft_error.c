/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 03:08:13 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/14 17:11:37 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_error(char *str, t_mlx *mlx)
{
	printf("Error\n%s", str);
	ft_free_all(mlx);
	exit(1);
}

int	skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	skip_vide_line(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (mlx->map[i])
	{
		j = 0;
		while (mlx->map[i] && !mlx->map[i][j])
			i++;
		if (mlx->map[i][j] && mlx->map[i][j] == ' ')
			j = skip_spaces(mlx->map[i]);
		if (mlx->map[i][j] != '\0' && mlx->map[i][j] != '\n'
			&& mlx->map[i][j] != ' ')
			break ;
		i++;
	}
	return (i);
}

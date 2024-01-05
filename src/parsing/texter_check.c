/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texter_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 03:08:06 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/05 03:50:21 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int    fill_texter(t_mlx *mlx, int i)
{
    if(ft_strnstr(mlx->full_file[i], "NO ", 3))
		mlx->north_texture = ft_substr(mlx->full_file[i], 4, ft_strlen(mlx->full_file[i]) - 4);
	else if(ft_strnstr(mlx->full_file[i], "SO ", 3))
		mlx->south_texture = ft_substr(mlx->full_file[i], 4, ft_strlen(mlx->full_file[i]) - 4);
	else if(ft_strnstr(mlx->full_file[i], "WE ", 3))
		mlx->west_texture = ft_substr(mlx->full_file[i], 4, ft_strlen(mlx->full_file[i]) - 4);
	else if(ft_strnstr(mlx->full_file[i], "EA ", 3))
		mlx->east_texture = ft_substr(mlx->full_file[i], 4, ft_strlen(mlx->full_file[i]) - 4);
	else if(ft_strnstr(mlx->full_file[i], "C ", 2))
		mlx->c_color = ft_substr(mlx->full_file[i], 2, ft_strlen(mlx->full_file[i]) - 3);
	else if(ft_strnstr(mlx->full_file[i], "F ", 2))
		mlx->f_color = ft_substr(mlx->full_file[i], 2, ft_strlen(mlx->full_file[i]) - 3);
    else
        return (1);
    return (0);
}

void    fill_texter_map(int i, int j,int size , t_mlx *mlx)
{
    while (mlx->full_file[i])
	{
		if(fill_texter(mlx, i) == 1)
		{
			if ( mlx->full_file[i][0] != '\0' && mlx->full_file[i][0] != '\n')
				textres_existence(mlx, "Wrong file format");
			if (!mlx->full_file[i + 1])
				mlx->map[j++] = ft_substr(mlx->full_file[i], 0, ft_strlen(mlx->full_file[i]));
			else
				mlx->map[j++] = ft_substr(mlx->full_file[i], 0, ft_strlen(mlx->full_file[i]) - 1);
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
	{
		printf("Error\nEmpty map");
		exit(1);
	}
	mlx->map = malloc(sizeof(char *) * (size + 1));
	if (!mlx->map)
	{
		printf("Error\nMalloc failed");
		exit(0);
	}
    fill_texter_map(i, j,size , mlx);
}

void	textres_existence(t_mlx *mlx, char *str)
{
	if(!mlx->east_texture || !mlx->west_texture || !mlx->south_texture || !mlx->north_texture)
	{
		printf("Error\n%s", str);
		if (mlx->east_texture)
			free(mlx->east_texture);
		if (mlx->west_texture)
			free(mlx->west_texture);
		if (mlx->south_texture)
			free(mlx->south_texture);
		if (mlx->north_texture)
			free(mlx->north_texture);
		ft_free(mlx->full_file);
		exit(1);
	}
}

void	texters_format(t_mlx *mlx, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			printf("Error\nWrong texter format");
			ft_free(mlx->full_file);
			exit(1);
		}
		i++;
	}
}

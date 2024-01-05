/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 03:07:22 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/05 03:49:29 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	is_deplecate(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(mlx->full_file[i])
	{
		if (!strncmp(mlx->full_file[i], "NO", 2) || !strncmp(mlx->full_file[i], "SO", 2) 
			|| !strncmp(mlx->full_file[i], "WE", 2) || !strncmp(mlx->full_file[i], "EA", 2) 
			|| !strncmp(mlx->full_file[i], "C ", 2) || !strncmp(mlx->full_file[i], "F ", 2))
		{
			j = i + 1;
			while(mlx->full_file[j])
			{
				if (!strncmp(mlx->full_file[i], mlx->full_file[j], 2))
				{
					printf("Error\nDuplicate texter or color");
					ft_free(mlx->full_file);
					exit(1);
				}
				j++;
			}
		}
		i++;
	}
}

void	get_file_size(t_mlx *mlx, char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFile not found");
		exit(1);
	}
	line = m_get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = m_get_next_line(fd);
	}
	free(line);
	close(fd);
	if (i == 0)
	{
		printf("Error\nEmpty file");
		exit(1);
	}
	mlx->full_file = malloc(sizeof(char *) * (i + 1));
	mlx->full_file[i] = NULL;
}


void    get_file(t_mlx *mlx, char *file)
{
	int     fd;
	char    *line;
	int     i;
	int     j;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFile not found");
		exit(1);
	}
	m_get_file_size(mlx, file);
	line = m_get_next_line(fd);
	while (line)
	{
		mlx->full_file[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		j = 0;
		while (line[j])
		{
			mlx->full_file[i][j] = line[j];
			j++;
		}
		mlx->full_file[i][j] = '\0';
		free(line);
		line = m_get_next_line(fd);
		i++;
	}
	close(fd);
}

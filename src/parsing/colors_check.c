/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 03:07:45 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/06 03:24:53 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	colors_existence(t_mlx *mlx)
{
	if (!mlx->c_color || !mlx->f_color)
	{
		printf("Error\nMissing color!! ");
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
		ft_free(mlx->full_file);
		exit(1);
	}
}

void	check_colors_format(char	*str, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != ',' && str[i] != '0'
			&& str[i] != '1' && str[i] != '2' && str[i] != '3'
			&& str[i] != '4' && str[i] != '5' && str[i] != '6'
			&& str[i] != '7' && str[i] != '8' && str[i] != '9')
			ft_Error("Wrong color format", mlx);
		if (str[i] == ',')
		{
			j++;
			if (str[i + 1] == ',' || str[i + 1] == ' ')
				ft_Error("Wrong color format", mlx);
		}
		i++;
	}
	if (j != 2)
		ft_Error("Wrong color format", mlx);
	check_colors_range(str, mlx);
}

void	colors_range(t_mlx *mlx, char *tmp, int i)
{
	int	a;

	if (ft_strlen(tmp) > 3)
		ft_Error("Wrong color format", mlx);
	a = ft_atoi(tmp);
	if (a < 0 || a > 255)
		ft_Error("Wrong color range", mlx);
	if (i == 0)
		mlx->c_color_int += a * 256 * 256;
	if (i == 1)
		mlx->c_color_int += a * 256;
	if (i == 2)
		mlx->c_color_int += a;
	free(tmp);
}

void	check_colors_range(char	*str, t_mlx *mlx)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] != ',')
		i++;
	tmp = ft_substr(str, 0, i);
	colors_range(mlx, tmp, 0);
	i++;
	j = i;
	while (str[i] != ',')
		i++;
	tmp = ft_substr(str, j, i - j);
	colors_range(mlx, tmp, 1);
	i++;
	j = i;
	while (str[i] != '\0')
		i++;
	tmp = ft_substr(str, j, i - j);
	colors_range(mlx, tmp, 2);
}

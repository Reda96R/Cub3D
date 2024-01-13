/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_janitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:57:02 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/04 09:57:09 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_error_buster(int id)
{
	if (id == 1)
		ft_putstr_fd("\033[0;31mError: unable to allocate memory\n", 2);
	else if (id == 2)
		ft_putstr_fd("\033[0;31mError: MiniLibX initialization failed\n", 2);
	else if (id == 3)
	{
		ft_putstr_fd("\033[0;31mError: Wrong number of arguments\n", 2);
		ft_putstr_fd("\033[0;32m\tUsage: ./cub3D <mapname>.cub\n", 2);
	}
	else if (id == 4)
	{
		ft_putstr_fd("\033[0;31mError: Wrong file format\n", 2);
		ft_putstr_fd("\033[0;32m\tUsage: ./cub3D <mapname>.cub\n", 2);
	}
	else if (id == 5)
	{
		ft_putstr_fd("\033[0;31mError: Wrong file format\n", 2);
		ft_putstr_fd("\033[0;32m\tUsage: ./cub3D <mapname>.cub\n", 2);
	}
	else if (id == 6)
		ft_putstr_fd("\033[0;31mError: Texture not found\n", 2);
	printf("\033[0m");
	exit (1);
}

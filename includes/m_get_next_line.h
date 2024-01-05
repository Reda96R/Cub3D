/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maouzal <maouzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:22:06 by maouzal           #+#    #+#             */
/*   Updated: 2024/01/05 01:40:20 by maouzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <string.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif


typedef struct s_mlx
{
	char			**full_file;
	char			**map;
	char            *north_texture;
	char            *south_texture;
	char            *west_texture;
	char            *east_texture;
	char			*c_color;
	char			*f_color;
	void			*Garbage;
	
}	t_mlx;

unsigned int	ft_strlen(const char *s);
char			*ft_strjoin(char *s1, char *s2);
int				ft_chr(char *s);
char			*ft_strdup(const char *s1);
char			*read_line(int fd, char *str);
char			*end_line(char *str);
char			*rest_val(char *str);
char			*get_next_line(int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char    *ft_substr(char const *s, unsigned int start, size_t len);
int		get_map_size(t_mlx *mlx);
void	get_file(t_mlx *mlx, char *file);
void	get_texters(t_mlx *mlx);
void	is_deplecate(t_mlx *mlx);
void	ft_free(char **str);
void	textres_existence(t_mlx *mlx, char *str);
void	colors_existence(t_mlx *mlx);
void	ft_Error(char *str, t_mlx *mlx);
void	check_map_format(t_mlx *mlx);
void	cheack_map_borders(t_mlx *mlx);
void	check_map_is_locked(t_mlx *mlx);
void	check_colors_format(char	*str, t_mlx *mlx);
void	check_colors_range(char	*str, t_mlx *mlx);
int		ft_atoi(const char *str);
void	ft_free_all(t_mlx *mlx);
void	enitialize(t_mlx *mlx);
void	is_palyer_deplicate(t_mlx *mlx);

#endif
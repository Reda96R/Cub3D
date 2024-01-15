/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerayyad <rerayyad@student.42.fr>            +#+  +:+       +#+	  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:54:28 by rerayyad          #+#    #+#             */
/*   Updated: 2024/01/07 16:58:40 by rerayyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include "m_get_next_line.h"
# include "structs.h"
# include "cub_macros.h"
# include "../../mlx_linux/mlx.h"
// # include <mlx.h>

typedef struct s_mlx
{
	int				map_height;
	int				map_width;
	float			win_x;
	float			win_y;
	float			cub_size;
	void			*mlx_ptr;
	void			*win_ptr;
	char			**full_file;
	char			**map;
	char			**new_map;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*c_color;
	char			*f_color;
	unsigned int	c_color_int;
	unsigned int	f_color_int;
	t_img			*n_wall;
	t_img			*s_wall;
	t_img			*w_wall;
	t_img			*e_wall;
	t_img			texture;
	t_img			img;
	t_player		*player;
	t_rays			*rays;
	t_pos			*pos;
}	t_mlx;

/*::::::::::::ft_janitor::::::::::::*/
void	ft_error_buster(int id, t_mlx *mlx);
void	ft_error_buster2(int id);
void	ft_free(char **str);
void	ft_free_all(t_mlx *mlx);

/*::::::::::::::::PRS:::::::::::::::*/

			/*---ft_error---*/
int		skip_spaces(char *line);
int		skip_vide_line(t_mlx *mlx);

			/*---file_check---*/
void	ft_file_parser(t_mlx *mlx, char *av);
void	get_file(t_mlx *mlx, char *file);
void	fill_file(t_mlx *mlx, char *line, int fd);
void	get_file_size(t_mlx *mlx, char *file);
void	is_deplecate(t_mlx *mlx);
int		skip_vide_line(t_mlx *mlx);

			/*---texter_check---*/
void	get_texters(t_mlx *mlx);
void	fill_texter_map(int i, int j, int size, t_mlx *mlx);

			/*---map_check0---*/
void	ft_map_parser(t_mlx *mlx);
void	map_height_width(t_mlx *mlx);
int		new_line_check(t_mlx *mlx, int i, int j);
void	check_map_format(t_mlx *mlx);

			/*---map_check1---*/
int		get_map_size(t_mlx *mlx);
void	is_palyer_deplicate(t_mlx *mlx);
void	ft_player_pos(t_mlx *mlx, int i, int j);
void	cheack_map_borders(t_mlx *mlx);
void	check_map_is_locked(t_mlx *mlx);

			/*---color_check---*/
void	colors_existence(t_mlx *mlx);
void	colors_range(t_mlx *mlx, char *tmp, int i, char c);
void	check_colors_format(char	*str, t_mlx *mlx, char c);
void	check_colors_range(char	*str, t_mlx *mlx, char c);
void	ft_color_assigner(t_mlx *mlx, char c, int a, int i);

			/*---new_map---*/
void	copy_map(t_mlx *mlx);
void	copy_to_new_map(t_mlx *mlx, int i, int x, int j);
int		get_start(t_mlx *mlx, char *line, int type);
int		get_end(t_mlx *mlx, char *line, int start);

/*:::::::::::::::::TXT:::::::::::::::*/

			/*---ft_texture---*/
t_img	*ft_file_to_image(t_mlx *mlx, char *path);
t_img	ft_texture_selector(t_mlx *mlx);
void	ft_render_skyfloor(t_mlx *mlx, int i, t_pos width_n_height, int n);
void	ft_draw_textured_wall(t_mlx *mlx, t_pos *coordinates,
			t_pos width_n_height);
void	pos_x_init(t_mlx *mlx, t_pos *pos);
/*::::::::::::::::RAY:::::::::::::::*/

			/*---ft_starter---*/
t_mlx	*ft_data_init(char *av[]);
void	ft_mlx_init(t_mlx **mlx);
void	ft_player_init(t_player **player, t_mlx *mlx);
void	ft_rays_init(t_rays **rays, t_mlx *mlx);
void	ft_textures_init(t_mlx *mlx);

			/*---ft_canvas_control---*/
void	ft_canvas_maker(t_mlx *mlx);
int		ft_update(t_mlx *mlx);

			/*---ft_rays---*/
void	ft_prime_and_cast(t_mlx *mlx);
void	ft_hit_detector(t_mlx *mlx);
void	ft_ray_igniter(t_mlx *mlx, int color);
void	ft_hit_assigner(t_rays *ray, t_rays *hit);
void	ft_3d_caster(t_mlx *mlx, int i);

			/*---ft_drawer---*/
void	ft_put_pixel(t_mlx *mlx, int x, int y, int color);
int		ft_my_mlx_pixel_get(t_mlx *mlx, int x, int y);
void	ft_scene_cleaner(t_mlx *mlx);
void	ft_draw_map(t_mlx *mlx);
void	ft_draw_player(t_mlx *mlx, int x, int y);
void	ft_clear_player(t_mlx *mlx, int x, int y, int size);
void	ft_clear_map(t_mlx *mlx);

			/*---ft_player_movements---*/
void	ft_pos_calculator(t_mlx *mlx);
void	ft_move_front(t_mlx *mlx);
void	ft_move_back(t_mlx *mlx);
void	ft_move_left(t_mlx *mlx);
void	ft_move_right(t_mlx *mlx);

			/*---ft_shapes---*/
void	ft_draw_line(t_mlx *mlx, float c[4], int color);
void	ft_draw_circle(t_mlx *mlx, int x, int y);
void	ft_draw_square(t_mlx *mlx, int x, int y, int color);
void	ft_draw_scaled_square(t_mlx *mlx, int x, int y, int color);
void	ft_draw_rectangle(t_mlx *mlx, t_pos *coordinates,
			t_pos width_n_height, int color);

			/*---ft_maths_hub0---*/
float	ft_hit_distance(float *coor, t_mlx *mlx);
int		ft_wall_colision(t_mlx *mlx);
int		ft_wall_detector(float x, float y, t_mlx *mlx);
void	ft_move_calculator(t_mlx *mlx);
void	ft_turn_calculator(t_mlx *mlx);

			/*---ft_maths_hub1---*/
int		ft_wall_inspection(t_mlx *mlx, t_rays *ray, float *coord, int n);
void	ft_h_hit_calculator(t_mlx *mlx, t_rays *h, char *heading, int *door);
void	ft_v_hit_calculator(t_mlx *mlx, t_rays *v, char *heading, int *door);
void	ft_vertical_detector(t_mlx *mlx, t_rays *v);
void	ft_horizontal_detector(t_mlx *mlx, t_rays *h);

			/*---ft_keylogger---*/
int		ft_cross(int key, t_mlx *mlx);
int		ft_key_press(int keycode, t_mlx *mlx);
int		ft_key_release(int keycode, t_mlx *mlx);

#endif

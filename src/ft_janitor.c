#include "../includes/cub3D.h"

void	ft_error_buster(int id)
{
	if (1)
		printf("\033[0;31mError: unable to allocate memory\n");
	printf("\033[0m");
}

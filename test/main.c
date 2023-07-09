#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../lib/MLX42/include/MLX42/MLX42.h"
#define WIDTH 256
#define HEIGHT 256

int32_t	main(void)
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	mlx_terminate(mlx);
	exit (EXIT_SUCCESS);
}
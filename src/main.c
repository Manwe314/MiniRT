/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:16:05 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/04 17:16:05 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/libft/includes/libft.h"

static int	init_minirt(t_minirt *minirt)
{
	minirt->width = WIDTH;
	minirt->height = HEIGHT;
	// Init mlx with a canvas size of 256x256 and the ability to resize the window.
	minirt->mlx = mlx_init(minirt->width , minirt->height, "minirt", true);

	if (!minirt->mlx)
		exit(ERROR);
	minirt->img = mlx_new_image(minirt->mlx, 256, 256);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);

	// Run the main loop and terminate on quit.
	return (SUCCESS);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	dot(t_vector3 a, t_vector3 b)
{
	float product;

	product = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (product);
}

void	hook(void *param)
{
	t_minirt *minirt;
	int x;
	int y;
	t_vector3 ray_direction;
	t_vector3 ray_origin;
	float a, b, c;
	float discriminant;
	t_vector2 coordinate;
	t_sphere *sphere;

	minirt = param;
	sphere = minirt->input_head->object;
	x = 0;
	ray_origin.x = 0;
	ray_origin.y = 0;
	ray_origin.z = -100;
	while (x < minirt->width)
	{
		y = 0;
		while (y < minirt->height)
		{
			coordinate.x = (float)x / (float)minirt->width;
			coordinate.y = (float)y / (float)minirt->height;
			coordinate.x = (coordinate.x * 2.0f) - 1.0f;
			coordinate.y = (coordinate.y * 2.0f) - 1.0f;
			ray_direction.x = coordinate.x;
			ray_direction.y = coordinate.y;
			ray_direction.z = 1;

			a = dot(ray_direction, ray_direction);
			b = 2 * dot(ray_origin, ray_direction);
			c = dot(ray_origin, ray_origin) - (sphere->radius * sphere->radius);

			discriminant = (b * b) - (4 * a * c);
			if (discriminant >= 0)
				mlx_put_pixel(minirt->img, x, y, get_rgba(255, 0, 0, 255));
			else
				mlx_put_pixel(minirt->img, x, y, get_rgba(0, 0, 0, 255));
			//printf("x: %d\ny: %d\n", x, y);
			y++;
		}
		x++;
	}

}

void close_function(void *param)
{
	t_minirt *minirt;

	minirt = param;

	mlx_delete_image(minirt->mlx, minirt->img);
	free(minirt->input_head->name);
	free(minirt->input_head->object);
}

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_minirt *minirt;

	minirt = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_hook(minirt->mlx, &close_function, minirt);
		mlx_close_window(minirt->mlx);
	}

}

float to_radian(float angle)
{
	return (angle * (M_PI / 180));
}

void get_input_list(t_minirt *minirt)
{
	t_sphere *sphere;
	t_input_list *head;

	sphere = malloc(sizeof(t_sphere));
	sphere->center.x = 0;
	sphere->center.y = 0;
	sphere->center.z = 0;
	sphere->radius = 50.0f;

	head = malloc(sizeof(t_input_list));
	head->name = ft_strdup("sphere");
	head->object = sphere;
	head->next = 0;

	minirt->input_head = head;
}


int main()
{
	t_minirt minirt;

	if (init_minirt(&minirt) == ERROR)
		return (ERROR);
	get_input_list(&minirt);
	mlx_loop_hook(minirt.mlx, &hook, &minirt);
	mlx_key_hook(minirt.mlx, &keyhook, &minirt);

	mlx_loop(minirt.mlx);
	mlx_terminate(minirt.mlx);
	return (SUCCESS);
}

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
	minirt->img = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
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

t_vector3 add_vector3(t_vector3 a, t_vector3 b)
{
	t_vector3 sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	return (sum);
}

t_vector3 subtract_vector3(t_vector3 a, t_vector3 b)
{
	t_vector3 subtraction;

	subtraction.x = a.x - b.x;
	subtraction.y = a.y - b.y;
	subtraction.z = a.z - b.z;
	return (subtraction);
}

float min(float a, float b)
{
	if (a > b)
		return b;
	else
		return a;
}

float max(float a, float b)
{
	if (a < b)
		return b;
	else
		return a;
}

t_vector3 multiply_vector_scalar(t_vector3 a, float b)
{
	t_vector3 product;

	product.x = a.x * b;
	product.y = a.y * b;
	product.z = a.z * b;
	return product;
}

t_vector3 normalize(t_vector3 a)
{
	float length;
	t_vector3 normal;

	length = (float)sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
	normal.x = a.x / length;
	normal.y = a.y / length;
	normal.z = a.z / length;
	return (normal);
}

void	hook(void *param)
{
	return ;
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

void print_input(t_minirt *minirt)
{
	t_input_list *input;

	input = minirt->input_head;
	while (input != 0)
	{
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("name: %s\n", input->name);
		if (ft_strncmp(input->name, "Ambient", 7) == 0)
		{
			t_ambient *amb = input->object;
			printf("intense: %f\ncolor: %f , %f, %f.\n", amb->intensity, amb->color.x, amb->color.y, amb->color.z);
		}
		if (ft_strncmp(input->name, "Camera", 6) == 0)
		{
			t_camera *cam = input->object;
			printf("fov: %f\ncoords: %f , %f, %f.\nnormal: %f , %f, %f.\n",cam->fov, cam->position.x, cam->position.y, cam->position.z, cam->orientation.x, cam->orientation.y, cam->orientation.z);
		}
		if (ft_strncmp(input->name, "Light", 5) == 0)
		{
			t_light *cam = input->object;
			printf("brightness: %f\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->brightness, cam->position.x, cam->position.y, cam->position.z, cam->color.x, cam->color.y, cam->color.z);
		}
		if (ft_strncmp(input->name, "Sphere", 6) == 0)
		{
			t_sphere *cam = input->object;
			printf("radious: %f\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->radius, cam->center.x, cam->center.y, cam->center.z, cam->color.x, cam->color.y, cam->color.z);
		}
		if (ft_strncmp(input->name, "Plane", 5) == 0)
		{
			t_plane *cam = input->object;
			printf("normal: %f , %f, %f.\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->normal.x, cam->normal.y, cam->normal.z, cam->point_on_plane.x, cam->point_on_plane.y, cam->point_on_plane.z, cam->color.x, cam->color.y, cam->color.z);
		}
		if (ft_strncmp(input->name, "Cylinder", 8) == 0)
		{
			t_cylinder *cam = input->object;
			printf("height: %f\ndiametre: %f\nnormal: %f , %f, %f.\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->height ,cam->diameter,cam->normal_axis.x, cam->normal_axis.y, cam->normal_axis.z, cam->centre.x, cam->centre.y, cam->centre.z, cam->color.x, cam->color.y, cam->color.z);
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		input = input->next;
	}

}

int main(int argc, char *argv[])
{
	t_minirt minirt;
	int	fd;

	if ( argc == 2  && !check_file(argv[1]))
		fd = open(argv[1], O_RDONLY);
	else
		return (0);
	/*if (init_minirt(&minirt) == ERROR)
		return (ERROR);*/
	get_input_list(&minirt, fd);
	validate_input(&minirt);
	//mlx_loop_hook(minirt.mlx, &hook, &minirt);
	//mlx_key_hook(minirt.mlx, &keyhook, &minirt);
	//mlx_loop(minirt.mlx);
	//mlx_terminate(minirt.mlx);
	//print_input(&minirt);
	close(fd);
	return (SUCCESS);
}

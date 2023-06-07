/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:16:05 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/07 08:53:39 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/libft/includes/libft.h"

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

void close_function(void *param)
{
	t_minirt *minirt;

	minirt = param;

	mlx_delete_image(minirt->mlx, minirt->img);
	free(minirt->input_head->name);
	free(minirt->input_head->object);
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

t_vector4	clamp(t_vector4 color, float min, float max)
{
	if (color.x < min)
		color.x = min;
	else if (color.x > max)
		color.x = max;
	if (color.y < min)
		color.y = min;
	else if (color.y > max)
		color.y = max;
	if (color.z < min)
		color.z = min;
	else if (color.z > max)
		color.z = max;
	if (color.w < min)
		color.w = min;
	else if (color.w > max)
		color.w = max;
	return (color);

}

void print_mat(t_matrix4x4 mat)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("%f ", mat.matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

static int	init_minirt(t_minirt *minirt)
{
	int i;
	int j;

	minirt->width = WIDTH;
	minirt->height = HEIGHT;

	minirt->error = 1;

	minirt->camera.fov = 90.0f;
	minirt->camera.pos = vector3(0.0f, 0.0f, 5.0f);
	minirt->camera.forward = vector3(0.0f, 0.0f, 1.0f);

	minirt->mlx = mlx_init(minirt->width ,minirt->height, "minirt", true);
	if (!minirt->mlx)
		exit(ERROR);
	minirt->camera.ray_dir = malloc(sizeof(t_vector3) * minirt->width * minirt->height);
	if (!minirt->camera.ray_dir)
		exit(ERROR);
	minirt->img = mlx_new_image(minirt->mlx, minirt->width, minirt->height);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
	calculateprojection(minirt);
	minirt->moved = true;
	return (SUCCESS);
}


/*
(x-a)^2 + (y-b)^2 - r^2 = 0
x = a + bt;
y = c + dt;
(a + bt - a)^2 + (c + dt - b)^2 - r^2 = 0
bt^2 + dt^2 + 2abt - 2bt^2 + c^2 + d^2 + 2cdt - 2bdt - r^2 = 0
t^2(b - d) + t(2ab - 2bd) + (a^2 + b^2 - r^2) = 0
det = (2ab - 2bd)^2 - 4(b - d)(a^2 + b^2 - r^2)
t = (-b + sqrt(det)) / 2(b - d)
t = (-b - sqrt(det)) / 2(b - d)
*/



int main(int argc, char *argv[])
{
	t_minirt minirt;
	//minirt.model = get_model();
	int	fd;

	// if (argc == 2  && !check_file(argv[1]))
		// fd = open(argv[1], O_RDONLY);
	// else
		// return (0);
	if (init_minirt(&minirt) == ERROR)
		return (ERROR);
	//get_input_list(&minirt, fd);
	//validate_input(&minirt);
	//minirt.scene = create the 3d world

	mlx_resize_hook(minirt.mlx, &resize, &minirt);
	mlx_loop_hook(minirt.mlx, &hook, &minirt);
	mlx_cursor_hook(minirt.mlx, &cursor, &minirt);
	mlx_key_hook(minirt.mlx, &keyhook, &minirt);

	if (minirt.error != ERROR)
		mlx_loop(minirt.mlx);
	mlx_terminate(minirt.mlx);
	if (minirt.camera.ray_dir)
		free(minirt.camera.ray_dir);
	//system("leaks minirt");
	close(fd);
	return (SUCCESS);
}


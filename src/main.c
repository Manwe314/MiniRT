/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:16:05 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/15 08:56:23 by beaudibe         ###   ########.fr       */
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
			printf("height: %f\ndiametre: %f\nnormal: %f , %f, %f.\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->height ,cam->radius,cam->normal.x, cam->normal.y, cam->normal.z, cam->center.x, cam->center.y, cam->center.z, cam->color.x, cam->color.y, cam->color.z);
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		input = input->next;
	}

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

t_material return_material(void)
{
	t_material material;

	material.emission_color = vector3(1.0f, 1.0f, 1.0f);
	material.color = vector3(1.0f, 1.0f, 1.0f);
	material.specular_color = vector3(1.0f, 1.0f, 1.0f);
	material.emission_strength = 50.0f;
	material.emission = vector3_multiply_float(material.emission_color, material.emission_strength);
	material.smoothness = 1.0f;
	material.specular_probability = 0.0f;
	return (material);
}

t_circle	get_circle_from_cylinder(t_cylinder cylinder, bool is_top, t_minirt *minirt)
{
	t_circle circle;
	static int i;

	circle.radius = cylinder.radius;
	circle.material = cylinder.material;
	if (is_top)
	{
		circle.center = vector3_add(cylinder.center, vector3_multiply_float(cylinder.normal, cylinder.height));
		circle.normal = cylinder.normal;
	}
	else
	{
		circle.center = vector3_subtract(cylinder.center, vector3_multiply_float(cylinder.normal, cylinder.height));
		circle.normal = vector3_multiply_float(cylinder.normal, -1.0f);
	}
	// minirt->scene.circle[i++] = circle;
	// minirt->scene.nb_circle++;
	return (circle);
}

static int	init_minirt(t_minirt *minirt)
{
	int i;
	int j;

	minirt->width = WIDTH;
	minirt->height = HEIGHT;

	minirt->error = 1;

	minirt->camera.fov = 90.0f;
	minirt->camera.pos = vector3(0.0f, 1.0f, 2.5f);
	minirt->camera.forward = vector3(0.0f, 0.0f, 1.0f);

	minirt->mlx = mlx_init(minirt->width ,minirt->height, "minirt", true);
	if (!minirt->mlx)
		exit(ERROR);
	minirt->camera.ray_dir = malloc(sizeof(t_vector3) * minirt->width * minirt->height);
	if (!minirt->camera.ray_dir)
		exit(ERROR);
	minirt->img = mlx_new_image(minirt->mlx, minirt->width, minirt->height);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
	minirt->camera.pitch = 0.0f;
	minirt->camera.yaw = 0.0f;
	calculateprojection(minirt);
	minirt->moved = true;
	minirt->camera.is_clicked = false;
	minirt->x = 0;
	minirt->y = 1;
	minirt->z = 0;
	minirt->radius = 1.0f;
	minirt->scene.material[0] = return_material();
	minirt->scene.material[1] = return_material();
	minirt->scene.material[2] = return_material();
	minirt->scene.material[1].emission = vector3(0.0f, 0.0f, 0.0f);
	minirt->scene.material[1].emission_strength = 0.0f;
	minirt->scene.material[1].emission_color = vector3(0.0f, 0.0f, 0.0f);
	minirt->scene.material[1].color = vector3(1.0f, 1.0f, 1.0f);

	minirt->scene.material[2].emission = vector3(0.0f, 0.0f, 0.0f);
	minirt->scene.material[2].emission_strength = 0.0f;
	minirt->scene.material[2].emission_color = vector3(0.0f, 0.0f, 0.0f);
	minirt->scene.material[2].color = vector3(0.0f, 0.0f, 1.0f);

	// minirt->scene.sphere[1].center = vector3(0.0f, -10.0f, 0.0f);
	// minirt->scene.sphere[1].radius = 10.0f;
	// minirt->scene.sphere[1].material = minirt->scene.material[1];
	// minirt->scene.sphere[1].material.color = vector3(0.5f, 0.6f, 0.7f);


	// minirt->scene.sphere[2].center = vector3(5.0f, 50.0f, 20.0f);
	// minirt->scene.sphere[2].radius = 20.0f;
	// minirt->scene.sphere[2].material = minirt->scene.material[0];

	// minirt->scene.sphere[0].center = vector3(0.0f, 1.0f, 0.0f);
	// minirt->scene.sphere[0].radius = 1.0f;
	// minirt->scene.sphere[0].material = minirt->scene.material[2];
	// minirt->scene.sphere[0].material.color = vector3(1.0f, 1.0f, 1.0f);
	// minirt->scene.sphere[0].material.smoothness = 1.0f;
	// minirt->scene.sphere[0].material.specular_probability = 1.0f;


	// minirt->scene.sphere[1].center = vector3(1.7f, 0.5f, -0.2f);
	// minirt->scene.sphere[1].radius = 0.8f;
	// minirt->scene.sphere[1].material = minirt->scene.material[2];
	// minirt->scene.sphere[1].material.color = vector3(1.0f, 1.0f, 1.0f);
	// minirt->scene.sphere[1].material.smoothness = 1.0f;
	// minirt->scene.sphere[1].material.specular_probability = 1.0f;
//
	// minirt->scene.sphere[4].center = vector3(0.0f, 1.0f, 0.0f);
	// minirt->scene.sphere[4].radius = 2.0f;
	// minirt->scene.sphere[4].material = minirt->scene.material[2];


	minirt->scene.plane[0].point_on_plane = vector3(0.0f, 0.0f, 0.0f);
	minirt->scene.plane[0].normal = vector3(0.0f, 1.0f, 0.0f);
	minirt->scene.plane[0].normal = vector3_normalize(minirt->scene.plane[0].normal);
	minirt->scene.plane[0].material = minirt->scene.material[1];
	minirt->scene.plane[0].material.color = vector3(0.5f, 0.0f, 0.0f);

	minirt->scene.nb_plane = 1;

	minirt->scene.cylinder[0].center = vector3(-1.0f, 1.0f, 0.0f);
	minirt->scene.cylinder[0].normal = vector3(0.0f, 1.0f, 0.0f);
	minirt->scene.cylinder[0].normal = vector3_normalize(minirt->scene.cylinder[0].normal);
	minirt->scene.cylinder[0].radius = 0.5f;
	minirt->scene.cylinder[0].height = 1.0f;
	minirt->scene.cylinder[0].material = minirt->scene.material[1];
	minirt->scene.cylinder[0].material.color = vector3(0.9f, 0.5f, 0.8f);
	minirt->scene.cylinder[0].circle_top = get_circle_from_cylinder(minirt->scene.cylinder[0], 1, minirt);
	minirt->scene.cylinder[0].circle_bottom = get_circle_from_cylinder(minirt->scene.cylinder[0], 0, minirt);
	minirt->scene.nb_cylinder = 1;

	minirt->scene.circle[0].center = vector3(-1.0f, 1.5f, 0.0f);
	minirt->scene.circle[0].normal = vector3(0.0f, 0.0, 1.0f);
	minirt->scene.circle[0].normal = vector3_normalize(minirt->scene.circle[0].normal);
	minirt->scene.circle[0].radius = 0.5f;
	minirt->scene.circle[0].material = minirt->scene.material[1];
	minirt->scene.circle[0].material.color = vector3(0.9f, 0.5f, 0.8f);
	// printf("circle: %f, %f, %f\n", minirt->scene.circle[0].center.x, minirt->scene.circle[0].center.y, minirt->scene.circle[0].center.z);

	t_sphere light;
	light.center = vector3(1.0f, 1.5f, 0.0f);
	light.radius = 0.5f;
	light.material = minirt->scene.material[0];
	light.material.color = vector3(1.0f, 0.0f, 1.0f);
	light.material.emission_color = vector3(1.0f, 1.0f, 1.0f);
	light.material.emission_strength = 50.0f;
	light.material.emission = vector3_multiply_float(light.material.emission_color, light.material.emission_strength);
	minirt->scene.sphere[0] = light;

	minirt->scene.nb_sphere = 1;
	minirt->scene.nb_circle = 0;


	/*
	minirt->scene.material[0] = add_material(vector3(0.0f, 0.0f, 0.0f), 1.0f, 0.1f);
	minirt->scene.material[1] = add_material(vector3(0.0f, 0.0f, 0.0f), 0.1f, 0.1f);
	minirt->scene.sphere[0] = add_sphere(vector3(0.0f, 0.6f, 0.0f),  0.6f, vector3(1.0f, 0.0f, 0.0f), 0);
	minirt->scene.sphere[1] = add_sphere(vector3(0.0f, -10.0f, 0.0f),  10.0f, vector3(0.0f, 1.0f, 0.0f), 1);
	minirt->scene.sphere[2] = add_sphere(vector3(0.0f, 0.0f, 0.5f),  0.6f, vector3(0.0f, 0.0f, 1.0f), 0);
	minirt->scene.sphere[3] = add_sphere(vector3(-0.5f, 0.0f, 0.0f), 0.6f, vector3(1.0f, 1.0f, 0.0f), 0);
	minirt->scene.sphere[4] = add_sphere(vector3(0.0f, -0.5f, 0.0f), 0.6f, vector3(1.0f, 0.0f, 1.0f), 0);
	minirt->scene.sphere[5] = add_sphere(vector3(0.0f, 0.0f, -0.5f), 0.6f, vector3(1.0f, 1.0f, 1.0f), 0);
	minirt->scene.nb_sphere =2;
	*/
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
	//get_input_list(&minirt, fd);
	//validate_input(&minirt);
	//minirt.scene = create the 3d world


	if (init_minirt(&minirt) == ERROR)
		return (ERROR);

	mlx_resize_hook(minirt.mlx, &resize, &minirt);
	mlx_loop_hook(minirt.mlx, &hook, &minirt);
	mlx_cursor_hook(minirt.mlx, &cursor, &minirt);
	mlx_key_hook(minirt.mlx, &keyhook, &minirt);
	mlx_mouse_hook(minirt.mlx, &mousehook, &minirt);
	if (minirt.error != ERROR)
		mlx_loop(minirt.mlx);
	mlx_terminate(minirt.mlx);
	if (minirt.camera.ray_dir)
		free(minirt.camera.ray_dir);
	close(fd);
	// int i = -100;
	// while (++i < 100)
		// printf("%f\n", ((random_float()) ));



	//system("leaks minirt");
	return (SUCCESS);
}
/*

float	random_float(float min, float max)
{
	float	random;

	min = -0.5f;
	max = 0.5f;
	random = (float)rand() / (float)RAND_MAX;
	return (min + (max - min) * random);
}

t_vector3 vector3_random(float min, float max)
{
	t_vector3 vec;

	vec.x = random_float(min, max);
	vec.y = random_float(min, max);
	vec.z = random_float(min, max);
	return (vec);
}
*/

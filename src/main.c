/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:16:05 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/15 08:56:23 by beaudibe         ###   ########.fr       */
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
			printf("height: %f\ndiametre: %f\nnormal: %f , %f, %f.\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n",cam->height ,cam->radius,cam->normal.x, cam->normal.y, cam->normal.z, cam->center.x, cam->center.y, cam->center.z, cam->color.x, cam->color.y, cam->color.z);
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		input = input->next;
	}

}

t_material create_material(void)
{
	t_material material;

	material.color = vector3(1.0f, 1.0f, 1.0f);
	material.specular_color = vector3(1.0f, 1.0f, 1.0f);

	material.emission_strength = 0.0f;
	material.emission_color = vector3(1.0f, 1.0f, 1.0f);
	material.emission = vector3(0.0f, 0.0f, 0.0f);
	material.smoothness = 1.0f;
	material.specular_probability = 0.0f;
	material.flag = 0;
}

t_scene	create_scene(void)
{
	t_scene scene;
	t_material red;
	t_material green;
	t_material blue;
	t_material white;
	t_material light;
	t_material yellow;

	red = create_material();
	red.color = vector3(1.0f, 0.0f, 0.0f);
	scene.material[0] = red;

	green = create_material();
	green.color = vector3(0.0f, 1.0f, 0.0f);
	scene.material[1] = green;

	blue = create_material();
	blue.color = vector3(0.0f, 0.0f, 1.0f);
	scene.material[2] = blue;

	white = create_material();
	white.color = vector3(1.0f, 1.0f, 1.0f);
	scene.material[3] = white;

	light = create_material();
	light.color = vector3(1.0f, 1.0f, 1.0f);
	light.emission_strength = 1.0f;
	light.emission = vector3_multiply_float(light.color, light.emission_strength);
	scene.material[4] = light;

	yellow = create_material();
	yellow.color = vector3(1.0f, 1.0f, 0.0f);
	scene.material[5] = yellow;

	t_sphere sphere;
	sphere.center = vector3(1.0f, 1.0f, 0.0f);
	sphere.radius = 1.0f;
	sphere.material = white;
	sphere.material.specular_probability = 1.0f;
	scene.sphere[0] = sphere;

	t_sphere sphere2;
	sphere2.center = vector3(-1.0f, 1.0f, 0.0f);
	sphere2.radius = 1.0f;
	sphere2.material = white;
	sphere2.material.specular_probability = 1.0f;
	scene.sphere[1] = sphere2;

	t_plane plane;
	plane.point_on_plane = vector3(0.0f, 0.0f, 0.0f);
	plane.normal = vector3(0.0f, 1.0f, 0.0f);
	plane.material = white;
	scene.plane[0] = plane;

	t_plane plane2;
	plane2.point_on_plane = vector3(0.0f, 4.0f, 0.0f);
	plane2.normal = vector3(0.0f, -1.0f, 0.0f);
	plane2.material = light;
	scene.plane[1] = plane2;

	t_plane plane3;
	plane3.point_on_plane = vector3(0.0f, 0.0f, -4.0f);
	plane3.normal = vector3(0.0f, 0.0f, 1.0f);
	plane3.material = green;
	scene.plane[2] = plane3;

	t_plane plane4;
	plane4.point_on_plane = vector3(0.0f, 0.0f, 4.0f);
	plane4.normal = vector3(0.0f, 0.0f, -1.0f);
	plane4.material = red;
	scene.plane[3] = plane4;

	t_plane plane5;
	plane5.point_on_plane = vector3(-4.0f, 0.0f, 0.0f);
	plane5.normal = vector3(1.0f, 0.0f, 0.0f);
	plane5.material = blue;
	scene.plane[4] = plane5;

	t_plane plane6;
	plane6.point_on_plane = vector3(4.0f, 0.0f, 0.0f);
	plane6.normal = vector3(-1.0f, 0.0f, 0.0f);
	plane6.material = yellow;
	scene.plane[5] = plane6;

	t_light light1;
	light1.position = vector3(0.0f, 3.0f, 0.0f);
	light1.color = vector3(1.0f, 1.0f, 1.0f);
	light1.brightness = 1.0f;
	scene.light[0] = light1;


	scene.nb_light = 0;
	scene.nb_sphere = 0;
	scene.nb_plane = 0;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	scene.nb_circle = 0;
	scene.nb_cone = 0;
	scene.nb_hyperboloid = 0;
	scene.nb_paraboloid = 0;
	scene.nb_obj = 0;

	scene.nb_sphere = 2;
	scene.nb_plane = 6;

	scene.nb_light = 1;

	return (scene);
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
	minirt->moved = true;
	minirt->camera.is_clicked = false;

	return (SUCCESS);
}


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
	minirt.scene = create_scene();
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:20:47 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:20:47 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/includes/libft.h"
#include "minirt.h"

#define WIDTH 500
#define HEIGHT 500


float	min(float a, float b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

float	max(float a, float b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

void	close_function(void *param)
{
	t_minirt *minirt;

	minirt = param;

	mlx_delete_image(minirt->mlx, minirt->img);
	free(minirt->input_head->name);
	free(minirt->input_head->object);
}

float	to_radian(float angle)
{
	return (angle * (M_PI / 180));
}

void	print_input(t_minirt *minirt)
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
			printf("intense: %f\ncolor: %f , %f, %f.\n", amb->intensity,
				amb->color.x, amb->color.y, amb->color.z);
		}
		if (ft_strncmp(input->name, "Camera", 6) == 0)
		{
			t_camera *cam = input->object;
			printf("fov: %f\ncoords: %f , %f, %f.\nnormal: %f , %f, %f.\n",
				cam->fov, cam->position.x, cam->position.y, cam->position.z,
				cam->orientation.x, cam->orientation.y, cam->orientation.z);
		}
		if (ft_strncmp(input->name, "Light", 5) == 0)
		{
			t_light *cam = input->object;
			printf("brightness: %f\ncoords: %f , %f, %f.\ncolor: %f , %f, \
				%f.\n", cam->brightness, cam->position.x, cam->position.y, \
				cam->position.z, cam->color.x, cam->color.y, cam->color.z);
		}
		if (ft_strncmp(input->name, "Sphere", 6) == 0)
		{
			t_sphere *cam = input->object;
			printf("radious: %f\ncoords: %f , %f, %f.\ncolor: %f , %f, %f.\n", \
				cam->radius, cam->center.x, cam->center.y, cam->center.z, \
				cam->color.x, cam->color.y, cam->color.z);
		}
		if (ft_strncmp(input->name, "Plane", 5) == 0)
		{
			t_plane *cam = input->object;
			printf("normal: %f , %f, %f.\ncoords: %f , %f, %f.\ncolor: %f , %f, \
				%f.\n", cam->normal.x, cam->normal.y, cam->normal.z, \
				cam->point_on_plane.x, cam->point_on_plane.y, \
				cam->point_on_plane.z, cam->color.x, cam->color.y, \
				cam->color.z);
		}
		if (ft_strncmp(input->name, "Cylinder", 8) == 0)
		{
			t_cylinder *cam = input->object;
			printf("height: %f\ndiametre: %f\nnormal: %f , %f, %f.\ncoords: %f , \
				%f, %f.\ncolor: %f , %f, %f.\n", cam->height, cam->radius, \
				cam->normal.x, cam->normal.y, cam->normal.z, cam->center.x, \
				cam->center.y, cam->center.z, cam->color.x, cam->color.y, \
				cam->color.z);
			printf("height: %f\ndiametre: %f\nnormal: %f , %f, %f.\ncoords: %f , \
				%f, %f.\ncolor: %f , %f, %f.\n", cam->height, cam->radius, \
				cam->normal.x, cam->normal.y, cam->normal.z, cam->center.x, \
				cam->center.y, cam->center.z, cam->color.x, cam->color.y, \
				cam->color.z);
		}
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		input = input->next;
	}
}

t_material	return_material(void)
{
	t_material material;

	material.emission_color = vector3(1.0f, 1.0f, 1.0f);
	material.color = vector3(1.0f, 0.0f, 0.0f);
	material.specular_color = vector3(1, 1, 1);
	material.emission_strength = 0.0f;
	material.emission = vector3_multiply_float(material.emission_color, \
		material.emission_strength);
	material.smoothness = 1.0f;
	material.specular_probability = 1.0f;
	material.flag = 0;
	return (material);
}

t_circle	get_circle_from_cylinder(t_cylinder cylinder, bool is_top,
		t_minirt *minirt)
{
	t_circle circle;
	static int i;

	circle.radius = cylinder.radius;
	circle.material = cylinder.material;
	if (is_top)
	{
		circle.center = vector3_add(cylinder.center,
			vector3_multiply_float(cylinder.normal, cylinder.height));
		circle.normal = cylinder.normal;
	}
	else
	{
		circle.center = vector3_subtract(cylinder.center,
			vector3_multiply_float(cylinder.normal, cylinder.height));
		circle.normal = vector3_multiply_float(cylinder.normal, -1.0f);
	}
	// minirt->scene.circle[i++] = circle;
	// minirt->scene.nb_circle++;
	return (circle);
}

t_scene	create_scene(void)
{
	t_scene		scene;
	t_material	red;
	t_material	green;
	t_material	blue;
	t_material	white;
	t_material	yellow;
	t_material	purple;
	t_material	black;
	t_material	light;

	float emission_strength = 0.0f;

	red = return_material();
	red.color = vector3(1.0f, 0.0f, 0.0f);
	red.emission_strength = emission_strength;
	red.emission_color = vector3(1.0f, 0.0f, 0.0f);
	red.emission = vector3_multiply_float(red.emission_color, \
		red.emission_strength);

	green = return_material();
	green.color = vector3(0.0f, 1.0f, 0.0f);
	green.emission_strength = emission_strength;
	green.emission_color = vector3(0.0f, 1.0f, 0.0f);
	green.emission = vector3_multiply_float(green.emission_color, \
		green.emission_strength);

	blue = return_material();
	blue.color = vector3(0.0f, 0.0f, 1.0f);
	blue.emission_strength = emission_strength;
	blue.emission_color = vector3(0.0f, 0.0f, 1.0f);
	blue.emission = vector3_multiply_float(blue.emission_color, \
		blue.emission_strength);

	white = return_material();
	white.color = vector3(1.0f, 1.0f, 1.0f);
	white.emission_strength = emission_strength;
	white.emission_color = vector3(1.0f, 1.0f, 1.0f);
	white.emission = vector3_multiply_float(white.emission_color, \
		white.emission_strength);

	yellow = return_material();
	yellow.color = vector3(1.0f, 1.0f, 0.0f);
	yellow.emission_strength = emission_strength;
	yellow.emission_color = vector3(1.0f, 1.0f, 0.0f);
	yellow.emission = vector3_multiply_float(yellow.emission_color, \
		yellow.emission_strength);

	purple = return_material();
	purple.color = vector3(1.0f, 0.0f, 1.0f);
	purple.emission_strength = emission_strength;
	purple.emission_color = vector3(1.0f, 0.0f, 1.0f);
	purple.emission = vector3_multiply_float(purple.emission_color, \
		purple.emission_strength);

	black = return_material();
	black.color = vector3(0.0f, 0.0f, 0.0f);
	black.emission_strength = emission_strength;
	black.emission_color = vector3(0.0f, 0.0f, 0.0f);
	black.emission = vector3_multiply_float(black.emission_color, \
		black.emission_strength);

	light = return_material();
	light.color = vector3(1.0f, 1.0f, 1.0f);
	light.emission_strength = 0.6f;
	light.emission_color = vector3(1.0f, 1.0f, 1.0f);
	light.emission = vector3_multiply_float(light.emission_color, \
		light.emission_strength);

	t_triangle triangle;
	triangle.p[0] = vector3(-3, 4.9f, 0);
	triangle.p[1] = vector3(3, 4.9f, 0);
	triangle.p[2] = vector3(0, 4.9f, 1);
	triangle.material = light;
	triangle.material.emission_strength = 10.0f;
	triangle.material.emission_color = vector3(1.0f, 1.0f, 1.0f);
	triangle.material.emission = vector3_multiply_float(triangle.material.emission_color, \
		triangle.material.emission_strength);
	scene.triangle[0] = triangle;

	t_sphere sphere;
	sphere.center = vector3(-1.0f, 1.5f, 0.0f);
	sphere.radius = 1.0f;
	sphere.material = white;
	sphere.material.specular_probability = 1.0f;
	sphere.material.smoothness = 1.0f;
	sphere.material.specular_color = vector3(1.0f, 1.0f, 1.0f);
	scene.sphere[0] = sphere;

	t_sphere sphere2;
	sphere2.center = vector3(1.0f, 1.5f, 0.0f);
	sphere2.radius = 1.0f;
	sphere2.material = blue;
	sphere2.material.smoothness = 0.9f;
	sphere2.material.specular_probability = 1.0f;
	sphere2.material.specular_color = vector3(0.0f, 0.0f, 1.0f);
	scene.sphere[1] = sphere2;

	t_sphere sphere3;
	sphere3.center = vector3(0.0f, 3.3f, 0.0f);
	sphere3.radius = 1.0f;
	sphere3.material = white;
	sphere3.material.color = vector3(0.3f, 0.6f, 0.2f);
	sphere3.material.specular_probability = 0.0f;
	sphere3.material.specular_color = vector3(0.3f, 0.9f, 0.5f);
	sphere3.material.flag = CHECKER_PATTERN;
	scene.sphere[2] = sphere3;

	t_plane plane;
	plane.point_on_plane = vector3(0.0f, 0.0f, 0.0f);
	plane.normal = vector3(0.0f, 1.0f, 0.0f);
	plane.normal = vector3_normalize(plane.normal);
	plane.material = white;
	plane.material.flag = CHECKER_PATTERN;
	scene.plane[0] = plane;

	t_plane plane2;
	plane2.point_on_plane = vector3(0.0f, 5.0f, 0.0f);
	plane2.normal = vector3(0.0f, -1.0f, 0.0f);
	plane2.normal = vector3_normalize(plane2.normal);
	plane2.material = light;
	scene.plane[1] = plane2;

	t_plane plane3;
	plane3.point_on_plane = vector3(0.0f, 0.0f, -5.0f);
	plane3.normal = vector3(0.0f, 0.0f, 1.0f);
	plane3.normal = vector3_normalize(plane3.normal);
	plane3.material = purple;
	scene.plane[2] = plane3;

	t_plane plane4;
	plane4.point_on_plane = vector3(0.0f, 0.0f, 5.0f);
	plane4.normal = vector3(0.0f, 0.0f, -1.0f);
	plane4.normal = vector3_normalize(plane4.normal);
	plane4.material = white;
	scene.plane[3] = plane4;

	t_plane plane5;
	plane5.point_on_plane = vector3(-5.0f, 0.0f, 0.0f);
	plane5.normal = vector3(1.0f, 0.0f, 0.0f);
	plane5.normal = vector3_normalize(plane5.normal);
	plane5.material = white;
	scene.plane[4] = plane5;

	t_plane plane6;
	plane6.point_on_plane = vector3(5.0f, 0.0f, 0.0f);
	plane6.normal = vector3(-1.0f, 0.0f, 0.0f);
	plane6.normal = vector3_normalize(plane6.normal);
	plane6.material = white;
	scene.plane[5] = plane6;

	float light_strength = 0.3f;

	t_light led;
	led.position = vector3(3, 2, 0);
	led.color = vector3(1.0f, 1.0f, 1.0f);
	led.brightness = light_strength;
	scene.light[0] = led;

	t_light led2;
	led2.position = vector3(0, 4.5f, 0);
	led2.color = vector3(1.0f, 1.0f, 1.0f);
	led2.brightness = light_strength;
	scene.light[1] = led2;

	t_light led3;
	led3.position = vector3(3, 2, 0);
	led3.color = vector3(0.0f, 0.0f, 1.0f);
	led3.brightness = light_strength;
	scene.light[2] = led3;

	t_light led4;
	led4.position = vector3(-3, 2, 0);
	led4.color = vector3(1.0f, 0.0f, 1.0f);
	led4.brightness = light_strength;
	scene.light[3] = led4;

	t_light led5;
	led5.position = vector3(0, 2, 3);
	led5.color = vector3(1.0f, 1.0f, 0.0f);
	led5.brightness = light_strength;
	scene.light[4] = led5;

	scene.nb_sphere = 0;
	scene.nb_plane = 0;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	scene.nb_circle = 0;
	scene.nb_cone = 0;
	scene.nb_hyperboloid = 0;
	scene.nb_paraboloid = 0;
	scene.nb_obj = 0;

	scene.nb_plane = 6;
	scene.nb_sphere = 3;
	scene.nb_light = 1;
	scene.nb_triangle = 0;
	return (scene);
}

t_scene	create_scene2(void)
{
	t_scene		scene;
	t_material	red;
	t_material	green;
	t_material	blue;
	t_material	white;
	t_material	light;

	float emission_strength = 0.0f;

	red = return_material();
	red.color = vector3(1.0f, 0.0f, 0.0f);
	red.emission_strength = emission_strength;
	red.emission_color = vector3(1.0f, 0.0f, 0.0f);
	red.emission = vector3_multiply_float(red.emission_color, \
		red.emission_strength);

	green = return_material();
	green.color = vector3(0.0f, 1.0f, 0.0f);
	green.emission_strength = emission_strength;
	green.emission_color = vector3(0.0f, 1.0f, 0.0f);
	green.emission = vector3_multiply_float(green.emission_color, \
		green.emission_strength);

	blue = return_material();
	blue.color = vector3(0.0f, 0.0f, 1.0f);
	blue.emission_strength = emission_strength;
	blue.emission_color = vector3(0.0f, 0.0f, 1.0f);
	blue.emission = vector3_multiply_float(blue.emission_color, \
		blue.emission_strength);

	white = return_material();
	white.color = vector3(1.0f, 1.0f, 1.0f);
	white.emission_strength = emission_strength;
	white.emission_color = vector3(1.0f, 1.0f, 1.0f);
	white.emission = vector3_multiply_float(white.emission_color, \
		white.emission_strength);

	light = return_material();
	light.color = vector3(1.0f, 1.0f, 1.0f);
	light.emission_strength = 1.0f;
	light.emission_color = vector3(1.0f, 1.0f, 1.0f);
	light.emission = vector3_multiply_float(light.emission_color, \
		light.emission_strength);

	t_triangle triangle;
	triangle.p[0] = vector3(-1, 4, 0);
	triangle.p[1] = vector3(1, 4, 0);
	triangle.p[2] = vector3(0, 4, 1);
	triangle.material = light;
	scene.triangle[0] = triangle;

	t_sphere sphere;
	sphere.center = vector3(-1.0f, 1.5f, 0.0f);
	sphere.radius = 1.0f;
	sphere.material = blue;
	sphere.material.specular_probability = 1.0f;
	scene.sphere[0] = sphere;

	t_sphere sphere2;
	sphere2.center = vector3(1.0f, 1.5f, 0.0f);
	sphere2.radius = 1.0f;
	sphere2.material = white;
	sphere2.material.specular_probability = 1.0f;
	scene.sphere[1] = sphere2;

	/*t_sphere sphere3;
	sphere3.center = vector3(1.0f, 1.5f, 0.0f);
	sphere3.radius = 1.0f;
	sphere3.material = white;
	sphere3.material.specular_probability = 1.0f;
	scene.sphere[0] = sphere3;*/

	t_plane plane;
	plane.point_on_plane = vector3(0.0f, 0.0f, 0.0f);
	plane.normal = vector3(0.0f, 1.0f, 0.0f);
	plane.normal = vector3_normalize(plane.normal);
	plane.material = red;
	plane.material.flag = CHECKER_PATTERN;
	scene.plane[0] = plane;

	t_plane plane2;
	plane2.point_on_plane = vector3(0.0f, 5.0f, 0.0f);
	plane2.normal = vector3(0.0f, -1.0f, 0.0f);
	plane2.normal = vector3_normalize(plane2.normal);
	plane2.material = light;
	scene.plane[1] = plane2;

	t_plane plane3;
	plane3.point_on_plane = vector3(0.0f, 0.0f, -5.0f);
	plane3.normal = vector3(0.0f, 0.0f, 1.0f);
	plane3.normal = vector3_normalize(plane3.normal);
	plane3.material = white;
	scene.plane[2] = plane3;

	t_plane plane4;
	plane4.point_on_plane = vector3(0.0f, 0.0f, 5.0f);
	plane4.normal = vector3(0.0f, 0.0f, -1.0f);
	plane4.normal = vector3_normalize(plane4.normal);
	plane4.material = white;
	scene.plane[3] = plane4;

	t_plane plane5;
	plane5.point_on_plane = vector3(-5.0f, 0.0f, 0.0f);
	plane5.normal = vector3(1.0f, 0.0f, 0.0f);
	plane5.normal = vector3_normalize(plane5.normal);
	plane5.material = red;
	scene.plane[4] = plane5;

	t_plane plane6;
	plane6.point_on_plane = vector3(5.0f, 0.0f, 0.0f);
	plane6.normal = vector3(-1.0f, 0.0f, 0.0f);
	plane6.normal = vector3_normalize(plane6.normal);
	plane6.material = green;
	scene.plane[5] = plane6;

	float light_strength = 5.0f;

	t_light led;
	led.position = vector3(0, 3, 0);
	led.color = vector3(1.0f, 1.0f, 1.0f);
	led.brightness = light_strength;
	scene.light[0] = led;

	t_light led2;
	led2.position = vector3(0, 4, 0);
	led2.color = vector3(1.0f, 1.0f, 1.0f);
	led2.brightness = light_strength;
	scene.light[1] = led2;

	scene.nb_sphere = 0;
	scene.nb_plane = 0;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	scene.nb_circle = 0;
	scene.nb_cone = 0;
	scene.nb_hyperboloid = 0;
	scene.nb_paraboloid = 0;
	scene.nb_obj = 0;

	scene.nb_plane = 1;
	scene.nb_sphere = 1;
	scene.nb_light = 1;
	scene.nb_triangle = 0;
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

	minirt->mlx = mlx_init(minirt->width, minirt->height, "minirt", true);
	if (!minirt->mlx)
		exit(ERROR);
	minirt->camera.ray_dir = malloc(sizeof(t_vector3) * minirt->width \
		* minirt->height);
	if (!minirt->camera.ray_dir)
		exit(ERROR);
	minirt->img = mlx_new_image(minirt->mlx, minirt->width, minirt->height);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
	minirt->camera.pitch = 0.0f;
	minirt->camera.yaw = 0.0f;

	minirt->camera.inv_lookat = mult_mat4x4(rotation_y(to_radian(minirt->camera.pitch)), \
		rotation_x(to_radian(minirt->camera.yaw)));
	minirt->moved = true;
	minirt->camera.is_clicked = false;
	minirt->x = 0;
	minirt->y = 1;
	minirt->z = 0;

	t_ambient ambient;
	ambient.intensity = 1.0f;
	ambient.color = vector3(1.0f, 0.0f, 1.0f);
	t_vector3 tmp = vector3_multiply_float(ambient.color, ambient.intensity);
	ambient.ambient = vector4(tmp.x, tmp.y, tmp.z, 1.0f);
	minirt->scene.ambient = ambient;
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_minirt minirt;

	// minirt.model = get_model();
	int fd;

	// if (argc == 2  && !check_file(argv[1]))
	// fd = open(argv[1], O_RDONLY);
	// else
	// return (0);
	// get_input_list(&minirt, fd);
	// validate_input(&minirt);
	// minirt.scene = create the 3d world

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

	// system("leaks minirt");
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

t_vector3	vector3_random(float min, float max)
{
	t_vector3 vec;

	vec.x = random_float(min, max);
	vec.y = random_float(min, max);
	vec.z = random_float(min, max);
	return (vec);
}
*/

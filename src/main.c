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

static bool	init_minirt(t_minirt *minirt)
{
	minirt->width = WIDTH;
	minirt->height = HEIGHT;
	minirt->error = 1;
	minirt->mlx = mlx_init(minirt->width, minirt->height, "minirt", true);
	if (!minirt->mlx)
		return (false);
	minirt->img = mlx_new_image(minirt->mlx, minirt->width, minirt->height);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);

	minirt->scene.nb_sphere = 0;
	minirt->scene.nb_plane = 0;
	minirt->scene.nb_triangle = 0;
	minirt->scene.nb_cylinder = 0;
	minirt->scene.nb_circle = 0;
	minirt->scene.nb_cone = 0;
	minirt->scene.nb_hyperboloid = 0;
	minirt->scene.nb_paraboloid = 0;
	minirt->scene.nb_obj = 0;
	minirt->scene.nb_ambient = 0;
	minirt->scene.nb_light = 0;
	minirt->scene.nb_camera = 0;
	minirt->moved = true;
	minirt->stop = false;
	return (true);
}

static void	get_scene(t_minirt *minirt)
{
	t_input_list	*tmp;

	while (minirt->input_head)
	{
		if (ft_strncmp("Ambient", minirt->input_head->name, 7) == 0)
			get_ambient(minirt, *(t_ambient *)minirt->input_head->object);
		else if (ft_strncmp("Camera", minirt->input_head->name, 6) == 0)
			get_camera(minirt, *(t_camera *)minirt->input_head->object);
		else if (ft_strncmp("Light", minirt->input_head->name, 5) == 0)
			get_light(minirt, *(t_light *)minirt->input_head->object);
		else if (ft_strncmp("Sphere", minirt->input_head->name, 6) == 0)
			get_sphere(minirt, *(t_sphere *)minirt->input_head->object);
		else if (ft_strncmp("Plane", minirt->input_head->name, 5) == 0)
			get_plane(minirt, *(t_plane *)minirt->input_head->object);
		else if (ft_strncmp("Cylinder", minirt->input_head->name, 8) == 0)
			get_cylinder(minirt, *(t_cylinder *)minirt->input_head->object);
		else if (ft_strncmp("Cone", minirt->input_head->name, 4) == 0)
			get_cone(minirt, *(t_cone *)minirt->input_head->object);
		tmp = minirt->input_head;
		minirt->input_head = minirt->input_head->next;
		free(tmp->name);
		free(tmp->object);
		free(tmp);
	}
	free(minirt->input_head);
}

void	free_scene(t_minirt *minirt)
{
	if (minirt->scene.nb_sphere)
		free(minirt->scene.sphere);
	if (minirt->scene.nb_plane)
		free(minirt->scene.plane);
	if (minirt->scene.nb_triangle)
		free(minirt->scene.triangle);
	if (minirt->scene.nb_cylinder)
		free(minirt->scene.cylinder);
	if (minirt->scene.nb_circle)
		free(minirt->scene.circle);
	if (minirt->scene.nb_cone)
		free(minirt->scene.cone);
	if (minirt->scene.nb_hyperboloid)
		free(minirt->scene.hyperboloid);
	if (minirt->scene.nb_paraboloid)
		free(minirt->scene.paraboloid);
	if (minirt->scene.nb_light)
		free(minirt->scene.light);
}

bool	check_arg(t_minirt *minirt, int argc, char *argv[])
{
	minirt->scene.bonus = 0;
	minirt->scene.random = 0;
	if (argc == 2)
		return (true);
	else if (argc > 4 || argc == 1)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (false);
	}
	if (argc == 3 && (argv[2][0] == '0' || argv[2][0] == '1')
			&& argv[2][1] == 0)
		minirt->scene.random = argv[2][0] - '0';
	else if (argc == 4 && (argv[3][0] == '0' || argv[3][0] == '1')
			&& argv[3][1] == 0
			&& (argv[2][0] == '0' || argv[2][0] == '1') && argv[2][1] == 0)
	{
		minirt->scene.random = argv[2][0] - '0';
		minirt->scene.bonus = argv[3][0] - '0';
	}
	else
	{
		ft_putstr_fd("Error\nWrong argument\n", 2);
		return (false);
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	t_minirt	minirt;
	int			fd;

	if (check_arg(&minirt, argc, argv) && !check_file(argv[1]))
		fd = open(argv[1], O_RDONLY);
	else
		exit (0);
	get_input_list(&minirt, fd);
	validate_input(&minirt);
	if (minirt.input_validity != 1 || init_minirt(&minirt) == false)
		exit (false);
	get_scene(&minirt);
	mlx_resize_hook(minirt.mlx, &resize, &minirt);
	mlx_loop_hook(minirt.mlx, &hook, &minirt);
	mlx_cursor_hook(minirt.mlx, &cursor, &minirt);
	mlx_key_hook(minirt.mlx, &keyhook, &minirt);
	mlx_mouse_hook(minirt.mlx, &mousehook, &minirt);
	mlx_loop(minirt.mlx);
	mlx_delete_image(minirt.mlx, minirt.img);
	mlx_terminate(minirt.mlx);
	free_scene(&minirt);
	exit (true);
}


/*
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

	scene.nb_sphere = 0;
	scene.nb_plane = 0;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	scene.nb_cone = 0;
	scene.nb_circle = 0;
	scene.nb_hyperboloid = 0;
	scene.nb_light = 0;

	scene.sphere = malloc(sizeof(t_sphere) * 20);
	scene.plane = malloc(sizeof(t_plane) * 20);
	scene.triangle = malloc(sizeof(t_triangle) * 20);
	scene.cylinder = malloc(sizeof(t_cylinder) * 20);
	scene.cone = malloc(sizeof(t_cone) * 20);
	scene.circle = malloc(sizeof(t_circle) * 20);
	scene.hyperboloid = malloc(sizeof(t_hyperboloid) * 20);
	scene.light = malloc(sizeof(t_light) * 20);



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

	t_triangle	triangle;
	triangle.p[0] = vector3(-3, 4.9f, 0);
	triangle.p[1] = vector3(3, 4.9f, 0);
	triangle.p[2] = vector3(0, 4.9f, 1);
	triangle.material = light;
	triangle.material.emission_strength = 10.0f;
	triangle.material.emission_color = vector3(1.0f, 1.0f, 1.0f);
	triangle.material.emission = vector3_multiply_float(\
	triangle.material.emission_color, triangle.material.emission_strength);
	scene.triangle[0] = triangle;

	t_sphere	sphere;
	sphere.center = vector3(0, 0, 0.0f);
	sphere.radius = 1.0f;
	sphere.material = red;
	sphere.material.specular_probability = 0.0f;
	sphere.material.smoothness = 1.0f;
	sphere.material.specular_color = vector3(1.0f, 1.0f, 1.0f);
	scene.sphere[0] = sphere;

	t_plane	plane;
	plane.point_on_plane = vector3(0.0f, 1.0f, 0.0f);
	plane.normal = vector3(0.0f, 1.0f, 0.0f);
	plane.normal = vector3_normalize(plane.normal);
	plane.material = white;
	plane.material.specular_color = vector3(0.3f, 0.6f, 0.2f);
	plane.material.flag = CHECKER_PATTERN;
	scene.plane[0] = plane;

	t_plane	plane2;
	plane2.point_on_plane = vector3(0.0f, 5.0f, 0.0f);
	plane2.normal = vector3(0.0f, -1.0f, 0.0f);
	plane2.normal = vector3_normalize(plane2.normal);
	plane2.material = light;
	scene.plane[1] = plane2;

	t_plane	plane3;
	plane3.point_on_plane = vector3(0.0f, 0.0f, -5.0f);
	plane3.normal = vector3(0.0f, 0.0f, 1.0f);
	plane3.normal = vector3_normalize(plane3.normal);
	plane3.material = purple;
	scene.plane[2] = plane3;

	t_plane	plane4;
	plane4.point_on_plane = vector3(0.0f, 0.0f, 5.0f);
	plane4.normal = vector3(0.0f, 0.0f, -1.0f);
	plane4.normal = vector3_normalize(plane4.normal);
	plane4.material = white;
	scene.plane[3] = plane4;

	t_plane	plane5;
	plane5.point_on_plane = vector3(-5.0f, 0.0f, 0.0f);
	plane5.normal = vector3(1.0f, 0.0f, 0.0f);
	plane5.normal = vector3_normalize(plane5.normal);
	plane5.material = white;
	scene.plane[4] = plane5;

	t_plane	plane6;
	plane6.point_on_plane = vector3(5.0f, 0.0f, 0.0f);
	plane6.normal = vector3(-1.0f, 0.0f, 0.0f);
	plane6.normal = vector3_normalize(plane6.normal);
	plane6.material = white;
	scene.plane[5] = plane6;

	float	light_strength = 0.8f;

	t_light	led;
	led.position = vector3(5, 3, 0);
	led.color = vector3(1.0f, 0.0f, 1.0f);
	led.brightness = light_strength;
	scene.light[0] = led;

	t_light	led2;
	led2.position = vector3(0, 4.5f, 0);
	led2.color = vector3(1.0f, 1.0f, 1.0f);
	led2.brightness = light_strength;
	scene.light[1] = led2;

	t_light	led3;
	led3.position = vector3(3, 2, 0);
	led3.color = vector3(0.0f, 0.0f, 1.0f);
	led3.brightness = light_strength;
	scene.light[2] = led3;

	t_light	led4;
	led4.position = vector3(-3, 2, 0);
	led4.color = vector3(1.0f, 0.0f, 1.0f);
	led4.brightness = light_strength;
	scene.light[3] = led4;

	t_light	led5;
	led5.position = vector3(0, 2, 3);
	led5.color = vector3(1.0f, 1.0f, 0.0f);
	led5.brightness = light_strength;
	scene.light[4] = led5;

	t_cylinder	cylinder;
	cylinder.center = vector3(0.0f, 0.0f, 0.0f);
	cylinder.radius = 1.0f;
	cylinder.height = 2.0f;
	cylinder.normal = vector3(0.0f, 1.0f, 0.0f);
	cylinder.normal = vector3_normalize(cylinder.normal);
	cylinder.material = yellow;
	cylinder.circle_bottom = get_circle_from_cylinder(cylinder, 0);
	cylinder.circle_top = get_circle_from_cylinder(cylinder, 1);
	scene.cylinder[0] = cylinder;

	t_cylinder	cylinder2;
	cylinder2.center = vector3(0.0f, 0.5f, 0.0f);
	cylinder2.radius = 1.0f;
	cylinder2.height = 2.0f;
	cylinder2.normal = vector3(0.0f, 0.0f, 1.0f);
	cylinder2.normal = vector3_normalize(cylinder2.normal);
	cylinder2.material = blue;
	cylinder2.circle_bottom = get_circle_from_cylinder(cylinder2, 0);
	cylinder2.circle_top = get_circle_from_cylinder(cylinder2, 1);
	scene.cylinder[1] = cylinder2;

	scene.nb_sphere = 0;
	scene.nb_plane = 0;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	scene.nb_circle = 0;
	scene.nb_cone = 0;
	scene.nb_hyperboloid = 0;
	scene.nb_paraboloid = 0;
	scene.nb_obj = 0;
	scene.nb_ambient = 0;
	scene.nb_light = 0;
	scene.nb_camera = 0;

	scene.nb_plane = 1;
	scene.nb_sphere = 1;
	scene.nb_light = 1;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	return (scene);
}
*/

/*t_scene	create_scene2(void)
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


	scene.camera.fov = 90.0f;
	scene.camera.pos = vector3(0.0f, 1.0f, 2.5f);
	scene.camera.pitch = 0.0f;
	scene.camera.yaw = 0.0f;
	scene.camera.inv_lookat = mult_mat4x4(rotation_y(to_radian(scene.camera.pitch)),
			rotation_x(to_radian(scene.camera.yaw)));
	scene.camera.is_clicked = false;

	float emission_strength = 0.0f;

	scene.nb_sphere = 0;
	scene.nb_plane = 0;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	scene.nb_cone = 0;
	scene.nb_circle = 0;
	scene.nb_hyperboloid = 0;
	scene.nb_light = 0;

	scene.sphere = malloc(sizeof(t_sphere) * 10);
	scene.plane = malloc(sizeof(t_plane) * 10);
	scene.triangle = malloc(sizeof(t_triangle) * 10);
	scene.cylinder = malloc(sizeof(t_cylinder) * 10);
	scene.cone = malloc(sizeof(t_cone) * 10);
	scene.circle = malloc(sizeof(t_circle) * 10);
	scene.hyperboloid = malloc(sizeof(t_hyperboloid) * 10);
	scene.light = malloc(sizeof(t_light) * 10);



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

	t_sphere	sphere;
	sphere.center = vector3(-1.0f, 1.5f, 0.0f);
	sphere.radius = 1.0f;
	sphere.material = white;
	sphere.material.specular_probability = 0.0f;
	sphere.material.smoothness = 1.0f;
	sphere.material.specular_color = vector3(1.0f, 1.0f, 1.0f);
	scene.sphere[0] = sphere;

	t_plane	plane;
	plane.point_on_plane = vector3(0.0f, 0.0f, 0.0f);
	plane.normal = vector3(0.0f, 1.0f, 0.0f);
	plane.normal = vector3_normalize(plane.normal);
	plane.material = white;
	plane.material.specular_color = vector3(0.3f, 0.6f, 0.2f);
	plane.material.flag = CHECKER_PATTERN;
	scene.plane[0] = plane;

	float	light_strength = 0.8f;

	t_light	led;
	led.position = vector3(3, 1.9f, 0);
	led.color = vector3(1.0f, 1.0f, 1.0f);
	led.brightness = light_strength;
	scene.light[0] = led;

	scene.nb_sphere = 0;
	scene.nb_plane = 0;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	scene.nb_circle = 0;
	scene.nb_cone = 0;
	scene.nb_hyperboloid = 0;
	scene.nb_paraboloid = 0;
	scene.nb_obj = 0;
	scene.nb_ambient = 0;
	scene.nb_light = 0;
	scene.nb_camera = 0;

	scene.nb_plane = 1;
	scene.nb_sphere = 1;
	scene.nb_light = 1;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
	scene.nb_camera = 1;
	return (scene);
}

*/

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

#define WIDTH 150
#define HEIGHT 150

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
	t_minirt	*minirt;

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
	t_input_list	*input;

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
			t_light	*cam = input->object;
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
			t_plane	*cam = input->object;
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
	material.specular_probability = 0.0f;
	material.flag = 0;
	return (material);
}

t_circle	get_circle_from_cylinder(t_cylinder cylinder, bool is_top)
{
	t_circle	circle;
	static int	i;

	circle.radius = cylinder.radius;
	circle.material = cylinder.material;
	if (is_top)
	{
		circle.center = vector3_add(cylinder.center, \
			vector3_multiply_float(cylinder.normal, cylinder.height));
		circle.normal = cylinder.normal;
	}
	else
	{
		circle.center = vector3_subtract(cylinder.center, \
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
	sphere.center = vector3(-1.0f, 1.5f, 0.0f);
	sphere.radius = 1.0f;
	sphere.material = white;
	sphere.material.specular_probability = 0.0f;
	sphere.material.smoothness = 1.0f;
	sphere.material.specular_color = vector3(1.0f, 1.0f, 1.0f);
	scene.sphere[0] = sphere;

	t_sphere	sphere2;
	sphere2.center = vector3(1.0f, 1.5f, 0.0f);
	sphere2.radius = 1.0f;
	sphere2.material = blue;
	sphere2.material.smoothness = 0.9f;
	sphere2.material.specular_probability = 0.0f;
	sphere2.material.specular_color = vector3(0.0f, 0.0f, 1.0f);
	scene.sphere[1] = sphere2;

	t_sphere	sphere3;
	sphere3.center = vector3(0.0f, 3.3f, 0.0f);
	sphere3.radius = 1.0f;
	sphere3.material = white;
	sphere3.material.color = vector3(0.3f, 0.6f, 0.2f);
	sphere3.material.specular_probability = 0.0f;
	sphere3.material.specular_color = vector3(0.3f, 0.9f, 0.5f);
	sphere3.material.flag = CHECKER_PATTERN;
	scene.sphere[2] = sphere3;

	t_plane	plane;
	plane.point_on_plane = vector3(0.0f, 0.0f, 0.0f);
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
	led.position = vector3(3, 1.9f, 0);
	led.color = vector3(1.0f, 1.0f, 1.0f);
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
	cylinder.center = vector3(0.0f, 0.5f, 0.0f);
	cylinder.radius = 1.0f;
	cylinder.height = 2.0f;
	cylinder.normal = vector3(0.0f, 0.0f, 1.0f);
	cylinder.normal = vector3_normalize(cylinder.normal);
	cylinder.material = blue;
	cylinder.circle_bottom = get_circle_from_cylinder(cylinder, 0);
	cylinder.circle_top = get_circle_from_cylinder(cylinder, 1);
	scene.cylinder[1] = cylinder;

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
	scene.nb_sphere = 2;
	scene.nb_light = 1;
	scene.nb_triangle = 0;
	scene.nb_cylinder = 0;
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

	float	emission_strength = 0.0f;

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

	t_triangle	triangle;
	triangle.p[0] = vector3(-1, 4, 0);
	triangle.p[1] = vector3(1, 4, 0);
	triangle.p[2] = vector3(0, 4, 1);
	triangle.material = light;
	scene.triangle[0] = triangle;

	t_sphere	sphere;
	sphere.center = vector3(-1.0f, 1.5f, 0.0f);
	sphere.radius = 1.0f;
	sphere.material = blue;
	sphere.material.specular_probability = 1.0f;
	scene.sphere[0] = sphere;

	t_sphere	sphere2;
	sphere2.center = vector3(1.0f, 1.5f, 0.0f);
	sphere2.radius = 1.0f;
	sphere2.material = white;
	sphere2.material.specular_probability = 1.0f;
	scene.sphere[1] = sphere2;

	/*t_sphere	sphere3;
	sphere3.center = vector3(1.0f, 1.5f, 0.0f);
	sphere3.radius = 1.0f;
	sphere3.material = white;
	sphere3.material.specular_probability = 1.0f;
	scene.sphere[0] = sphere3;*/

	t_plane	plane;
	plane.point_on_plane = vector3(0.0f, 0.0f, 0.0f);
	plane.normal = vector3(0.0f, 1.0f, 0.0f);
	plane.normal = vector3_normalize(plane.normal);
	plane.material = red;
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
	plane3.material = white;
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
	plane5.material = red;
	scene.plane[4] = plane5;

	t_plane	plane6;
	plane6.point_on_plane = vector3(5.0f, 0.0f, 0.0f);
	plane6.normal = vector3(-1.0f, 0.0f, 0.0f);
	plane6.normal = vector3_normalize(plane6.normal);
	plane6.material = green;
	scene.plane[5] = plane6;

	float light_strength = 5.0f;

	t_light	led;
	led.position = vector3(0, 3, 0);
	led.color = vector3(1.0f, 1.0f, 1.0f);
	led.brightness = light_strength;
	scene.light[0] = led;

	t_light	led2;
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

static bool	init_minirt(t_minirt *minirt)
{
	int	i;
	int	j;

	minirt->width = WIDTH;
	minirt->height = HEIGHT;

	minirt->error = 1;

	minirt->camera.fov = 90.0f;
	minirt->camera.pos = vector3(0.0f, 1.0f, 2.5f);

	minirt->mlx = mlx_init(minirt->width, minirt->height, "minirt", true);
	if (!minirt->mlx)
		return (false);
	minirt->img = mlx_new_image(minirt->mlx, minirt->width, minirt->height);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
	minirt->camera.pitch = 0.0f;
	minirt->camera.yaw = 0.0f;

	minirt->camera.inv_lookat = mult_mat4x4(rotation_y(to_radian(minirt->camera.pitch)), \
		rotation_x(to_radian(minirt->camera.yaw)));

	minirt->moved = true;
	minirt->camera.is_clicked = false;
	minirt->stop = false;
	minirt->x = 0;
	minirt->y = 1;
	minirt->z = 0;
	return (true);
}

void	get_camera(t_minirt *minirt, t_camera camera)
{
	t_matrix4x4	rotation;

	minirt->camera.fov = camera.fov;
	minirt->camera.pos = camera.position;
	minirt->camera.angle = camera.orientation;
	minirt->camera.angle.y *= 90;
	minirt->camera.angle.x *= 180;
	minirt->camera.angle.z *= 180;
	minirt->camera.pitch = minirt->camera.angle.y;
	minirt->camera.yaw = minirt->camera.angle.x;
	minirt->camera.is_clicked = false;
	minirt->scene.nb_camera++;
	rotation = mult_mat4x4(rotation_y(to_radian(minirt->camera.pitch)),
			rotation_x(to_radian(minirt->camera.yaw)));
	rotation = mult_mat4x4(rotation,
			rotation_z(to_radian(minirt->camera.angle.z)));
	minirt->camera.inv_lookat = rotation;
	minirt->scene.camera = minirt->camera;
}

void	get_ambient(t_minirt *minirt, t_ambient ambient)
{
	t_vector3	tmp;

	minirt->scene.ambient = ambient;
	ambient.color = vector3_multiply_float(ambient.color, 1 / 255.0f);
	tmp = vector3_multiply_float(ambient.color, ambient.intensity);
	minirt->scene.ambient.ambient = tmp;
}

void	get_light(t_minirt *minirt, t_light light)
{
	int	i;

	if (minirt->scene.nb_light == 0)
		minirt->scene.light = malloc(sizeof(t_light));
	else
		minirt->scene.light = ft_realloc(minirt->scene.light, sizeof(t_light) * (minirt->scene.nb_light + 1));
	if (!minirt->scene.light)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_light++;
	minirt->scene.light[i] = light;
	minirt->scene.light[i].color = vector3_multiply_float(light.color, 1 / 255.0f);
}

void	get_sphere(t_minirt *minirt, t_sphere sphere)
{
	int	i;

	if (minirt->scene.nb_sphere == 0)
		minirt->scene.sphere = malloc(sizeof(t_sphere));
	else
		minirt->scene.sphere = ft_realloc(minirt->scene.sphere, sizeof(t_sphere) * (minirt->scene.nb_sphere + 1));
	if (!minirt->scene.sphere)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_sphere++;
	minirt->scene.sphere[i] = sphere;
	minirt->scene.sphere[i].material = return_material();
	minirt->scene.sphere[i].material.color = vector3_multiply_float(minirt->scene.sphere[i].material.color, 1 / 255.0f);
}

void	get_cylinder(t_minirt *minirt, t_cylinder cylinder)
{
	int	i;

	if (minirt->scene.nb_cylinder == 0)
		minirt->scene.cylinder = malloc(sizeof(t_cylinder));
	else
		minirt->scene.cylinder = ft_realloc(minirt->scene.cylinder, sizeof(t_cylinder) * (minirt->scene.nb_cylinder + 1));
	if (!minirt->scene.cylinder)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_cylinder++;
	minirt->scene.cylinder[i] = cylinder;
	minirt->scene.cylinder[i].material = return_material();
	minirt->scene.cylinder[i].material.color = vector3_multiply_float(
			cylinder.color, 1 / 255.0f);
	minirt->scene.nb_cylinder++;
}


void	get_plane(t_minirt *minirt, t_plane plane)
{
	int	i;

	if (minirt->scene.nb_plane == 0)
		minirt->scene.plane = malloc(sizeof(t_plane));
	else
		minirt->scene.plane = ft_realloc(minirt->scene.plane, sizeof(t_plane) * (minirt->scene.nb_plane + 1));
	if (!minirt->scene.plane)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		minirt->error = 1;
		return ;
	}
	i = minirt->scene.nb_plane++;
	minirt->scene.plane[i] = plane;
	minirt->scene.plane[i].material = return_material();
	minirt->scene.plane[i].material.color = vector3_multiply_float(
			plane.color, 1 / 255.0f);
}


static bool	get_scene(t_minirt *minirt)
{
	int	i;
	int	j;

	minirt->scene.nb_sphere = 0;
	minirt->scene.nb_plane = 0;
	minirt->scene.nb_triangle = 0;
	minirt->scene.nb_cylinder = 0;
	minirt->scene.nb_cone = 0;
	minirt->scene.nb_circle = 0;
	minirt->scene.nb_hyperboloid = 0;
	minirt->scene.nb_light = 0;
	minirt->scene.nb_camera = 0;
	minirt->scene.nb_ambient = 0;

	while (minirt->input_head)
	{
		printf("name:%s\n", minirt->input_head->name);
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

		/*
		else if (ft_strncmp("Triangle", minirt->input_head->name, 8) == 0)
			get_triangle(minirt, *(t_triangle *)minirt->input_head->object);
		else if (ft_strncmp("Circle", minirt->input_head->name, 6) == 0)
			get_circle(minirt, *(t_circle *)minirt->input_head->object);
		else if (ft_strncmp("Cone", minirt->input_head->name, 4) == 0)
			get_cone(minirt, *(t_cone *)minirt->input_head->object);
		else if (ft_strncmp("Hyperboloid", minirt->input_head->name, 11) == 0)
			get_hyperboloid(minirt, *(t_hyperboloid *)minirt->input_head->object);
		else if (ft_strncmp("Paraboloid", minirt->input_head->name, 10) == 0)
			get_paraboloid(minirt, *(t_paraboloid *)minirt->input_head->object);
		*/
		else
			return (false);
		
		minirt->input_head = minirt->input_head->next;
	}
	return (true);
}

void	print_scene(t_scene scene)
{
	int	i;

	i = -1;
	printf("scene\n");
	printf("nb_sphere %d\n", scene.nb_sphere);
	printf("nb_plane %d\n", scene.nb_plane);
	printf("nb_cylinder %d\n", scene.nb_cylinder);
	printf("nb_light %d\n", scene.nb_light);
	printf("nb_camera %d\n", scene.nb_camera);
	printf("nb_ambient %d\n\n", scene.nb_ambient);


	while (++i < scene.nb_cylinder)
	{
		printf("cylinder %d\n", i);
		printf("color %f %f %f\n", scene.cylinder[i].material.color.x, scene.cylinder[i].material.color.y, scene.cylinder[i].material.color.z);
		printf("position %f %f %f\n", scene.cylinder[i].center.x, scene.cylinder[i].center.y, scene.cylinder[i].center.z);
		printf("normal %f %f %f\n", scene.cylinder[i].normal.x, scene.cylinder[i].normal.y, scene.cylinder[i].normal.z);
		printf("diameter %f\n", scene.cylinder[i].radius);
		printf("height %f\n\n", scene.cylinder[i].height);
	}
	i = -1;
	while (++i < scene.nb_sphere)
	{
		printf("\nsphere %d\n", i);
		printf("color %f %f %f\n", scene.sphere[i].material.color.x, scene.sphere[i].material.color.y, scene.sphere[i].material.color.z);
		printf("position %f %f %f\n", scene.sphere[i].center.x, scene.sphere[i].center.y, scene.sphere[i].center.z);
		printf("diameter %f\n\n", scene.sphere[i].radius);
	}
	
	i = -1;
	while (++i < scene.nb_plane)
	{
		printf("\nplane %d\n", i);
		printf("color %f %f %f\n", scene.plane[i].material.color.x, scene.plane[i].material.color.y, scene.plane[i].material.color.z);
		printf("position %f %f %f\n", scene.plane[i].point_on_plane.x, scene.plane[i].point_on_plane.y, scene.plane[i].point_on_plane.z);
		printf("normal %f %f %f\n\n", scene.plane[i].normal.x, scene.plane[i].normal.y, scene.plane[i].normal.z);
	}
	i = -1;
	while (++i < scene.nb_light)
	{
		printf("\nlight %d\n", i);
		printf("color %f %f %f\n", scene.light[i].color.x, scene.light[i].color.y, scene.light[i].color.z);
		printf("position %f %f %f\n", scene.light[i].position.x, scene.light[i].position.y, scene.light[i].position.z);
		printf("brightness %f\n\n", scene.light[i].brightness);
	}
	printf("\ncamera %d\n", i);
	printf("position %f %f %f\n", scene.camera.pos.x, scene.camera.pos.y, scene.camera.pos.z);
	printf("normal %f %f %f\n", scene.camera.angle.x, scene.camera.angle.y, scene.camera.angle.z);
	printf("fov %f\n\n", scene.camera.fov);

	i = -1;
	while (++i < scene.nb_ambient)
	{
		printf("\nambient %d\n", i);
		printf("color %f %f %f\n", scene.ambient.color.x, scene.ambient.color.y, scene.ambient.color.z);
		printf("brightness %f\n", scene.ambient.intensity);
	}
}

int	main(int argc, char *argv[])
{
	t_minirt	minirt;
	int			fd;

	if (argc == 2 && !check_file(argv[1]))
		fd = open(argv[1], O_RDONLY);
	else
		return (0);
	get_input_list(&minirt, fd);
	validate_input(&minirt);
	print_input(&minirt);

	if (get_scene(&minirt) == false)
		printf("error\n");
	print_scene(minirt.scene);
	return (0);
	// get_input(&minirt.scene, argc, argv);
	// print_scene(minirt.scene);
	// return (0);
	// if (init_minirt(&minirt) && get_input(&minirt.scene, argc, argv))
		// return (false);

	// get_scene(&minirt);
	minirt.scene = create_scene();

	mlx_resize_hook(minirt.mlx, &resize, &minirt);
	mlx_loop_hook(minirt.mlx, &hook, &minirt);
	mlx_cursor_hook(minirt.mlx, &cursor, &minirt);
	mlx_key_hook(minirt.mlx, &keyhook, &minirt);
	mlx_mouse_hook(minirt.mlx, &mousehook, &minirt);
	mlx_loop(minirt.mlx);
	mlx_delete_image(minirt.mlx, minirt.img);
	mlx_terminate(minirt.mlx);
	// system("leaks minirt");
	return (true);
}

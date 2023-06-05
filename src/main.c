/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:16:05 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/05 20:58:13 by lkukhale         ###   ########.fr       */
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
	minirt->camera.pos = vector3(0.0f, 0.0f, 1.0f);
	minirt->camera.forward = vector3(0.0f, 0.0f, 1.0f);

	// Init mlx with a canvas size of 256x256 and the ability to resize the window.
	minirt->mlx = mlx_init(minirt->width ,minirt->height, "minirt", true);
	if (!minirt->mlx)
		exit(ERROR);
	minirt->camera.ray_dir = malloc(sizeof(t_vector3) * minirt->width * minirt->height);
	if (!minirt->camera.ray_dir)
		exit(ERROR);
	minirt->img = mlx_new_image(minirt->mlx, minirt->width, minirt->height);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
	calculateprojection(minirt);
	// Run the main loop and terminate on quit.
	minirt->moved = true;
	return (SUCCESS);
}

int	get_rgba(t_vector4 color)
{
	color.x = color.x * 255.0f;
	color.y = color.y * 255.0f;
	color.z = color.z * 255.0f;
	color.w = color.w * 255.0f;
	return ((int) color.x << 24 | (int) color.y << 16 | (int) color.z << 8 |(int)  color.w);
}

void	resize(int32_t width, int32_t height, void *param)
{
	t_minirt *minirt;

	minirt = (t_minirt *)param;
	mlx_delete_image( minirt->mlx,  minirt->img);
	 minirt->img = mlx_new_image( minirt->mlx, width, height);
	if (!minirt->img)
		exit(EXIT_FAILURE);
	minirt->width = width;
	minirt->height = height;
	free(minirt->camera.ray_dir);
	minirt->camera.ray_dir = malloc(sizeof(t_vector3) * minirt->width * minirt->height);
	if (!minirt->camera.ray_dir)
	{
		minirt->error = ERROR;
		minirt->camera.ray_dir = NULL;
		exit(ERROR);
	}
	//calculateprojection(minirt);
	//calculateraydirections(minirt);
	minirt->moved = true;
	mlx_image_to_window( minirt->mlx,  minirt->img, 0, 0);
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
t_vector4 renderer(t_vector2 coord, t_minirt *minirt)
{
	t_vector4 color;
	t_ray ray;


	ray.origin = minirt->camera.pos;
	ray.origin = minirt->camera.pos;

	ray.direction = multiplymatrixvector(vector3(coord.x, coord.y, 1), minirt->camera.inv_lookat);
	ray.direction = vector3_normalize(vector3(coord.x, coord.y, 1));

	t_sphere sphere;
	sphere.center = vector3(0.0f, 0.0f, 10.0f);
	sphere.radius = 0.5f;
	t_vector3 oc = vector3_subtract(ray.origin, sphere.center);

	float a = dot_product(ray.direction, ray.direction);
	float b = 2.0f * dot_product(oc, ray.direction);
	float c = dot_product(oc, oc) - sphere.radius * sphere.radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (vector4(0.0f, 0.0f, 0.0f, 1.0f));
	float t = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (t < 0)
		t = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (t < 0)
		return (vector4(0.0f, 0.0f, 0.0f, 1.0f));
	t_vector3 hit_point = vector3_add(ray.origin, vector3_multiply_float(ray.direction, t));
	t_vector3 normal = vector3_normalize(vector3_subtract(hit_point, sphere.center));
	color = vector4(normal.x, normal.y, normal.z, 1.0f);


	return (color);
}

void print_fps(t_minirt *minirt)
{
	static int frames;
	static int last_time;
	int current_time = time(NULL);
	char *str;
	frames++;
	if (current_time - last_time >= 1)
	{
		str = ft_itoa(frames);
		printf("FPS: %s\n", str);
		free(str);

		frames = 0;
		last_time = current_time;
	}
}

void hook(void *param)
{
	t_minirt *minirt = (t_minirt *)param;
	t_ray ray;
	int x;
	int y;

	if (minirt->moved != true)
		return ;
	minirt->moved = false;

	calculateprojection(minirt);
	calculatelookat(minirt);
	minirt->camera.inv_lookat = mult_mat4x4(minirt->camera.inv_perspective, minirt->camera.inv_lookat);
	x = -1;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			t_vector3 coord = vector3((float)x / (float)minirt->width, (float)(y) / (float)minirt->height,0);
			coord = vector3(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f,0);
			//coord = multiplymatrixvector(vector3(coord.x, coord.y, 1), minirt->camera.inv_perspective);
			coord = multiplymatrixvector(vector3(coord.x, coord.y, 1), minirt->camera.inv_lookat);
			mlx_put_pixel(minirt->img,minirt->width - x - 1, minirt->height - y - 1, get_rgba(renderer(vector2(coord.x, coord.y), minirt)));
		}
	}
	print_fps(minirt);


}

/*void	hook(void *param)
{
	t_minirt *minirt;
	int x;
	int y;
	t_vector2 coord;
	t_vector4 color;

	if (minirt->moved == false)
		return ;
	minirt = (t_minirt *)param;
	x = -1;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			coord = vector2((float) x / (float) minirt->width, (float) (minirt->height - y) / (float) minirt->height);
			coord = vector2(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f);
			ray.direction
			color = clamp(renderer(0, minirt), 0.0f, 255.0f);
			mlx_put_pixel(minirt->img, x, y, get_rgba(color));
		}
	}
}*/

void	cursor(double xpos, double ypos, void *param)
{
	t_minirt *minirt;
	minirt = (t_minirt *)param;
	// static double lastx;
	// static double lasty;

	// if (lastx == 0 && lasty == 0)
	// {
		// lastx = xpos;
		// lasty = ypos;
	// }
	// if (xpos > lastx)
		// minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_y(to_radian(0.1)));
	// else
		// minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_y(to_radian(-0.1)));
	// if (ypos < lasty)
		// minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_x(to_radian(0.1)));
	// else
		// minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_x(to_radian(-0.1)));
	// lastx = xpos;
	// lasty = ypos;
	xpos = (xpos / minirt->width) * 2.0f - 1.0f;
	ypos = (ypos / minirt->height) * 2.0f - 1.0f;

	minirt->camera.forward = vector3(-xpos / 2, ypos / 2, 1.0f);
	minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_y(to_radian(6.0f * xpos)));
	minirt->camera.forward = vector3_normalize(minirt->camera.forward);
	minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_x(to_radian(6.0f * ypos)));
	minirt->camera.forward = vector3_normalize(minirt->camera.forward);

	minirt->moved = true;
}

int main(int argc, char *argv[])
{
	t_minirt minirt;
	int	fd;

	if (argc == 2  && !check_file(argv[1]))
		fd = open(argv[1], O_RDONLY);
	else
		return (0);
	if (init_minirt(&minirt) == ERROR)
		return (ERROR);
	get_input_list(&minirt, fd);
	validate_input(&minirt);
	mlx_resize_hook(minirt.mlx, &resize, &minirt);
	mlx_loop_hook(minirt.mlx, &hook, &minirt);
	mlx_cursor_hook(minirt.mlx, &cursor, &minirt);
	mlx_key_hook(minirt.mlx, &keyhook, &minirt);

	if (minirt.error != ERROR)
		mlx_loop(minirt.mlx);
	mlx_terminate(minirt.mlx);
	if (minirt.camera.ray_dir)
		free(minirt.camera.ray_dir);
	system("leaks minirt");
	close(fd);
	return (SUCCESS);
}


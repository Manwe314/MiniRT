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


t_vec4	clamp(t_vec4 color, float min, float max)
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
	minirt->camera.pos = vec3(0.0f, 0.0f, -0.8f);
	minirt->camera.forward = vec3(0.0f, 0.0f, 1.0f);

	// Init mlx with a canvas size of 256x256 and the ability to resize the window.
	minirt->mlx = mlx_init(minirt->width ,minirt->height, "minirt", true);
	if (!minirt->mlx)
		exit(ERROR);
	minirt->camera.ray_dir = malloc(sizeof(t_vec3) * minirt->width * minirt->height);
	if (!minirt->camera.ray_dir)
		exit(ERROR);
	minirt->img = mlx_new_image(minirt->mlx, minirt->width, minirt->height);
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
	calculateprojection(minirt);
	// Run the main loop and terminate on quit.
	minirt->moved = true;
	return (SUCCESS);
}

int	get_rgba(t_vec4 color)
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
	minirt->camera.ray_dir = malloc(sizeof(t_vec3) * minirt->width * minirt->height);
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

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

t_vec4 renderer(t_ray ray, t_minirt *minirt, int x, int y)
{
	float discriminant;
	float radius;
	// t_vec2 coord = vec2((float) x / (float) minirt->width, (float) (minirt->height - y) / (float) minirt->height);
	// coord = vec2(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f);
	// ray.origin = vec3(minirt->camera.pos.x, minirt->camera.pos.y, minirt->camera.pos.z - 2);
	// ray.direction = vec3(x, y, 1);

	radius = 0.5f;
	float a = dot_product(ray.direction, ray.direction);
	float b = 2.0f * dot_product(ray.origin, ray.direction);
	float c = dot_product(ray.origin, ray.origin) - radius * radius;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (vec4(0, 0, 0, 1));

	float t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	float closest = (-b + sqrtf(discriminant)) / (2.0f * a);
	t_vec3 hitpoint = vec3_add( vec3_multf(ray.direction, closest), ray.origin);
	hitpoint = vec3_normalize(hitpoint);
	hitpoint = vec3_addf( vec3_multf(hitpoint, 0.5f), 0.5f);

	t_vec3 light_dir = vec3_normalize(vec3(-1.0f, -1.0f, 1.0f));
	float d = max(0.0f, dot_product(hitpoint, vec3_multf(light_dir, -1.0f)));
	t_vec4 sphere_color = vec4(d,0,d, 1.0f);
	//sphere_color = vec4_multf(sphere_color, d);

	return (sphere_color);
}

void hook(void *param)
{
	t_minirt *minirt = (t_minirt *)param;
	t_ray ray;

	if (minirt->moved == false)
		return ;
	calculateraydirections(minirt);
	calculateview(minirt);
	ray.origin = minirt->camera.pos;
	// printf("forward: %2f %2f %2f\n", minirt->camera.forward.x, minirt->camera.forward.y, minirt->camera.forward.z);
	printf("pos: %2f %2f %2f\n", minirt->camera.pos.x, minirt->camera.pos.y, minirt->camera.pos.z);
	minirt->moved = false;
	int x = -1;
	while (++x < minirt->width)
	{
		int y = minirt->height;
		while (--y > 0)
		{
			ray.direction = minirt->camera.ray_dir[x + y * minirt->width];
			t_vec4 color = clamp(renderer(ray, minirt, x, y), 0.0f, 255.0f);
			mlx_put_pixel(minirt->img, x, minirt->height - y, get_rgba(color));
		}
	}
}

/*void	hook(void *param)
{
	t_minirt *minirt;
	int x;
	int y;
	t_vec2 coord;
	t_vec4 color;

	if (minirt->moved == false)
		return ;
	minirt = (t_minirt *)param;
	x = -1;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			coord = vec2((float) x / (float) minirt->width, (float) (minirt->height - y) / (float) minirt->height);
			coord = vec2(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f);
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
//
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

	minirt->camera.forward = vec3(-xpos / 2, -ypos / 2, 1.0f);
	minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_y(to_radian(xpos)));
	minirt->camera.forward = vec3_normalize(minirt->camera.forward);
	minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_x(to_radian(ypos)));
	minirt->camera.forward = vec3_normalize(minirt->camera.forward);
	// calculateraydirections(minirt);
	// calculateview(minirt);
	minirt->moved = true;
}


int main()
{
	t_minirt minirt;

	if (init_minirt(&minirt) == ERROR)
		return (ERROR);

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
	return (SUCCESS);
}

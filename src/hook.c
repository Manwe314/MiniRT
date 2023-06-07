/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:38:47 by beaudibe          #+#    #+#             */
/*   Updated: 2023/05/06 14:38:47 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void keyhook(mlx_key_data_t keydata, void *param)
{
	t_minirt *minirt;

	minirt = (t_minirt *)param;
	float speed = 0.05f;
	t_vector3 updirection;
	t_vector3 rightdirection;

	// updirection = vector3(0.0f, 1.0f, 0.0f);
	// rightdirection = vector3_cross(minirt->camera.forward, vector3(0.0f, 1.0f, 0.0f));
	// if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = vector3_add(minirt->camera.pos, vector3_multiply_float(rightdirection, speed));
	// if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = vector3_subtract(minirt->camera.pos, vector3_multiply_float(rightdirection, speed));
	// if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = vector3_add(minirt->camera.pos, vector3_multiply_float(updirection, speed));
	// if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = vector3_subtract(minirt->camera.pos, vector3_multiply_float(updirection, speed));
	// if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = vector3_add(minirt->camera.pos, vector3_multiply_float(minirt->camera.forward, speed));
	// if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = vector3_subtract(minirt->camera.pos, vector3_multiply_float(minirt->camera.forward, speed));

	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		minirt->camera.pos.x += speed;
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		minirt->camera.pos.x -= speed;
	if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
		minirt->camera.pos.y += speed;
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action != MLX_RELEASE)
		minirt->camera.pos.y -= speed;
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		minirt->camera.pos.z -= speed;
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		minirt->camera.pos.z += speed;

	// if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos, translation(rightdirection));
	// if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)

	// if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos, translation(updirection));
	// if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action != MLX_RELEASE)

	// if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos, translation(minirt->camera.forward));
	// if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)

	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_A \
	|| keydata.key == MLX_KEY_SPACE || keydata.key == MLX_KEY_LEFT_CONTROL \
	|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
	{
		minirt->moved = true;
		// calculateraydirections(minirt);
		// calculateview(minirt);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_hook(minirt->mlx, &close_function, minirt);
		mlx_close_window(minirt->mlx);
	}

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
	t_scene scene;
	int x;
	int y;

	print_fps(minirt);
	if (minirt->moved != true)
		return ;
	minirt->moved = false;
	ray.origin = minirt->camera.pos;
	calculatelookat(minirt);
	calculateprojection(minirt);
	//minirt->model = get_model();
	minirt->camera.inv_lookat = mult_mat4x4(minirt->camera.inv_perspective, minirt->camera.inv_lookat);
	x = -1;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			t_vector3 coord = vector3((float)x / (float)minirt->width, (float)(y) / (float)minirt->height,0);
			coord = vector3(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f,0);
			// coord = multiplymatrixvector(vector3(coord.x, coord.y, 1), minirt->camera.inv_perspective);
			coord = multiplymatrixvector(vector3(coord.x, coord.y, -1), minirt->camera.inv_lookat);
			ray.direction = vector3(coord.x, coord.y, -1.0f);
			mlx_put_pixel(minirt->img,minirt->width - x - 1, minirt->height - y - 1, get_rgba(renderer(ray, minirt)));
		}
	}


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
	calculateprojection(minirt);
	minirt->moved = true;
	mlx_image_to_window( minirt->mlx,  minirt->img, 0, 0);
}

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
	//printf("forward = %f %f %f\n", minirt->camera.forward.x, minirt->camera.forward.y, minirt->camera.forward.z);
	minirt->camera.forward = vector3(-xpos / 2, ypos / 2, 1.0f);
	minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_y(to_radian(1.0f * xpos)));
	minirt->camera.forward = vector3_normalize(minirt->camera.forward);
	minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_x(to_radian(1.0f * ypos)));
	minirt->camera.forward = vector3_normalize(minirt->camera.forward);

	minirt->moved = true;
}

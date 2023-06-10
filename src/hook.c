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


void mousehook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_minirt *minirt;

	minirt = (t_minirt *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action != MLX_RELEASE)
		minirt->camera.is_clicked = true;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		minirt->camera.is_clicked = false;
}

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_minirt *minirt;

	minirt = (t_minirt *)param;
	float speed = 0.05f;
	t_vector3 updirection;
	t_vector3 rightdirection;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action != MLX_RELEASE)
	{
		mlx_close_hook(minirt->mlx, &close_function, minirt);
		mlx_close_window(minirt->mlx);
		minirt->error = ERROR;
	}
	updirection = vector3(0.0f, 1.0f, 0.0f);
	rightdirection = vector3_cross(minirt->camera.forward, vector3(0.0f, 1.0f, 0.0f));
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vector3_add(minirt->camera.pos, vector3_multiply_float(rightdirection, speed));
	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vector3_subtract(minirt->camera.pos, vector3_multiply_float(rightdirection, speed));
	if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vector3_add(minirt->camera.pos, vector3_multiply_float(updirection, speed));
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vector3_subtract(minirt->camera.pos, vector3_multiply_float(updirection, speed));
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vector3_add(minirt->camera.pos, vector3_multiply_float(minirt->camera.forward, speed));
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vector3_subtract(minirt->camera.pos, vector3_multiply_float(minirt->camera.forward, speed));


	// if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		// minirt->camera.pos.x += speed;
	// if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		// minirt->camera.pos.x -= speed;
	// if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
		// minirt->camera.pos.y += speed;
	// if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action != MLX_RELEASE)
		// minirt->camera.pos.y -= speed;
	// if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		// minirt->camera.pos.z -= speed;
	// if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		// minirt->camera.pos.z += speed;

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
		//calculateprojection(minirt);
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

t_vector4 **init_0(t_minirt *minirt)
{
	int x;
	int y;
	t_vector4 **color;

	color = malloc(sizeof(t_vector4 *) * minirt->width + 1);
	if (!color)
		return (NULL);
	x = -1;
	while (++x < minirt->width)
	{
		color[x] = malloc(sizeof(t_vector4) * minirt->height + 1);
		if (!color[x])
		{
			while (--x >= 0)
				free(color[x]);
			free(color);
			return (NULL);

		}
		y = -1;
		while (++y < minirt->height)
			color[x][y] = vector4(0, 0, 0, 0);
	}
	return (color);
}

t_vector4 **set_0(t_vector4 **color, t_minirt *minirt)
{
	int i;
	int j;

	i = -1;
	while (++i < minirt->width)
	{
		j = -1;
		while (++j < minirt->height)
			color[i][j] = vector4(0, 0, 0, 0);
	}
	return (color);
}

void free_color(t_vector4 **color, t_minirt *minirt)
{
	int i;

	i = -1;
	while (++i < minirt->width)
		free(color[i]);
	free(color);
}

void hook(void *param)
{
	t_minirt *minirt = (t_minirt *)param;
	t_ray ray;
	t_scene scene;
	int x;
	int y;
	static int i;
	static t_vector4 **color;


	print_fps(minirt);
	if (i == 0 || minirt->resized == true)
	{
		if (minirt->resized == true)
			free(color);
		minirt->resized = false;
		color = init_0(minirt);
		if (!color)
			exit(EXIT_FAILURE);
	}

	if (minirt->moved == true)
	{
		color = set_0(color, minirt);
		i = 0;
	}
	i++;

	minirt->moved = false;
	ray.origin = minirt->camera.pos;
	calculatelookat(minirt);
	calculateprojection(minirt);
	//minirt->model = get_model();
	//minirt->camera.inv_lookat = mult_mat4x4(minirt->camera.inv_perspective, minirt->camera.inv_lookat);
	x = -1;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			t_vector3 coord = vector3((float)x / (float)minirt->width, (float)(y) / (float)minirt->height,0);
			coord = vector3(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f,0);
			ray = create_ray(coord.x, coord.y, minirt);

			color[x][y] = vector4_add(color[x][y] , PerPixel(ray, minirt->scene));
			t_vector4 accumulated_color = vector4_multiply_float(color[x][y] , 1.0f / (float)i) ;
			accumulated_color = vector4_clamp(accumulated_color, 0.0f, 1.0f);
			mlx_put_pixel(minirt->img,minirt->width - x - 1, minirt->height - y - 1, get_rgba(accumulated_color));
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
	//calculateprojection(minirt);
	minirt->moved = true;
	minirt->resized = true;
	mlx_image_to_window( minirt->mlx,  minirt->img, 0, 0);
}

void	cursor(double xpos, double ypos, void *param)
{
	t_minirt *minirt;
	minirt = (t_minirt *)param;
	t_matrix4x4 mat[2];
	static int i, x, y;

	if (minirt->camera.is_clicked == false)
	{
		i = 0;

		return;
	}
	if (i == 0)
	{
		mlx_set_mouse_pos(minirt->mlx, minirt->width / 2, minirt->height / 2);
		i = 1;
		return;
	}
	xpos = (xpos / minirt->width) * 2.0f - 1.0f;
	ypos = (ypos / minirt->height) * 2.0f - 1.0f;
	if (xpos > 0)
	{
		minirt->camera.yaw += 0.1f;
	}
	else if (xpos < 0)
	{
		minirt->camera.yaw -= 0.1f;
	}
	if (ypos > 0)
	{
		minirt->camera.pitch += 0.1f;
	}
	else if (ypos < 0)
	{
		minirt->camera.pitch -= 0.1f;
	}
	xpos = asin(xpos);
	ypos = atan2(-ypos, 1.0f);
	xpos /= 20;
	ypos /= -20;
	mat[0] = rotation_y(xpos);
	mat[1] =  rotation_x(ypos);

	mat[0] = mult_mat4x4(mat[1], mat[0]);
	minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, mat[0]);
	minirt->camera.forward = vector3_normalize(minirt->camera.forward);
	//if (minirt->camera.forward.z < 0.0f)
	//	minirt->camera.forward.z = -minirt->camera.forward.z;
	//printf("forward = %f %f %f\n", minirt->camera.forward.x, minirt->camera.forward.y, minirt->camera.forward.z);

	// minirt->camera.forward = vector3(-xpos / 2, ypos / 2, 1.0f);
	// minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_y(to_radian(1.0f * xpos)));
	// minirt->camera.forward = vector3_normalize(minirt->camera.forward);
	// minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, rotation_x(to_radian(1.0f * ypos)));
	// minirt->camera.forward = vector3_normalize(minirt->camera.forward);
	mlx_set_mouse_pos(minirt->mlx, minirt->width / 2, minirt->height / 2);
	//calculatelookat(minirt);
	minirt->moved = true;
}
// 0 1 0 y bas
// 0 -1 0 y haut
// -1 0 0 x droite
// 1 0 0 x gauche

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:20:28 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:20:28 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	print_fps(t_minirt *minirt)
{
	static int	frames;
	static int	last_time;
	static int	i;
	int current_time = time(NULL);

	frames++;
	i++;

	if (current_time - last_time >= 1)
	{
		printf("FPS: %d   frames = %d\n", frames, i);
		frames = 0;
		last_time = current_time;
	}
}
// used struc timeval to print the time between each frame
void	print_time(t_minirt *minirt)
{
	static struct timeval last_time;
	struct timeval current_time;
	float time;
	static float moyenne;
	static int i;

	i++;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - last_time.tv_sec) * 1000.0f
		+ (current_time.tv_usec - last_time.tv_usec) / 1000.0f;
	if (time > 10.0f)
		last_time = current_time;
	moyenne += time;
	moyenne /= i;
	printf("time: %f\n", moyenne);
}

t_vector3	**init_0(t_minirt *minirt)
{
	int			x;
	int			y;
	t_vector3	**color;

	color = malloc(sizeof(t_vector3 *) * minirt->width + 1);
	if (!color)
		return (NULL);
	x = -1;
	while (++x < minirt->width)
	{
		color[x] = malloc(sizeof(t_vector3) * minirt->height + 1);
		if (!color[x])
		{
			while (--x >= 0)
				free(color[x]);
			free(color);
			return (NULL);
		}
		y = -1;
		while (++y < minirt->height)
			color[x][y] = vector3(0, 0, 0);
	}
	return (color);
}

t_vector3	**set_0(t_vector3 **color, t_minirt *minirt)
{
	int	i;
	int	j;

	i = -1;
	while (++i < minirt->width)
	{
		j = -1;
		while (++j < minirt->height)
			color[i][j] = vector3(0, 0, 0);
	}
	return (color);
}

t_vector3	blurred(t_vector3 **color, int x, int y, t_minirt *minirt)
{
	t_vector3	blurred_color;
	float		i;

	i = 0.0f;

	blurred_color = color[x][y];
	// if (x - 1 >= 0)
	// {
	// blurred_color = vector4_add(blurred_color, color[x - 1][y - 1]);
	// i++;
	// }
	// if (x + 1 < minirt->width)
	// {
	// blurred_color = vector4_add(blurred_color, color[x + 1][y - 1]);
	// i++;
	// }
	// if (y - 1 >= 0)
	// {
	// blurred_color = vector4_add(blurred_color, color[x][y - 1]);
	// i++;
	// }
	// if (y + 1 < minirt->height)
	// {
	// blurred_color = vector4_add(blurred_color, color[x][y + 1]);
	// i++;
	// }
	//
	// blurred_color = vector4_multiply_float(blurred_color, 1.0f / i);
	return (blurred_color);
}

/*t_vector4 saturate(t_vector4 color, int frame, int x, int y,
	t_minirt *minirt)
{
	static t_vector4 **previous;
	t_vector4 accumulatedcol;
	if (frame == 1)
	{
		previous = init_0(minirt);
		if (!previous)
			exit(EXIT_FAILURE);
	}

	float weight = 1.0 / (frame);
	// Combine prev frame with current frame. Weight the contributions to result in an average over all frames.
	accumulatedcol = vector4_clamp(vector4_add(vector4_multiply_float(previous[x][y],
				1 - weight), vector4_multiply_float(color, weight)), 0.0f,
		1.0f);
	previous[x][y] = accumulatedcol;
	return (accumulatedcol);
}*/

/*
((2.0f * x) / ((float)minirt->width) - 1.0f) * aspect_ratio
((2 * x - width) / width ) * aspect
2 * aspect * x / width  -   width * aspect / width
2 * aspect * x / width  -   aspect
*/
void hook(void *param)
{
	t_minirt			*minirt;
	t_ray				ray;
	t_scene				scene;
	int					x;
	int					y;
	static int			i;
	static t_vector3	color[10000][10000];
	t_vector3			accumulated_color;
	static float		x_aspect_ratio;
	static float		y_aspect_ratio;
	float				aspect_ratio;

	minirt = (t_minirt *)param;
	aspect_ratio = (float)minirt->width / (float)minirt->height;
	print_fps(minirt);
	//print_time(minirt);

	if (minirt->moved == true || minirt->resized == true)
	{
		x = -1;
		x_aspect_ratio =2.0f * aspect_ratio / minirt->width;
		y_aspect_ratio = 2.0f / (float)minirt->height;
		while (++x < minirt->width)
		{
			y = -1;
			while (++y < minirt->height)
				color[x][y] = vector3(0, 0, 0);
		}
		i = 0;
	}
	i++;
	minirt->moved = false;
	minirt->resized = false;
	ray.origin = minirt->camera.pos;
	//minirt->model = get_model();
	//minirt->camera.inv_lookat = mult_mat4x4(minirt->camera.inv_perspective, minirt->camera.inv_lookat);
	x = -1;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			ray.direction = create_ray( (float) x * x_aspect_ratio - aspect_ratio,\
			 1.0f - y * y_aspect_ratio, minirt);
			color[x][y] = vector3_add(color[x][y] , perpixel(ray, &minirt->scene,  x * minirt->height + y + i * 719393));
			accumulated_color = vector3_multiply_float(color[x][y] , 1.0f / (float)i);
			accumulated_color = vector3_clamp(accumulated_color, 0.0f, 1.0f);			
			mlx_put_pixel(minirt->img, x, y, get_rgba(accumulated_color));
		}
	}
}

/*void	hook(void *param)
{
	t_minirt *minirt = (t_minirt *)param;
	t_ray ray;
	t_scene scene;
	t_vector3 color;
	int				x;
	int y;

	print_fps(minirt);
	x = -1;
	ray.origin = minirt->camera.pos;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			t_vector3 coord = vector3((float)x / (float)minirt->width,
				(float)(y) / (float)minirt->height,0);
			coord = vector3(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f,0);
			ray.direction = create_ray(coord.x, coord.y, minirt);
			color = PerPixel(ray, &minirt->scene,  x * minirt->height + y);
			mlx_put_pixel(minirt->img,minirt->width - x - 1, minirt->height - y
				- 1, get_rgba(color));
		}
	}
}*/

void	resize(int32_t width, int32_t height, void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	mlx_delete_image(minirt->mlx, minirt->img);
	minirt->img = mlx_new_image(minirt->mlx, width, height);
	if (!minirt->img)
		exit(EXIT_FAILURE);
	minirt->width = width;
	minirt->height = height;
	free(minirt->camera.ray_dir);
	minirt->camera.ray_dir = malloc(sizeof(t_vector3) * minirt->width \
		* minirt->height);
	if (!minirt->camera.ray_dir)
	{
		minirt->error = ERROR;
		minirt->camera.ray_dir = NULL;
		exit(ERROR);
	}
	calculateprojection(minirt);
	minirt->moved = true;
	minirt->resized = true;
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
}

void	cursor(double xpos, double ypos, void *param)
{
	t_minirt		*minirt;
	static float	lastx;
	static float	lasty;
	t_matrix4x4		mat[2];
	static int		i;

	minirt = (t_minirt *)param;
	if (minirt->camera.is_clicked == false)
	{
		i = 0;
		return ;
	}
	if (i == 0)
	{
		mlx_set_mouse_pos(minirt->mlx, minirt->width / 2, minirt->height / 2);
		lastx = 0;
		lasty = 0;
		i++;
		return ;
	}
	if (lastx == lasty == 0)
	{
		lastx = 0;
		lasty = 0;
	}
	xpos = (xpos / minirt->width) * 2.0f - 1.0f;
	ypos = (ypos / minirt->height) * 2.0f - 1.0f;

	// if (xpos >= lastx)
	// minirt->camera.pitch += 1;
	// else if (xpos < lastx)
	// minirt->camera.pitch -= 1;
	// if (ypos >= lasty)
	// minirt->camera.yaw += 1;
	// else if (ypos < lasty)
	// minirt->camera.yaw -= 1;

	minirt->camera.pitch += (xpos - lastx) * 1.5f;
	minirt->camera.yaw += (ypos - lasty) * 1.5f;

	lastx = xpos;
	lasty = ypos;

	// xpos = asin(minirt->camera.pitch);
	// ypos = atan2(minirt->camera.yaw, 1.0f);

	mat[0] = rotation_y(to_radian(minirt->camera.pitch));
	mat[1] = rotation_x(to_radian(minirt->camera.yaw));

	minirt->camera.inv_lookat = mult_mat4x4(mat[1], mat[0]);

	mat[0] = rotation_y(to_radian(-minirt->camera.pitch));
	mat[1] = rotation_x(to_radian(-minirt->camera.yaw));
	minirt->camera.forward = multiplymatrixvector(minirt->camera.forward, \
		minirt->camera.inv_lookat);
	minirt->camera.forward = vector3_normalize(minirt->camera.forward);
	mlx_set_mouse_pos(minirt->mlx, minirt->width / 2, minirt->height / 2);

	minirt->moved = true;
}
// 0 1 0 y bas
// 0 -1 0 y haut
// -1 0 0 x droite
// 1 0 0 x gauche

void	mousehook(mouse_key_t button, action_t action, modifier_key_t mods, \
		void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action != MLX_RELEASE)
		minirt->camera.is_clicked = true;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		minirt->camera.is_clicked = false;
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_minirt	*minirt;
	float		speed;
	t_vector3	updirection;
	t_vector3	rightdirection;


	minirt = (t_minirt *)param;
	speed = 0.05f;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action != MLX_RELEASE)
	{
		mlx_close_hook(minirt->mlx, &close_function, minirt);
		mlx_close_window(minirt->mlx);
		minirt->error = ERROR;
	}
	updirection = vector3(0.0f, 1.0f, 0.0f);
	rightdirection = vector3_cross(minirt->camera.forward,\
	 vector3(0.0f, 1.0f, 0.0f));
	// if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
	// 	minirt->camera.pos = vector3_add(minirt->camera.pos,vector3_multiply_float(rightdirection, speed));
	// if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
	// 	minirt->camera.pos = vector3_subtract(minirt->camera.pos,vector3_multiply_float(rightdirection, speed));
	// if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
	// 	minirt->camera.pos = vector3_add(minirt->camera.pos,vector3_multiply_float(updirection, speed));
	// if (keydata.key == MLX_KEY_Q && keydata.action != MLX_RELEASE)
	// 	minirt->camera.pos = vector3_subtract(minirt->camera.pos,vector3_multiply_float(updirection, speed));
	// if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
	// 	minirt->camera.pos = vector3_add(minirt->camera.pos,vector3_multiply_float(minirt->camera.forward, speed));
	// if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
	// 	minirt->camera.pos = vector3_subtract(minirt->camera.pos,vector3_multiply_float(minirt->camera.forward, speed));

	if (keydata.key == MLX_KEY_1 && keydata.action != MLX_RELEASE)
		minirt->radius += 0.1f;
	if (keydata.key == MLX_KEY_2 && keydata.action != MLX_RELEASE)
		minirt->radius -= 0.1f;
	if (keydata.key == MLX_KEY_4 && keydata.action != MLX_RELEASE)
		minirt->x += 0.1f;
	if (keydata.key == MLX_KEY_6 && keydata.action != MLX_RELEASE)
		minirt->x -= 0.1f;
	if (keydata.key == MLX_KEY_8 && keydata.action != MLX_RELEASE)
		minirt->y += 0.1f;
	if (keydata.key == MLX_KEY_5 && keydata.action != MLX_RELEASE)
		minirt->y -= 0.1f;
	if (keydata.key == MLX_KEY_7 && keydata.action != MLX_RELEASE)
		minirt->z += 0.1f;
	if (keydata.key == MLX_KEY_9 && keydata.action != MLX_RELEASE)
		minirt->z -= 0.1f;

	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		minirt->camera.pos.x += speed;
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		minirt->camera.pos.x -= speed;
	if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
		minirt->camera.pos.y += speed;
	if (keydata.key == MLX_KEY_Q && keydata.action != MLX_RELEASE)
		minirt->camera.pos.y -= speed;
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		minirt->camera.pos.z -= speed;
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		minirt->camera.pos.z += speed;
	//
	// if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
	// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos,translation(vector3_multiply_float(rightdirection, -1.0f)));
	// if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
	// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos,translation(rightdirection));
	// if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
	// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos, translation(updirection));
	// if (keydata.key == MLX_KEY_LEFT_CONTROL	&& keydata.action != MLX_RELEASE)
	// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos,translation(vector3_multiply_float(updirection, -1.0f)));
	// if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
	// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos,translation(vector3_multiply_float(minirt->camera.forward, -1.0f)));
	// if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
	// minirt->camera.pos = multiplymatrixvector(minirt->camera.pos,translation(minirt->camera.forward));

	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_A
		|| keydata.key == MLX_KEY_SPACE || keydata.key == MLX_KEY_LEFT_CONTROL
		|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_Q)

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

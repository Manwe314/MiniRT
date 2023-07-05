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

// used struc timeval to print the time between each frames
float	print_time(t_minirt *minirt)
{
	static struct timeval	last_time;
	struct timeval			current_time;
	float					time;
	static float			moyenne;
	static int				i;

	(void)minirt;
	i++;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - last_time.tv_sec) * 1000.0f
		+ (current_time.tv_usec - last_time.tv_usec) / 1000.0f;
	if (time > 10.0f)
		last_time = current_time;
	if (i < 20)
		return (0);
	moyenne += time;
	moyenne /= i;
	return (moyenne);
}

void	print_fps(t_minirt *minirt)
{
	static int	frames;
	static int	last_time;
	static int	i;
	int			current_time;
	float		moyenne;

	frames++;
	i++;
	current_time = time(NULL);
	moyenne = print_time(minirt);
	if (current_time - last_time >= 1)
	{
		printf("FPS: %d   frames = %d, moyenne = %f\n", frames, i, moyenne);
		frames = 0;
		last_time = current_time;
	}
}

bool	something_changed(t_minirt *minirt)
{
	if (minirt->moved == true || minirt->resized == true)
		return (true);
	return (false);
}

bool	should_stop(t_minirt *minirt)
{
	if (minirt->stop == true)
		return (true);
	return (false);
}

void	free_param(t_param *param)
{
	free(param->ray);
	free(param->accumulated_color);
}

void	malloc_param(t_param *param, t_minirt *minirt)
{
	param->ray = malloc(sizeof(t_ray) * (minirt->width * minirt->height));
	param->accumulated_color = malloc(sizeof(t_vector3)
			* (minirt->width * minirt->height));
}

void	set_param(t_param *param, t_minirt *minirt)
{
	int		x;
	int		y;
	float	x_aspect_ratio;
	float	y_aspect_ratio;
	float	aspect_ratio;

	x = -1;
	aspect_ratio = (float)minirt->width / (float)minirt->height;
	x_aspect_ratio = 2.0f * aspect_ratio / minirt->width;
	y_aspect_ratio = 2.0f / (float)minirt->height;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			param->accumulated_color[x * minirt->height + y] = vector3(0, 0, 0);
			param->ray[x * minirt->height + y].origin = minirt->camera.pos;

			param->ray[x * minirt->height + y].direction
				= create_ray((float)x * x_aspect_ratio - aspect_ratio,
					1.0f - y * y_aspect_ratio, minirt);
		}
	}
}

void	reset_param(t_param *param, t_minirt *minirt)
{
	static int	i;

	minirt->moved = false;
	minirt->resized = false;
	param->frames = 0;
	if (i++ == 0)
	{
		malloc_param(param, minirt);
		set_param(param, minirt);
		return ;
	}
	free_param(param);
	malloc_param(param, minirt);
	set_param(param, minirt);
}

void	for_each_pixel(t_param *param, const t_minirt *minirt)
{
	int			x;
	int			y;
	int			i;
	t_vector3	color;

	x = -1;
	param->frames++;
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			i = x * minirt->height + y;
			color = perpixel(param->ray[i], &minirt->scene, i + param->frames);
			param->accumulated_color[i] = \
				vector3_add(param->accumulated_color[i], color);
			color = vector3_multiply_float(param->accumulated_color[i],
					1.0f / (float)(param->frames));
			color = vector3_clamp(color, 0.0f, 1.0f);
			mlx_put_pixel(minirt->img, x, y, get_rgba(color));
		}
	}
}

void	hook(void *mini)
{
	t_minirt		*minirt;
	static t_param	param;

	minirt = (t_minirt *)mini;
	print_fps(minirt);
	if (should_stop(minirt))
	{
		free_param(&param);
		mlx_close_hook(minirt->mlx, &close_function, minirt);
		mlx_close_window(minirt->mlx);
		return ;
	}
	if (something_changed(minirt))
		reset_param(&param, minirt);
	for_each_pixel(&param, minirt);
}



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
	minirt->moved = true;
	minirt->resized = true;
	mlx_image_to_window(minirt->mlx, minirt->img, 0, 0);
}

void	cursor(double xpos, double ypos, void *param)
{
	t_minirt		*minirt;
	t_matrix4x4		mat[2];

	minirt = (t_minirt *)param;
	if (minirt->camera.is_clicked == false)
		return ;
	mlx_set_mouse_pos(minirt->mlx, minirt->width / 2, minirt->height / 2);
	xpos = (xpos / minirt->width) * 2.0f - 1.0f;
	ypos = (ypos / minirt->height) * 2.0f - 1.0f;
	minirt->camera.pitch += xpos * 1.5f;
	minirt->camera.yaw += ypos * 1.5f;
	if (minirt->camera.yaw > 90)
		minirt->camera.yaw = 90;
	if (minirt->camera.yaw < -90)
		minirt->camera.yaw = -90;
	mat[0] = rotation_y(to_radian(minirt->camera.pitch));
	mat[1] = rotation_x(to_radian(minirt->camera.yaw));
	minirt->camera.inv_lookat = mult_mat4x4(mat[1], mat[0]);
	minirt->moved = true;
}

void	mousehook(mouse_key_t button, action_t action, modifier_key_t mods, \
		void *param)
{
	t_minirt	*minirt;

	(void)mods;
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

	minirt = (t_minirt *)param;
	speed = 0.05f;
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
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_A
		|| keydata.key == MLX_KEY_SPACE || keydata.key == MLX_KEY_LEFT_CONTROL
		|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_Q)
		minirt->moved = true;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		minirt->stop = true;
}

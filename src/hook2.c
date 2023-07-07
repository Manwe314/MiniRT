/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:47:00 by beaudibe          #+#    #+#             */
/*   Updated: 2023/07/07 12:01:20 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

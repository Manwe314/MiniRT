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
	while (++x < minirt->width)
	{
		y = -1;
		while (++y < minirt->height)
		{
			i = x * minirt->height + y;
			if (BONUS == 1)
				color = shoot_ray(param->ray[i],
						&minirt->scene, i + ++param->frames);
			else
				color = shoot_bonus(param->ray[i],
						&minirt->scene, i + ++param->frames);
			param->accumulated_color[i] = \
				vector3_add(param->accumulated_color[i], color);
			color = vector3_clamp(vector3_multiply_float(\
			param->accumulated_color[i], 1.0f / (float)(param->frames)), 0, 1);
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

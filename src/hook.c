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
		minirt->camera.pos.z += speed;
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		minirt->camera.pos.z -= speed;

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

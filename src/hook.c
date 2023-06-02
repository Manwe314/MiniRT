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
	float speed = 0.01f;
	t_vec3 updirection;
	t_vec3 rightdirection;

	updirection = vec3(0.0f, 1.0f, 0.0f);
	rightdirection = vec3_cross(minirt->camera.forward, updirection);
	printf("pos: %f %f %f\n", minirt->camera.pos.x, minirt->camera.pos.y, minirt->camera.pos.z);
	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vec3_add(minirt->camera.pos, vec3_multf(rightdirection, speed));
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vec3_sub(minirt->camera.pos, vec3_multf(rightdirection, speed));
	if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vec3_add(minirt->camera.pos, vec3_multf(updirection, speed));
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vec3_sub(minirt->camera.pos, vec3_multf(updirection, speed));
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vec3_add(minirt->camera.pos, vec3_multf(minirt->camera.forward, speed));
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		minirt->camera.pos = vec3_sub(minirt->camera.pos, vec3_multf(minirt->camera.forward, speed));

	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_A \
	|| keydata.key == MLX_KEY_SPACE || keydata.key == MLX_KEY_LEFT_CONTROL \
	|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
	{
		minirt->moved = true;
		// calculateraydirections(minirt);
		// calculateview(minirt);
	}

}

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
	(void)param;
	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		g_minirt.world.coord_world.x += 0.1;
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		g_minirt.world.coord_world.x -= 0.1;
	if (keydata.key == MLX_KEY_SPACE && keydata.action != MLX_RELEASE)
		g_minirt.world.coord_world.y += 0.1;
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action != MLX_RELEASE)
		g_minirt.world.coord_world.y -= 0.1;
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		g_minirt.world.coord_world.z += 0.1;
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE)
		g_minirt.world.coord_world.z -= 0.1;

	if (keydata.key == MLX_KEY_KP_5 && keydata.action != MLX_RELEASE)
		g_minirt.world.angle_world.x += 10;
	if (keydata.key == MLX_KEY_KP_8 && keydata.action != MLX_RELEASE)
		g_minirt.world.angle_world.x -= 10;
	if (keydata.key == MLX_KEY_KP_6 && keydata.action != MLX_RELEASE)
		g_minirt.world.angle_world.y += 10;
	if (keydata.key == MLX_KEY_KP_4 && keydata.action != MLX_RELEASE)
		g_minirt.world.angle_world.y -= 10;
	if (keydata.key == MLX_KEY_KP_7 && keydata.action != MLX_RELEASE)
		g_minirt.world.angle_world.z += 10;
	if (keydata.key == MLX_KEY_KP_9 && keydata.action != MLX_RELEASE)
		g_minirt.world.angle_world.z -= 10;
}

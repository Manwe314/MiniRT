/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_eye.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:19:34 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:19:34 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calculateprojection(t_minirt *minirt)
{
	// minirt->camera.inv_perspective = matrixInverse(
	// createperspectivematrix(minirt->camera.fov, minirt->width / minirt->height,
	// 0.1f, 100.0f), 4);
	minirt->camera.inv_perspective = inverse_perspective_matrix(\
	minirt->camera.fov,	minirt->width / minirt->height, 0.1, 100);
}

void	calculatelookat(t_minirt *minirt)
{
	t_vector3	target;

	target = vector3_multiply_float(minirt->camera.forward, 100.0f);
	target = vector3_add(minirt->camera.pos, target);
	minirt->camera.inv_lookat = inverse_lookat_matrix(minirt->camera.pos, \
		target, vector3(0, 1, 0));
	// minirt->camera.inv_lookat = FPSViewRH(minirt->camera.pos, minirt->camera.pitch, minirt->camera.yaw);
	// minirt->camera.inv_lookat = matrixInverse(
	// lookat(minirt->camera.pos, target, vector3(0, 1, 0)), 4);
}

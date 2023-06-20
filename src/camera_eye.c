/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_eye.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:56:22 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/13 17:01:10 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void calculateprojection(t_minirt *minirt)
{
	// minirt->camera.inv_perspective = matrixInverse(
	// createperspectivematrix(minirt->camera.fov, minirt->width / minirt->height,
	// 0.1f, 100.0f), 4);
	minirt->camera.inv_perspective = inverse_perspective_matrix( \
	minirt->camera.fov, minirt->width / minirt->height, 0.1, 100);
}

void calculatelookat(t_minirt *minirt)
{
	t_vector3 target;

	target = vector3_multiply_float(minirt->camera.forward, 100.0f);
	target = vector3_add(minirt->camera.pos, target);
	minirt->camera.inv_lookat = inverse_lookat_matrix(minirt->camera.pos, \
	target, vector3(0, 1, 0));
	//minirt->camera.inv_lookat = FPSViewRH(minirt->camera.pos, minirt->camera.pitch, minirt->camera.yaw);
	// minirt->camera.inv_lookat = matrixInverse(
	// lookat(minirt->camera.pos, target, vector3(0, 1, 0)), 4);
}

void calculateraydirections(t_minirt *minirt)
{
	int x = -1;
	while (++x < minirt->width)
	{
		int y = minirt->height;
		while (--y > 0)
		{
			t_vector2 coord = vector2((float)x / (float)minirt->width, (float)(y) / (float)minirt->height);
			coord = vector2(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f);

			t_vector3 target = multiplymatrixvector(vector3(coord.x, coord.y, 1), minirt->camera.inv_perspective);
			minirt->camera.ray_dir[x + y * minirt->width] = \
			multiplymatrixvector(vector3_normalize(target), minirt->camera.inv_lookat);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_eye.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:56:22 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/05 20:08:35 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void calculateprojection(t_minirt *minirt)
{
	minirt->camera.inv_perspective = matrixInverse(
	createperspectivematrix(minirt->camera.fov, minirt->width / minirt->height,
	0.1f, 100.0f), 4);
	// minirt->camera.inv_perspective = inverse_perspective_matrix( \
	// minirt->camera.fov, minirt->width / minirt->height, 0.1f, 100.0f);
}

void calculatelookat(t_minirt *minirt)
{
	minirt->camera.inv_lookat = matrixInverse(
	lookat(minirt->camera.pos, vector3_add(minirt->camera.pos, minirt->camera.forward),
	vector3(0, 1, 0)), 4);
	// minirt->camera.inv_lookat = inverse_lookat_matrix(minirt->camera.pos, \
	// vector3_add(minirt->camera.pos, minirt->camera.forward), vector3(0, 1, 0));
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

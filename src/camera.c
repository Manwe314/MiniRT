/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:23:49 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/02 13:23:49 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void calculateprojection(t_minirt *minirt)
{
	minirt->camera.inv_perspective = matrixInverse( \
	createperspectivematrix(minirt->camera.fov, minirt->width / minirt->height,\
	0.1f, 100.0f), 4);
}

void calculateview(t_minirt *minirt)
{
	minirt->camera.inv_lookat = matrixInverse( \
	lookat(minirt->camera.pos, vec3_add(minirt->camera.pos, minirt->camera.forward), \
	vec3(0, 1, 0)), 4);
}

void calculateraydirections(t_minirt *minirt)
{
	int x = -1;
	while (++x < minirt->width)
	{
		int y = minirt->height;
		while (--y > 0)
		{
			t_vec2 coord = vec2((float)x / (float)minirt->width, (float)(y) / (float)minirt->height);
			coord = vec2(coord.x * 2.0f - 1.0f, coord.y * 2.0f - 1.0f);

			t_vec3 target = multiplymatrixvector(vec3(coord.x, coord.y, 1), minirt->camera.inv_perspective);
			minirt->camera.ray_dir[x + y * minirt->width] = \
			multiplymatrixvector(vec3_normalize(target), minirt->camera.inv_lookat);
		}
	}
}

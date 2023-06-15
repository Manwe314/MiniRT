/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:31:28 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/07 15:31:28 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray create_ray(float x, float y, t_minirt *minirt)
{
	t_ray ray;
	t_vector4 cameraSpacePos;
	t_vector4 worldSpacePos;

	cameraSpacePos = multiplymatrixvector4(vector4(x, y, -1, 1), minirt->camera.inv_perspective);
	worldSpacePos = multiplymatrixvector4(cameraSpacePos, minirt->camera.inv_lookat);

	ray.origin = minirt->camera.pos;
	ray.direction = vector3(x, y, -1);
	ray.direction = vector3_normalize(ray.direction);
	// ray.direction = vector3_subtract(vector3(worldSpacePos.x, worldSpacePos.y, worldSpacePos.z), ray.origin);
	// ray.direction = vector3_normalize(ray.direction);
	return (ray);
}

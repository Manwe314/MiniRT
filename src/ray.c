/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:21:41 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:41 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	create_ray(float x, float y, t_minirt *minirt)
{
	t_vector3	direction;

	direction = vector3(x * minirt->camera.fov / 90.0,
			y * minirt->camera.fov / 90.0, -1);
	direction = multiplymatrixvector(direction, minirt->camera.inv_lookat);
	return (direction);
}

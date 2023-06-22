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

t_vector3 create_ray(float x, float y, t_minirt *minirt)
{
	t_vector3 direction;

	direction = vector3(x * minirt->camera.fov / 90.0, y, -1);
	direction = vector3_normalize(direction);
	return (direction);
}

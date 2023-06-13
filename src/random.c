/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:04:24 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/08 14:04:24 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int nextrandom(uint state)
{
	state = state * 747796405 + 2891336453;
	uint result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
	result = (result >> 22) ^ result;
	return result;
}

// float randomvalue(uint state)
// {
// 	return nextrandom(state) / 4294967295.0; // 2^32 - 1
// }

float randomvalue(uint state)
{
	return rand() / (float)RAND_MAX;
}

// Random value in normal distribution (with mean=0 and sd=1)
float randomvaluevormaldistribution(uint state)
{
	float theta = 2 * 3.1415926 * randomvalue(state);
	float rho = sqrt(-2 * log(randomvalue(state)));
	return rho * cos(theta);
}

// Calculate a random direction
t_vector3 random_direction(uint state)
{
	t_vector3 vec;

	vec.x = randomvaluevormaldistribution(state);
	vec.y = randomvaluevormaldistribution(state);
	vec.z = randomvaluevormaldistribution(state);
	return (vector3_normalize(vec));
}

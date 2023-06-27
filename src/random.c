/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:21:18 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:18 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	nextrandom(uint state)
{
	static uint	seed;
	uint		result;

	if (seed == 0)
		seed = 4532156;
	seed += 56;
	state += seed;
	state = state * 747796405 + 2891336453;
	result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
	result = (result >> 22) ^ result;
	return (result);
}

// float randomvalue(uint state)
// {
// return (nextrandom(state) / (float)RAND_MAX); // 2^32 - 1
// }
//
float	randomvalue(uint state)
{
	return (rand() / (float)RAND_MAX);
}

// Random value in normal distribution
float	randomvaluevormaldistribution(uint state)
{
	float	theta;
	float	rho;

	if (RANDOM != 1)
		return (0.0f);
	theta = 2 * 3.1415926 * randomvalue(state);
	rho = sqrt(-2 * log(randomvalue(state)));
	return (rho * cos(theta));
}

// Calculate a random direction
t_vector3	random_direction(uint state)
{
	t_vector3	vec;

	vec.x = randomvaluevormaldistribution(state);
	vec.y = randomvaluevormaldistribution(state);
	vec.z = randomvaluevormaldistribution(state);
	return (vector3_normalize(vec));
}

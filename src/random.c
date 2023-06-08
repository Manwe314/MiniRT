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

#include <time.h>
float	random_float()
{
	uint result;
	static int seed;

	seed++;
	int state = seed;
	state = state * 747796405 + 2891336453;
	result = (state >> ((state >> 28) + 4)) ^ state * 277803737;
	result = (result >> 22) ^ result;
	return ((result / 4294967295.0) - 0.5f);
}

// float	random_float(void)
// {
// 	float	random;
// 	float min = -0.5f;
// 	float max = 0.5f;
// 	random = (float)rand() / (float)RAND_MAX;
// 	return (min + (max - min) * random);
// }

t_vector3 vector3_random(float x, float y)
{
	t_vector3 vec;
	static long long state;
	float random[3];

	// random[0] = random_float(x * y * 53 + state);
	// random[1] = random_float((x * 2 + 1) * y * 123 + state);
	// random[2] = random_float(x * (y * 2 + 1) * 652 + state);
	vec.x = random_float();
	vec.y = random_float();
	vec.z = random_float();
	state++;
	if (state > 1000000000000000000)
		state = 0;
	return (vec);
}

/*
float	random_float(void)
{
	float	random;
	float min = -0.5f;
	float max = 0.5f;
	random = (float)rand() / (float)RAND_MAX;
	return (min + (max - min) * random);
}

t_vector3 vector3_random(float x, float y)
{
	t_vector3 vec;

	vec.x = random_float();
	vec.y = random_float();
	vec.z = random_float();
	return (vec);
}
*/

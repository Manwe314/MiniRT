/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:57:56 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/06 10:57:56 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(const char *str)
{
	float	result;
	float	fractionfactor;
	int		sign;
	int		i;

	result = 0.0;
	i = 0;
	fractionfactor = 0.1;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' && *str++)
		sign = -1;
	while (ft_isdigit(*str) && i++ < 11)
		result = result * 10 + (*str++ - '0');
	if (i > 10)
		return (INT_MAX - 10);
	i = 0;
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str) && i++ < 11)
		{
			result += (*str++ - '0') * fractionfactor;
			fractionfactor *= 0.1;
		}
		if (i > 10)
			return (INT_MAX - 10);
	}
	return (result * sign);
}

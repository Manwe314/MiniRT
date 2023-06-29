/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:21:58 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:58 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_all_space(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '	')
			j++;
		i++;
	}
	if (i == j)
		return (1);
	return (0);
}

float	ft_atof(const char *str)
{
	float	result;
	float	fractionfactor;
	int		sign;

	result = 0.0;
	fractionfactor = 0.1;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' && *str++)
		sign = -1;
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result += (*str++ - '0') * fractionfactor;
			fractionfactor *= 0.1;
		}
	}
	return (result * sign);
}

int	get_rgba(t_vector3 color)
{
	color.x = color.x * 255.0f;
	color.y = color.y * 255.0f;
	color.z = color.z * 255.0f;
	return ((int)color.x << 24 | (int)color.y << 16 | (int)color.z << 8 | 255);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		i++;
	return (i);
}

t_vector3	get_vector3(const char *line, int i, t_input_list *input)
{
	char		**values;
	char		*param;
	int			j;
	t_vector3	output;

	j = i;
	while (line[j] != ' ' && line[j] != '\0')
		j++;
	param = ft_substr(line, i, j - i);
	values = ft_split(param, ',');
	if (split_size(values) != 3)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
	else
	{
		output.x = ft_atof(values[0]);
		output.y = ft_atof(values[1]);
		output.z = ft_atof(values[2]);
	}
	free_split(values);
	free(param);
	return (output);
}

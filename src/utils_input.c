/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:16:56 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/05 18:17:51 by lkukhale         ###   ########.fr       */
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

float ft_atof(const char* str)
{
    int i = 0;
    int sign = 1;
    float result = 0.0;
    float fraction = 0.0;
    float divisor = 10.0;

    while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i] != '\0')
        i++;
    if (str[i] == '-')
	{
        sign = -1;
        i++;
    }
	else if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
	{
        i++;
        while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
		{
            fraction += (str[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }
    result += fraction;
	result = roundf(result * 100) / 100;
    result *= sign;
    return (result);
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

int split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		i++;
	return (i);
}

t_vector3 get_vector3(const char *line, int i, t_input_list *input)
{
	char **values;
	char *param;
	int j;
	t_vector3 output;

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

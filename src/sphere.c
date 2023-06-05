/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:06:32 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/05 18:07:34 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int validate_line_sphere(const char *line)
{
	char **inputs;
	int i;
	int j;

	inputs = ft_split(line, ' ');
	if (split_size(inputs) != 4)
		return (0);
	i = 1;
	while (inputs[i] != 0)
	{
		j = 0;
		while (inputs[i][j] != '\0')
		{
			if (is_non_valid_character(inputs[i][j]))
			{
				printf("Non valid character on line: \n%s\nObject will not be rendered\n", line);
				free_split(inputs);
				return (0);
			}
			j++;
		}
		i++;
	}
	free_split(inputs);
	return (1);
}

t_sphere *init_sphere(const char *line, t_input_list *input)
{
	t_sphere *obj;
	int i;

	obj = (t_sphere *)malloc(sizeof(t_sphere));
	if (!validate_line_sphere(line))
	{
		free(input->name);
		input->name = ft_strdup("inv");
		return (obj);
	}
	i = get_to_next_param(line, 0, input);
	obj->center = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	obj->radius = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

void validate_values_sphere(t_input_list *input)
{
	int failed;
	t_sphere *obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color , 0.0, 255.0))
	{
		printf("Sphere color out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}
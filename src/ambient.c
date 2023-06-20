/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:02:17 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/05 18:29:43 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int validate_line_ambient(const char *line)
{
	char **inputs;
	int i;
	int j;

	inputs = ft_split(line, ' ');
	if (split_size(inputs) != 3)
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

t_ambient *init_ambient(const char *line, t_input_list *input)
{
	t_ambient *obj;
	int i;

	obj = (t_ambient *)malloc(sizeof(t_ambient));
	if (!validate_line_ambient(line))
	{
		free(input->name);
		input->name = ft_strdup("inv");
		return (obj);
	}
	i = get_to_next_param(line, 0, input);
	obj->intensity = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

void validate_values_ambient(t_input_list *input)
{
	t_ambient *obj;

	obj = input->object;
	if (obj->intensity < 0.0 || obj->intensity > 1.0)
	{
		printf("Ambient light intensity out of range\n");
		free(input->name);
		input->name = ft_strdup("inv");
		return ;
	}
	if (!vector3_checker(obj->color, 0.0, 255.0))
	{
		printf("Ambient light color out of range\n");
		free(input->name);
		input->name = ft_strdup("inv");
	}
}
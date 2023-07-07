/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:26:26 by lkukhale          #+#    #+#             */
/*   Updated: 2023/07/07 19:41:56 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_line_co6(char **inputs, const char *line)
{
	int	i;
	int	j;

	i = 1;
	while (inputs[i] != 0)
	{
		j = -1;
		while (inputs[i][++j] != '\0')
		{
			if (is_non_valid_character(inputs[i][j]))
			{
				printf(\
	"Non valid character on line: \n%s\nObject will not be rendered\n", line);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validate_line_co13(char **inputs, const char *line)
{
	int	i;
	int	j;

	i = 1;
	while (inputs[i] != 0)
	{
		j = -1;
		if (i == 6 && ft_strlen(inputs[i]) == 1 && inputs[i][0] == 'm')
			i++;
		else if (i == 6 && (ft_strlen(inputs[i]) != 1 || inputs[i][0] != 'm'))
			return (0);
		while (inputs[i][++j] != '\0')
		{
			if (is_non_valid_character(inputs[i][j]))
			{
				printf(\
	"Non valid character on line: \n%s\nObject will not be rendered\n", line);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validate_line_cone(const char *line)
{
	char	**inputs;
	int		return_value;

	return_value = 1;
	inputs = ft_split(line, ' ');
	if (split_size(inputs) != 6 && split_size(inputs) != 13)
		return_value = 0;
	if (return_value != 0 && split_size(inputs) == 6)
		return_value = validate_line_co6(inputs, line);
	if (return_value != 0 && split_size(inputs) == 13)
		return_value = validate_line_co13(inputs, line);
	free_split(inputs);
	return (return_value);
}

t_cone	*init_cone(const char *line, t_input_list *input)
{
	t_cone	*obj;
	int		i;

	obj = (t_cone *)malloc(sizeof(t_cone));
	if (!validate_line_cone(line))
	{
		free(input->name);
		input->name = ft_strdup("inv");
		return (obj);
	}
	i = get_to_next_param(line, 0, input);
	obj->center = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	obj->normal = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	obj->radius = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	obj->height = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	obj->color = get_vector3(line, i, input);
	obj->material = get_material_rt(line, input);
	return (obj);
}

void	validate_values_cone(t_input_list *input)
{
	int		failed;
	t_cone	*obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color, 0.0, 255.0))
	{
		printf("Cone color out of range\n");
		failed = 1;
	}
	if (!vector3_checker(obj->normal, -1.0, 1.0))
	{
		printf("Cone normal axis out of range\n");
		failed = 1;
	}
	if (!material_checker(obj->material))
	{
		printf("Cone material is out of rang\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

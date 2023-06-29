/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:20:01 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:20:01 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_line_cylinder(const char *line)
{
	char	**inputs;
	int		i;
	int		j;

	inputs = ft_split(line, ' ');
	if (split_size(inputs) != 6)
		return (0);
	i = 0;
	while (inputs[++i] != 0)
	{
		j = -1;
		while (inputs[i][++j] != '\0')
		{
			if (is_non_valid_character(inputs[i][j]))
			{
				printf(\
	"Non valid character on line: \n%s\nObject will not be rendered\n", line);
				free_split(inputs);
				return (0);
			}
		}
	}
	free_split(inputs);
	return (1);
}

t_cylinder	*init_cylinder(const char *line, t_input_list *input)
{
	t_cylinder	*obj;
	int			i;

	obj = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!validate_line_cylinder(line))
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
	return (obj);
}

void	validate_values_cylinder(t_input_list *input)
{
	int			failed;
	t_cylinder	*obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color, 0.0, 255.0))
	{
		printf("Cylinder color out of range\n");
		failed = 1;
	}
	if (!vector3_checker(obj->normal, -1.0, 1.0))
	{
		printf("Cylinder normal axis out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

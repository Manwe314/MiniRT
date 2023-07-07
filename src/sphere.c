/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:21:49 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:49 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_line_sp4(char **inputs, const char *line)
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
				printf("SP HI\n");
				printf(\
	"Non valid character on line: \n%s\nObject will not be rendered\n", line);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validate_line_sp11(char **inputs, const char *line)
{
	int	i;
	int	j;

	i = 1;
	while (inputs[i] != 0)
	{
		j = -1;
		if (i == 4 && ft_strlen(inputs[i]) == 1 && inputs[i][0] == 'm')
			i++;
		else if (i == 4 && (ft_strlen(inputs[i]) != 1 || inputs[i][0] != 'm'))
			return (0);
		while (inputs[i][++j] != '\0')
		{
			if (is_non_valid_character(inputs[i][j]))
			{
				printf("SP HI\n");
				printf(\
	"Non valid character on line: \n%s\nObject will not be rendered\n", line);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validate_line_sphere(const char *line)
{
	char	**inputs;
	int		return_value;

	return_value = 1;
	inputs = ft_split(line, ' ');
	if (split_size(inputs) != 4 && split_size(inputs) != 11)
		return_value = 0;
	if (return_value != 0 && split_size(inputs) == 4)
		return_value = validate_line_sp4(inputs, line);
	if (return_value != 0 && split_size(inputs) == 11)
		return_value = validate_line_sp11(inputs, line);
	free_split(inputs);
	return (return_value);
}

t_sphere	*init_sphere(const char *line, t_input_list *input)
{
	t_sphere	*obj;
	int			i;

	obj = (t_sphere *)malloc(sizeof(t_sphere));
	if (!validate_line_sphere(line))
	{
		printf("~SP~ HI\n");
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
	obj->material = get_material_rt(line, input);
	return (obj);
}

void	validate_values_sphere(t_input_list *input)
{
	int			failed;
	t_sphere	*obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color, 0.0, 255.0))
	{
		printf("Sphere color out of range\n");
		failed = 1;
	}
	if (!material_checker(obj->material))
	{
		printf("Sphere material out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

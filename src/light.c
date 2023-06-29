/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:20:35 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:20:35 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_line_light(const char *line)
{
	char	**inputs;
	int		i;
	int		j;

	inputs = ft_split(line, ' ');
	if (split_size(inputs) != 4)
		return (0);
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
				free_split(inputs);
				return (0);
			}
		}
		i++;
	}
	free_split(inputs);
	return (1);
}

t_light	*init_light(const char *line, t_input_list *input)
{
	t_light	*obj;
	int		i;

	obj = (t_light *)malloc(sizeof(t_light));
	if (!validate_line_light(line))
	{
		free(input->name);
		input->name = ft_strdup("inv");
		return (obj);
	}
	i = get_to_next_param(line, 0, input);
	obj->position = get_vector3(line, i, input);
	i = get_to_next_param(line, i, input);
	obj->brightness = ft_atof(line + i);
	i = get_to_next_param(line, i, input);
	obj->color = get_vector3(line, i, input);
	return (obj);
}

void	validate_values_light(t_input_list *input)
{
	int		failed;
	t_light	*obj;

	failed = 0;
	obj = input->object;
	if (!vector3_checker(obj->color, 0.0, 255.0))
	{
		printf("light color out of range\n");
		failed = 1;
	}
	if (obj->brightness < 0 || obj->brightness > 1.0)
	{
		printf("Light brightness out of range\n");
		failed = 1;
	}
	if (failed)
	{
		free(input->name);
		input->name = ft_strdup("inv");
	}
}

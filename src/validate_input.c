/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <beaudibe@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:22:07 by beaudibe          #+#    #+#             */
/*   Updated: 2023/06/27 20:22:07 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	has_invalid_input(t_input_list *input)
{
	t_input_list	*traverse;
	int				is_invalid;

	traverse = input;
	is_invalid = 0;
	while (traverse != 0)
	{
		if (traverse->name == 0)
			is_invalid = 1;
		traverse = traverse->next;
	}
	return (is_invalid);
}

void	check_esentials(t_minirt *minirt)
{
	t_input_list	*traverse;
	int				has_esentials;
	int				has_an_object;

	has_esentials = 0;
	has_an_object = 0;
	traverse = minirt->input_head;
	while (traverse != 0)
	{
		if (ft_strncmp(traverse->name, "Ambient", 7) == 0
			|| (ft_strncmp(traverse->name, "Camera", 6) == 0)
			|| (ft_strncmp(traverse->name, "Light", 5) == 0))
			has_esentials++;
		else
			has_an_object++;
		traverse = traverse->next;
	}
	if (has_esentials != 3 && has_an_object == 0)
	{
		printf("Error\nCritical error nothing will be rendered\n");
		minirt->input_validity = -1;
	}
	else
		minirt->input_validity = 1;
}

t_input_list	*get_first_valid_node(t_input_list *lst)
{
	while (lst != 0)
	{
		if (lst != 0 && (lst->name == 0 || ft_strncmp(lst->name, "inv",
					3) == 0))
			lst = lst->next;
		else
			return (lst);
	}
	return (0);
}

void	final_prepare_input(t_minirt *minirt)
{
	t_input_list	*traverse;
	t_input_list	*temp;
	t_input_list	*last_valid;
	t_input_list	*first_valid;

	traverse = minirt->input_head;
	last_valid = traverse;
	first_valid = get_first_valid_node(minirt->input_head);
	while (traverse != 0)
	{
		if (traverse != 0 && traverse->name == 0)
		{
			temp = traverse->next;
			if (last_valid != 0 && (last_valid->name == 0
					|| ft_strncmp(last_valid->name, "inv", 3) == 0))
				last_valid = last_valid->next;
			else
				last_valid->next = temp;
			free(traverse);
			traverse = temp;
		}
		else if (traverse != 0 && ft_strncmp(traverse->name, "inv", 3) == 0)
		{
			temp = traverse->next;
			if (last_valid != 0 && (last_valid->name == 0
					|| ft_strncmp(last_valid->name, "inv", 3) == 0))
				last_valid = last_valid->next;
			else
				last_valid->next = temp;
			free(traverse->name);
			free(traverse->object);
			free(traverse);
			traverse = temp;
		}
		else
		{
			if (traverse->next != 0 && traverse->next->name != 0
				&& ft_strncmp(traverse->next->name, "inv", 3 != 0))
				last_valid = traverse->next;
			else
				last_valid = traverse;
			traverse = traverse->next;
		}
	}
	//print_input(minirt);
	minirt->input_head = first_valid;
	check_esentials(minirt);
}

void	validate_input(t_minirt *minirt)
{
	t_input_list	*input;

	input = minirt->input_head;
	while (input != 0)
	{
		if (input->name == 0 || ft_strncmp(input->name, "inv", 3) == 0)
			printf(\
				"Invalid object description, object will not be rendered\n");
		if (ft_strncmp(input->name, "Ambient", 7) == 0)
			validate_values_ambient(input);
		if (ft_strncmp(input->name, "Camera", 6) == 0)
			validate_values_camera(input);
		if (ft_strncmp(input->name, "Light", 5) == 0)
			validate_values_light(input);
		if (ft_strncmp(input->name, "Sphere", 6) == 0)
			validate_values_sphere(input);
		if (ft_strncmp(input->name, "Plane", 5) == 0)
			validate_values_plane(input);
		if (ft_strncmp(input->name, "Cylinder", 8) == 0)
			validate_values_cylinder(input);
		input = input->next;
	}
	final_prepare_input(minirt);
}

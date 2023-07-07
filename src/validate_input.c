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

void	handle_null_node(t_input_list **last_valid, t_input_list **traverse)
{
	t_input_list	*temp;

	temp = (*traverse)->next;
	if (last_valid != 0 && ((*last_valid)->name == 0
			|| ft_strncmp((*last_valid)->name, "inv", 3) == 0))
		(*last_valid) = (*last_valid)->next;
	else
		(*last_valid)->next = temp;
	free((*traverse));
	(*traverse) = temp;
}

void	handle_in_node(t_input_list **last_valid, t_input_list **traverse)
{
	t_input_list	*temp;

	temp = (*traverse)->next;
	if ((*last_valid) != 0 && ((*last_valid)->name == 0
			|| ft_strncmp((*last_valid)->name, "inv", 3) == 0))
		(*last_valid) = (*last_valid)->next;
	else
		(*last_valid)->next = temp;
	free((*traverse)->name);
	free((*traverse)->object);
	free((*traverse));
	(*traverse) = temp;
}

void	handle_default_node(t_input_list **last_valid, t_input_list **traverse)
{
	if ((*traverse)->next != 0 && (*traverse)->next->name != 0
		&& ft_strncmp((*traverse)->next->name, "inv", 3 != 0))
		(*last_valid) = (*traverse)->next;
	else
		(*last_valid) = (*traverse);
	(*traverse) = (*traverse)->next;
}

void	final_prepare_input(t_minirt *minirt)
{
	t_input_list	*traverse;
	t_input_list	*last_valid;
	t_input_list	*first_valid;

	traverse = minirt->input_head;
	last_valid = traverse;
	first_valid = get_first_valid_node(minirt->input_head);
	while (traverse != NULL)
	{
		if (traverse != NULL && traverse->name == NULL)
			handle_null_node(&last_valid, &traverse);
		else if (traverse != NULL && ft_strncmp(traverse->name, "inv", 3) == 0)
			handle_in_node(&last_valid, &traverse);
		else
			handle_default_node(&last_valid, &traverse);
	}
	minirt->input_head = first_valid;
	check_esentials(minirt);
}

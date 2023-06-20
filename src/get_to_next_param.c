/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_to_next_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkukhale <lkukhale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:15:40 by lkukhale          #+#    #+#             */
/*   Updated: 2023/06/05 18:16:18 by lkukhale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	jump_spaces(const char *line, int i)
{
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (-1);
	return (i);
}

int	jump_non_spaces(const char *line, int i)
{
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (-1);
	return (i);
}

int evaluator(t_input_list *input, int i)
{
	if (i < 0)
	{
		free(input->name);
		input->name = ft_strdup("inv");
		return (1);
	}
	else
		return (0);
}

int get_to_next_param(const char *line, int i, t_input_list *input)
{
	if (i == 0)
	{
		i = jump_spaces(line, i);
		if (evaluator(input, i) == 1)
			return (-1);
	}
	i = jump_non_spaces(line, i);
	if (evaluator(input, i) == 1)
		return (-1);
	i = jump_spaces(line, i);
	if (evaluator(input, i) == 1)
		return (-1);
	return (i);
}
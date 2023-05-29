/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beaudibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:48:46 by beaudibe          #+#    #+#             */
/*   Updated: 2022/11/17 18:23:08 by beaudibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Gnl work by putting buf at the end of mem_line and then analyzing if it	*/
/*contains \n if there's one it will put the string until \n (included) in	*/
/*line then remove all the element before in mem_line. Else it will read a	*/
/*new buff until finding a \n or EOF										*/

static int	ft_strclen(char *s, char c)
{
	int	i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	if (c == 0)
		return (i);
	return (-1);
}

static char	*ft_find_n(char **mem_line, char *temp, char *buff, int len_mem)
{
	len_mem = ft_strclen(*mem_line, '\n');
	if (!*mem_line)
		return (0);
	if (len_mem == -1)
	{
		temp = ft_strdup(*mem_line);
		if (!temp)
			return (0);
		free(*mem_line);
		*mem_line = 0;
		return (temp);
	}
	buff = ft_substr(*mem_line, 0, len_mem + 1);
	if (len_mem + 1 == (int) ft_strlen(*mem_line))
	{
		free(*mem_line);
		*mem_line = 0;
		return (buff);
	}
	temp = ft_substr(*mem_line, len_mem + 1, ft_strlen(*mem_line) - len_mem);
	free(*mem_line);
	*mem_line = malloc(ft_strlen(temp) + 1);
	ft_strlcpy(*mem_line, temp, ft_strlen(temp) + 1);
	free(temp);
	return (buff);
}

static char	*ft_add_buff(char *mem_line, char *buff, char *temp, int len_read)
{
	int	len_mem;

	if (!mem_line)
		mem_line = ft_strdup(buff);
	else
	{
		len_mem = ft_strlen(mem_line) + 1;
		temp = malloc(len_read + len_mem);
		if (!temp)
		{
			free(buff);
			return (0);
		}
		ft_strlcpy(temp, mem_line, len_mem);
		ft_strlcat(temp, buff, len_read + len_mem);
		free(mem_line);
		mem_line = ft_strdup(temp);
		free(temp);
	}
	if (!mem_line)
	{
		free(buff);
		return (0);
	}
	return (mem_line);
}

char	*get_next_line(int fd)
{
	static char	*mem_line[1025];
	char		*buff;
	int			len_read;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	while (ft_strclen(mem_line[fd], '\n') == -1)
	{
		len_read = read(fd, buff, BUFFER_SIZE);
		if (!len_read)
			break ;
		if (len_read == -1)
		{
			free(buff);
			return (0);
		}
		buff[len_read] = 0;
		mem_line[fd] = ft_add_buff(mem_line[fd], buff, 0, len_read);
		if (!mem_line[fd])
			return (0);
	}
	free(buff);
	return (ft_find_n(&mem_line[fd], 0, buff, 0));
}

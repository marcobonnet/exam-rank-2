/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:08:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/26 11:06:31 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *remains, char *buffer)
{
	char			*array;
	unsigned int	size;
	int				i;
	int				j;

	if (!remains && !buffer)
		return (NULL);
	size = ft_strlen(remains) + ft_strlen(buffer);
	if (!(array = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	j = 0;
	if (remains)
	{
		while (remains[i])
		{
			array[j] = remains[i];
			i++;
			j++;
		}
		i = 0;
	}
	while (buffer[i])
	{
		array[j] = buffer[i];
		i++;
		j++;
	}
	array[size] = '\0';
	free((void *)remains);
	return (array);
}

char*push_line(char *remains)
{
	int		i;
	char	*array;

	i = 0;
	while (remains[i] && remains[i] != '\n')
		i++;
	if (!(array = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (remains[i] && remains[i] != '\n')
	{
		array[i] = remains[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*cut_next_line(char *remains)
{
	int		i;
	int		j;
	char	*array;

	i = 0;
	j = 0;
	while (remains[i] && remains[i] != '\n')
		i++;
	if (remains[i])
	{
		free(remains);
		return (NULL);
	}
	if (!(array = (char *)malloc(sizeof(char) * (ft_strlen(remains)- i + 1))))
		return (NULL);
	i++;
	while (remains[i])
	{
		array[j] = remains[i];
		j++;
		i++;
	}
	array[j] = '\0';
	free(remains);
	return (array);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*remains;
	static int	fin = 0;
	int			count;
	char		*line;

	count = 1;
	if (fin == 1)
		return (NULL);
	while (buffer[0] != '\n' && count != 0)
	{
		if ((count = read(fd, buffer, BUFFER_SIZE)) == -1)
			return (NULL);
		buffer[count] = '\0';
		remains = ft_strjoin(remains, buffer);
	}
	line = push_line(remains);
	remains = cut_next_line(remains);
	if (count == 0)
		fin = 1;
	return (line);
}

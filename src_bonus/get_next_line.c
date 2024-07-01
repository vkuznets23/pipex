/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:27:15 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/01 13:57:26 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#define BUFFER_SIZE 100

static char	*free_and_return(char *str, char *ret_val)
{
	free(str);
	return (ret_val);
}

static char	*copy_from_newline(char *str)
{
	int		i;
	int		j;
	char	*string_2;

	i = 0;
	j = 0;
	if (!*str || !str)
		return (free_and_return(str, NULL));
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	string_2 = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!string_2)
		return (free_and_return(str, NULL));
	while (str[i] != '\0')
		string_2[j++] = str[i++];
	string_2[j] = '\0';
	if (!*string_2)
	{
		free(str);
		free(string_2);
		return (NULL);
	}
	return (free_and_return(str, string_2));
}

static char	*copy_untl_newline(char *str)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	if (!str || *str == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	string = (char *)malloc(sizeof(char) * i + 1);
	if (!string)
		return (NULL);
	while (j < i)
	{
		string[j] = str[j];
		j++;
	}
	string[j] = '\0';
	return (string);
}

static char	*reading_function(char *str, int fd)
{
	int		b_bytes;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	b_bytes = 1;
	while (b_bytes != 0 && !ft_strchr(str, '\n'))
	{
		b_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[b_bytes] = '\0';
		str = ft_my_strjoin(str, buffer);
		if (!str)
			return (free_and_return(buffer, NULL));
	}
	return (free_and_return(buffer, str));
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = reading_function(str, fd);
	if (!str)
		return (NULL);
	line = copy_untl_newline(str);
	if (!line)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = copy_from_newline(str);
	return (line);
}

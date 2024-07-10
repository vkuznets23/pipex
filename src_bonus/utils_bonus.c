/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:27:15 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/01 15:42:42 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_my_strjoin(char *str, char *buffer)
{
	size_t	str_len;
	char	*d;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_len = 0;
	if (!str && !buffer)
		return (NULL);
	if (str)
		str_len = ft_strlen(str);
	d = (char *)malloc(sizeof(char) * ((ft_strlen(buffer) + str_len + 1)));
	if (!d)
		return (free(str), NULL);
	while (str && str[i])
	{
		d[i] = str[i];
		i++;
	}
	while (buffer && buffer[j])
		d[i++] = buffer[j++];
	d[i] = '\0';
	return (free(str), d);
}

/*void	my_dup_bonus(int *old_fd, int *new_fd)
{
	close(new_fd[0]);
	if (dup2(old_fd[0], 0) == -1)
	{
		close(old_fd[0]);
		close(new_fd[1]);
		error_handler(NULL, 7, 1);
	}
	if (dup2(new_fd[1], 1) == -1)
	{
		close(old_fd[0]);
		close(new_fd[1]);
		error_handler(NULL, 7, 1);
	}
	close(old_fd[0]);
	close(old_fd[1]);
}*/

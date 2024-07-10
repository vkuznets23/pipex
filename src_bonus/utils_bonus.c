/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:27:15 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/10 16:35:10 by vkuznets         ###   ########.fr       */
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

int	ft_cmd_nums(t_pipex *data)
{
	int	num_cmd;

	if (ft_strncmp("here_doc", data->av[1], 9) == 0)
		num_cmd = data->ac - 4;
	else
		num_cmd = data->ac - 3;
	return (num_cmd);
}

void	ft_here_doc(t_pipex *data, int *p_fd, pid_t *pid)
{
	if (data->ac < 6)
	{
		free(pid);
		error_handler(NULL, 4, 1);
	}
	here_doc_func(data, p_fd, pid);
}

pid_t	*ft_malloc_cmds(t_pipex *data)
{
	int		num_cmd;
	pid_t	*pid;

	num_cmd = ft_cmd_nums(data);
	pid = malloc(num_cmd * sizeof(pid_t));
	if (!pid)
		error_handler(NULL, 8, 1);
	return (pid);
}

void	ft_piping(int *p_fd, pid_t *pid)
{
	if (pipe(p_fd) == -1)
	{
		free(pid);
		error_handler(NULL, 5, 1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:10:13 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/27 13:46:19 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	initilize_data(char **av, char **envp, int ac, t_pipex *data)
{
	data->av = av;
	data->envp = envp;
	data->ac = ac;
}

void	my_dup2(int fd_from, int fd_to, int p_fd_from, int p_fd_to)
{
	dup2(fd_from, fd_to);
	dup2(p_fd_from, p_fd_to);
	close(p_fd_from);
	close(fd_from);
}

static int	space_checker(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	if (cmd[i] == '\0')
		return (0);
	while (cmd)
	{
		if (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n')
			i++;
		if (i == len)
			return (1);
	}
	return (0);
}

void	exec(char *cmd, char **envp)
{
	char	*path_to_cmd;
	char	**s_cmd;
	int	flag;

	flag = 0;
	if (space_checker(cmd) == 1)
		flag = 1;
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		exit(1);
	if (!*s_cmd && flag == 0)
		error_handler(*s_cmd, 2, 127);
	if (!*s_cmd && flag == 1)
		error_handler(*s_cmd, 3, 127);
	path_to_cmd = get_path(s_cmd, envp);
	if (execve(path_to_cmd, s_cmd, envp) == -1)
		error_handler_func(s_cmd, 3, 0);
}

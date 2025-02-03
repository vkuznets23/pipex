/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:10:13 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/11 14:17:00 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	initilize_data(char **av, char **envp, int ac, t_pipex *data)
{
	data->av = av;
	data->envp = envp;
	data->ac = ac;
	data->i = 0;
}

void	my_dup2(int fd_from, int fd_to, int p_fd_from, int p_fd_to)
{
	if (dup2(fd_from, fd_to) == -1)
	{
		close(fd_from);
		close(p_fd_from);
		error_handler(NULL, 7, 1);
	}
	if (dup2(p_fd_from, p_fd_to) == -1)
	{
		close(fd_from);
		close(p_fd_from);
		error_handler(NULL, 7, 1);
	}
	close(p_fd_from);
	close(fd_from);
}

static void	space_checker(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (cmd[0] == '\0')
		error_handler(cmd, 3, 126);
	if (cmd[0] == ' ' || (cmd[0] >= 9 && cmd[0] <= 13))
		error_handler(cmd, 3, 127);
	if (cmd[len -1] == ' ' || (cmd[len - 1] >= 9 && cmd[len - 1] <= 13))
		error_handler(cmd, 3, 127);
}

void	exec(char *cmd, char **envp)
{
	char	*path_to_cmd;
	char	**s_cmd;

	space_checker(cmd);
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		exit(1);
	if (!*s_cmd)
		error_handler(*s_cmd, 2, 127);
	path_to_cmd = get_path(s_cmd, envp);
	if (execve(path_to_cmd, s_cmd, envp) == -1)
		error_handler_func(s_cmd, 3, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/01 15:33:09 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	last_child(int *p_fd, t_pipex *data)
{
	int	fd;

	fd = open(data->av[data->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (access(data->av[data->ac - 1], W_OK) == -1)
		error_handler(data->av[data->ac - 1], 2, 1);
	if (fd == -1)
		error_handler(data->av[data->ac - 1], 1, 1);
	my_dup2(fd, 1, p_fd[0], 0);
	close(p_fd[1]);
	exec(data->av[data->ac - 2], data->envp);
}

void	last_child_fork(t_pipex *data, int *p_fd, pid_t *pid)
{
	pid[data->i] = fork();
	if (pid[data->i] < 0)
		error_handler(NULL, 6, 1);
	if (pid[data->i] == 0)
		last_child(p_fd, data);
	close(p_fd[0]);
}

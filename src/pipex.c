/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/10 15:40:39 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	ft_child_process(int *p_fd, t_pipex *data)
{
	int	fd;

	if (access(data->av[1], F_OK) == -1)
		error_handler(data->av[1], 1, 1);
	if (access(data->av[1], R_OK) == -1)
		error_handler(data->av[1], 2, 1);
	fd = open(data->av[1], O_RDONLY);
	if (fd == -1)
		error_handler(data->av[1], 2, 1);
	my_dup2(fd, 0, p_fd[1], 1);
	close(p_fd[0]);
	exec(data->av[2], data->envp);
}

static void	ft_second_fork(t_pipex *data, int *p_fd, pid_t *pid)
{
	int		fd;

	*pid = fork();
	if (*pid < 0)
		error_handler(NULL, 6, 1);
	if (*pid == 0)
	{
		fd = open(data->av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (access(data->av[4], W_OK) == -1)
			error_handler(data->av[4], 2, 1);
		if (fd == -1)
			error_handler(data->av[4], 1, 1);
		my_dup2(fd, 1, p_fd[0], 0);
		close(p_fd[1]);
		exec(data->av[3], data->envp);
	}
	close(p_fd[0]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	pid_t	pid[2];
	int		p_fd[2];
	int		error;

	if (ac != 5)
		error_handler(NULL, 4, 1);
	initilize_data(av, envp, ac, &data);
	if (pipe(p_fd) == -1)
		error_handler(NULL, 5, 1);
	pid[0] = fork();
	if (pid[0] < 0)
		error_handler(NULL, 6, 1);
	if (pid[0] == 0)
		ft_child_process(p_fd, &data);
	close(p_fd[1]);
	ft_second_fork(&data, p_fd, &pid[1]);
	waitpid(pid[0], &error, 0);
	waitpid(pid[1], &error, 0);
	exit(WEXITSTATUS(error));
}

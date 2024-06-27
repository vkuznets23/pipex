/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/27 14:02:57 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int *p_fd, t_pipex *data)
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

static void	ft_second_fork(t_pipex *data, int *p_fd)
{
	pid_t	pid;
	int	error;
	int	fd;

	pid = fork();
	if (pid < 0)
		error_handler(NULL, 6, 1);
	if (pid == 0)
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
	waitpid(pid, &error, 0);
	close(p_fd[0]);
	error = (error & 0xff00) >> 8;
	exit(error);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	pid_t	pid;
	int	p_fd[2];

	if (ac != 5)
		error_handler(NULL, 4, 1);
	initilize_data(av, envp, ac, &data);
	if (pipe(p_fd) == -1)
		error_handler(NULL, 5, 1);
	pid = fork();
	if (pid < 0)
		error_handler(NULL, 6, 1);
	if (pid == 0)
		child_process(p_fd, &data);
	close(p_fd[1]);
	ft_second_fork(&data, p_fd);
}

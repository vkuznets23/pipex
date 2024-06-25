/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/24 14:29:13 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec(char *cmd, char **envp)
{
	char	*path_to_cmd;
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		exit(1);
	if (!*s_cmd)
		error_handler(*s_cmd, 2, 127);
	path_to_cmd = get_path(s_cmd, envp);
	if (execve(path_to_cmd, s_cmd, envp) == -1)
		error_handler_func(s_cmd, 3, 0);
}

static void	my_dup2(int fd_from, int fd_to, int p_fd_from, int p_fd_to, int p_fd)
{
	dup2(fd_from, fd_to);
	dup2(p_fd_from, p_fd_to);
	close(p_fd);
	close(p_fd_from);
	close(fd_from);
	/*dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);//we dont use it
	close(p_fd[1]);//we don´t need it anymore
	close(fd);*/
	/*dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	close(fd);
	close(p_fd[0]);*/
}

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
	my_dup2(fd, 0, p_fd[1], 1, p_fd[0]);
	exec(data->av[2], data->envp);
}

static void	second_child(int *p_fd, t_pipex *data)
{
	int	fd;

	fd = open(data->av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (access(data->av[4], W_OK) == -1)
		error_handler(data->av[4], 2, 1);
	if (fd == -1)
		error_handler(data->av[4], 1, 1);
	my_dup2(fd, 1, p_fd[0], 0, p_fd[1]);
	exec(data->av[3], data->envp);
}

static void	ft_second_fork(t_pipex *data, int *p_fd)
{
	pid_t pid;
	int error;

	pid = fork();
	if (pid < 0)
	{
		perror("fork: ");
		exit(1);
	}
	if (pid == 0)
		second_child(p_fd, data);
	waitpid(pid, &error, 0);
	close(p_fd[0]);
	error = (error & 0xff00) >> 8;
	exit(error);
}

int	main(int ac, char **av, char **envp)
{
	int	p_fd[2];
	pid_t	pid;
	t_pipex data;

	if (ac != 5)
	{
		error_options(4);
		exit (1);
	}
	initilize_data(av, envp, ac, &data);
	if (pipe(p_fd) == -1)
	{
		perror("pipe: ");
		exit(1)
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork: ");
		exit(1);
	}
	if (pid == 0)
		child_process(p_fd, &data);
	close(p_fd[1]);//we read from the pipe
	ft_second_fork(&data, p_fd);//o execut the 2nd cmd
}

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

static void	child_process(char **av, int *p_fd, char **envp)
{
	int	fd;

	if (access(av[1], F_OK) == -1)
		error_handler(av[1], 1, 1);
	if (access(av[1], R_OK) == -1)
		error_handler(av[1], 2, 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_handler(av[1], 2, 1);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);//we dont use it
	close(p_fd[1]);//we don´t need it anymore
	close(fd);
	exec(av[2], envp);
}

static void	second_child(char **av, int *p_fd, char **envp)
{
	int	fd;

	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (access(av[4], W_OK) == -1)
		error_handler(av[4], 2, 1);
	if (fd == -1)
		error_handler(av[4], 1, 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	close(fd);
	close(p_fd[0]);
	exec(av[3], envp);
}

static void	ft_second_fork(char **av, char **envp, int *p_fd)
{
	pid_t pid;
	int error;

	pid = fork();
	if (pid < 0)
	{
		perror("fork: ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		second_child(av, p_fd, envp);
	//maybe close something??
	waitpid(pid, &error, 0);
	close(p_fd[0]);
	error = (error & 0xff00) >> 8;
	exit(error);
}

int	main(int ac, char **av, char **envp)
{
	int	p_fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		if (ac < 5)
			ft_putstr_fd("pipex: not enough arguments\n", 2);
		else
			ft_putstr_fd("pipex: too many arguments\n", 2);
		exit (1);
	}
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork: ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process(av, p_fd, envp);
	close(p_fd[1]);//we read from the pipe
	ft_second_fork(av, envp, p_fd);//o execut the 2nd cmd
}

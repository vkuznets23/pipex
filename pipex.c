/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/18 16:37:13 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handler(char *cmd1, int error)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd1, 2);
	if (error == 1)
		ft_putstr_fd(": No such file or directory", 2);
	else if (error == 2)
		ft_putstr_fd(": Permission denied", 2);
	else if (error == 3)
		ft_putstr_fd(": Command not found", 2);
	exit(1);
}

static void	exec(char  *cmd, char **envp)
{
	char	*path_to_cmd;
	char 	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		exit(1);
	if(!*s_cmd)
		error_handler(cmd, 3); 
	path_to_cmd = get_path(s_cmd, envp);
	if (path_to_cmd) 
	{
        execve(path_to_cmd, s_cmd, envp);
        perror("execve");
    } 
	else 
        perror("Command not found");
	free_func(s_cmd);
	exit(EXIT_FAILURE);
}

static void	child_process(char **av, int *p_fd, char **envp) //f1, cmd1
{
	int fd;
	if (access(av[1], F_OK) == -1)
		error_handler(av[1], 1);
	if (access(av[1], R_OK) == -1)
		error_handler(av[1], 2);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_handler(av[1], 2);
	dup2(fd, 0); //STDIN_FILENO
	dup2(p_fd[1], 1);//STDOUT_FILENO
	close(p_fd[0]); // always close the p_fd of the pipe you don't use
	exec(av[2], envp);
}

static void	parent_process(char **av, int *p_fd, char **envp)//f2, cmd2
{
	int status;
	int	fd;

	fd  = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (access(av[4], W_OK) == -1)
		error_handler(av[4], 2);
	if (fd == -1)
		error_handler(av[4], 1);
	waitpid(-1, &status, 0);//this should be somewere!!
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], envp);
}

int main(int ac, char **av, char **envp)
{
	int		p_fd[2];
	pid_t	pid;
	if (ac != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit (1);
	}
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	//crete child process
	pid = fork();
	if (pid < 0)
	{
		perror("fork: ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) //if returns 0 we are in child process
		child_process(av, p_fd,envp);
	else
		parent_process(av, p_fd,envp);
}

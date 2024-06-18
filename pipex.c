/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:00:49 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/14 14:03:47 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec(char  *cmd, char **envp)
{
	char	*path_to_cmd;
	char 	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	path_to_cmd = get_path(s_cmd[0], envp);
	//hz if i need it
	if (path_to_cmd) {
        execve(path_to_cmd, s_cmd, envp);
        perror("execve");
        free(path_to_cmd);
        free_func(s_cmd);
        exit(EXIT_FAILURE);
    } else {
        perror("Command not found");
        free_func(s_cmd);
        exit(EXIT_FAILURE);
    }
}

static void	child_process(char **av, int *p_fd, char **envp) //f1, cmd1
{
	int fd;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		perror("Reading error");
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
	if (fd == -1)
		perror("Writing error");
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
		return (1);
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);// it means error
	}
	//crete child process
	pid = fork();
	if (pid < 0)
	{
		perror("fork: ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)//if returns 0 we are in child process
		child_process(av, p_fd,envp);
	else
		parent_process(av, p_fd,envp);
}

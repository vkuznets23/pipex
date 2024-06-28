/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_experiment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/28 16:09:03 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

static void	middle_child(int *old_fd, t_pipex *data, int cmd_num)
{
	pid_t	pid;
	int		new_fd[2];

	if (pipe(new_fd) == -1)
		error_handler(NULL, 5, 1);
	pid = fork();
	if (pid < 0)
		error_handler(NULL, 6, 1);
	if (pid == 0)
	{
		close(new_fd[0]);
		dup2(old_fd[0], 0);
		dup2(new_fd[1], 1);
		close(old_fd[0]);
		close(old_fd[1]);
		exec(data->av[cmd_num], data->envp);
	}
	close(new_fd[1]);
	waitpid(pid, NULL, 0);
	if (cmd_num < data->ac - 3)
		middle_child(new_fd, data, cmd_num + 1);
	else
		last_child_fork(data, new_fd);
}

static void	here_doc_func(t_pipex *data, int *p_fd)//what a fuck???
{
	pid_t	pid;
	char	*hd_text;


	if (pipe(p_fd) == -1)
		error_handler(NULL, 5, 1);
	pid = fork();
	if (pid < 0)
		error_handler(NULL, 6, 1);
	if (pid == 0)
	{
		close(p_fd[0]);
		while (1)
		{
			hd_text = get_next_line(0);
			if (ft_strncmp(hd_text, data->av[2], ft_strlen(data->av[2])) == 0)
			{
				free(hd_text);
				close (p_fd[1]);
				exit (1);
			}
			ft_putstr_fd(hd_text, p_fd[1]);
			free(hd_text);
		}
	}
	close(p_fd[1]);
	middle_child(p_fd, data, 3);
	waitpid(pid, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;
	t_pipex	data;
	int		p_fd[2];

	if (ac < 5)
		error_handler(NULL, 4, 1);
	initilize_data(av, envp, ac, &data);
	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		if (ac < 6)
			error_handler(NULL, 4, 1);
		here_doc_func(&data, p_fd);
	}
	if (pipe(p_fd) == -1)
		error_handler(NULL, 5, 1);
	pid = fork();
	if (pid < 0)
		error_handler(NULL, 6, 1);
	if (pid == 0)
		child_process(p_fd, &data);
	close(p_fd[1]);
	if (ac - 3 > 2)
		middle_child(p_fd, &data, 3);
	else
		last_child_fork(&data, p_fd);
}

//line 65: create a pipe for the first process 
//line 67: fork for the first child process

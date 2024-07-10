/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/01 16:14:46 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	here_doc_reading(t_pipex *data, int *p_fd)
{
	char	*hd_text;
	char	*stop_word;

	stop_word = ft_strjoin(data->av[2], "\n");
	while (1)
	{
		hd_text = get_next_line(0);
		if (ft_strncmp(hd_text, stop_word, ft_strlen(stop_word)) == 0)		
		{
			free(hd_text);
			free(stop_word);
			close (p_fd[0]);
			exit (1);
		}
		ft_putstr_fd(hd_text, p_fd[1]);
		free(hd_text);
	}
}

static void	here_doc_func(t_pipex *data, int *p_fd, pid_t *pid)
{
	if (pipe(p_fd) == -1)
		error_handler(NULL, 5, 1);
	pid[data->i] = fork();
	if (pid[data->i] < 0)
		error_handler(NULL, 6, 1);
	if (pid[data->i] == 0)
	{
		close(p_fd[0]);
		here_doc_reading(data, p_fd);
	}
	waitpid(pid[data->i], NULL, 0);
	close(p_fd[1]);

}

int	ft_cmd_nums(t_pipex *data)
{
	int	num_cmd;

	if (ft_strncmp("here_doc", data->av[1], 9) == 0)
		num_cmd = data->ac - 4;
	else
		num_cmd = data->ac - 3;
	return (num_cmd);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	*pid;
	t_pipex	data;
	int		p_fd[2];
	int		num_cmd;
	int		error;
	int		j;

	if (ac < 5)
		error_handler(NULL, 4, 1);
	initilize_data(av, envp, ac, &data);
	num_cmd = ft_cmd_nums(&data);
	pid = malloc(num_cmd * sizeof(pid_t));
	if (!pid)
		error_handler("malloc failure", 4, 1);
	if (pipe(p_fd) == -1)
	{
		free(pid);
		error_handler(NULL, 5, 1);
	}
	if (ft_strncmp("here_doc", av[1], 9) == 0)
	{
		if (ac < 6)
		{
			free(pid);
			error_handler(NULL, 4, 1);
		}
		here_doc_func(&data, p_fd, pid);
	}
	else
		child_process(&data, p_fd, pid);
	data.i++;
	if (ac - 3 > 2)
		middle_child(p_fd, &data, 3, pid);
	else
		last_child_fork(&data, p_fd, pid);
	j = 0;
	while (j <= data.i)
	{
		waitpid(pid[j], &error, 0);
		j++;
	}
	exit(WEXITSTATUS(error));
}

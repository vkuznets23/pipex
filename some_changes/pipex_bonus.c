/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/03 17:23:41 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	middle_child(int *old_fd, t_pipex *data, int cmd_num, pid_t *pid)
{
	int		new_fd[2];

	if (pipe(new_fd) == -1)
		error_handler(NULL, 5, 1);
	*pid = fork();
	if (*pid < 0)
	{
		close(new_fd[1]);
		close(old_fd[0]);
		error_handler(NULL, 6, 1);
	}
	if (*pid == 0)
	{
		close(new_fd[0]);
		my_dup2(old_fd[0], 0, new_fd[1], 1);
		close(old_fd[1]);
		exec(data->av[cmd_num], data->envp);
	}
}

static int number_of_cmds(t_pipex *data)
{
	int	num_cmd;

	if (ft_strncmp("here_doc", data->av[1], 9) == 0)
		num_cmd = data->ac - 4;
	else
		num_cmd = data->ac - 3;
	return(num_cmd);
}

int	main(int ac, char **av, char **envp)
{
	pid_t	*pid;
	t_pipex	data;
	int		p_fd[2];
	int		num_cmd;
	int		i;
	int		error;

	if (ac < 5)
		error_handler(NULL, 4, 1);
	initilize_data(av, envp, ac, &data);
	num_cmd = number_of_cmds(&data);
	pid = malloc(num_cmd * sizeof(pid_t));
	i = 1;
	if (!pid)
        error_handler("malloc failed", 1, 1);
	if (ft_strncmp("here_doc", av[1], 9) == 0)
	{
		if (ac < 6)
			error_handler(NULL, 1, 1);
		here_doc_func(&data, p_fd, &pid[i]);
		i++;
	}
	else
	{
		if (pipe(p_fd) == -1)
			error_handler(NULL, 5, 1);
		first_child_fork(&data, p_fd, &pid[0]);
	}
	if (num_cmd > 2)
	{
			while(i < num_cmd - 2)
			{
				middle_child(p_fd, &data, i + 3, &pid[i]);
				i++;
			}
	}
	last_child_fork(&data, p_fd, &pid[num_cmd - 1]);
	while(i >= 0)
	{
		waitpid(pid[i], &error, 0);
		i--;
	}
	free(pid);
	exit(WEXITSTATUS(error));
}

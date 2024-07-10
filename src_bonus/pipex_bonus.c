/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:06:23 by vkuznets          #+#    #+#             */
/*   Updated: 2024/07/10 16:31:11 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	pid_t	*pid;
	t_pipex	data;
	int		p_fd[2];
	int		error;
	int		j;

	if (ac < 5)
		error_handler(NULL, 4, 1);
	initilize_data(av, envp, ac, &data);
	pid = ft_malloc_cmds(&data);
	ft_piping(p_fd, pid);
	if (ft_strncmp("here_doc", av[1], 9) == 0)
		ft_here_doc(&data, p_fd, pid);
	else
		child_process(&data, p_fd, pid);
	data.i++;
	if (ac - 3 > 2)
		middle_child(p_fd, &data, 3, pid);
	else
		last_child_fork(&data, p_fd, pid);
	j = 0;
	while (j++ <= data.i)
		waitpid(pid[j], &error, 0);
	free(pid);
	exit(WEXITSTATUS(error));
}

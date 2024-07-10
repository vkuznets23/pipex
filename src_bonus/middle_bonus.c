

#include "../pipex.h"

void	middle_child(int *old_fd, t_pipex *data, int cmd_num, pid_t *pid)
{
	int		new_fd[2];

	if (pipe(new_fd) == -1)
		error_handler(NULL, 5, 1);
	pid[data->i] = fork();
	if (pid[data->i] < 0)
		error_handler(NULL, 6, 1);
	if (pid[data->i] == 0)
	{
		close(new_fd[0]);
		my_dup2(old_fd[0], 0, new_fd[1], 1);
		exec(data->av[cmd_num], data->envp);
	}
	close(new_fd[1]);
	close(old_fd[0]);
	data->i++;
	if (cmd_num < data->ac - 3)
		middle_child(new_fd, data, cmd_num + 1, pid);
	else
		last_child_fork(data, new_fd, pid);
}

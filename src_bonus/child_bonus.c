

#include "../pipex.h"



 /*void	child_process(int *p_fd, t_pipex *data)
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
}*/

static void	fork_child_process(int *p_fd, t_pipex *data)
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

void	child_process(t_pipex *data, int *p_fd, pid_t *pid)
{
	pid[data->i] = fork();
	if (pid[data->i] < 0)
		error_handler(NULL, 6, 1);
	if (pid[data->i] == 0)
		fork_child_process(p_fd, data);
	close(p_fd[1]);
}

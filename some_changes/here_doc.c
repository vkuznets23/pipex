void	here_doc_reading(t_pipex *data, int *p_fd)
{
	char	*hd_text;

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

void	here_doc_func(t_pipex *data, int *p_fd)
{
	pid_t	pid;

	if (pipe(p_fd) == -1)
		error_handler(NULL, 5, 1);
	pid = fork();
	if (pid < 0)
		error_handler(NULL, 6, 1);
	if (pid == 0)
	{
		close(p_fd[0]);
		here_doc_reading(data, p_fd);
	}
	close(p_fd[1]);
	waitpid(pid, NULL, 0);
	middle_child(p_fd, data, 3);
}
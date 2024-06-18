/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd_thingy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:49:02 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/14 16:58:41 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_func(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_envp(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (&envp[i][5]);
	}
	return (0);
}

char	*get_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	**s_cmd;
	char	*path_part;
	char	*path_to_cmd;
	int		i;

	i = -1;
	s_cmd = ft_split(cmd, ' ');//i can have several cmds
	all_paths = ft_split(get_envp(envp), ':');
	while (all_paths[++i])
	{
		path_part = ft_strjoin(all_paths[i], "/");
		path_to_cmd = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(path_to_cmd, F_OK | X_OK) == 0)
		{
			free_func(s_cmd);
			return (path_to_cmd);
		}
		free(path_to_cmd);
	}
	free_func(all_paths);
	free_func(s_cmd);
	return (cmd);
}

/*int main(int ac, char **av, char **envp)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = get_path(av[1], envp);
	printf("%s\n", cmd);
	while (cmd[i])
	{
		printf("%s\n", cmd[i]);
		i++;
	}
	//printf("%s\n", get_envp(envp));

}*/

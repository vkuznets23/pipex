/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuznets <vkuznets@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:29:05 by vkuznets          #+#    #+#             */
/*   Updated: 2024/06/19 11:00:40 by vkuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_options(int error)
{
	if (error == 1)
		ft_putstr_fd("no such file or directory: ", 2);
	else if (error == 2)
		ft_putstr_fd("permission denied: ", 2);
	else if (error == 3)
		ft_putstr_fd("command not found: ", 2);
}
void	error_handler(char *cmd, int error)
{
	ft_putstr_fd("pipex: ", 2);
	error_options(error);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	error_handler_func(char **cmd, int error)
{
	ft_putstr_fd("pipex: ", 2);
	error_options(error);
	ft_putstr_fd(*cmd, 2);
	ft_putstr_fd("\n", 2);
	free_func(cmd);
}

void	malloc_failure(char **ar1, char **ar2)
{
	free_func(ar1);
	free_func(ar2);
	exit(1);
}

void	free_func(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:23:28 by hlindeza          #+#    #+#             */
/*   Updated: 2024/01/22 21:42:03 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*join_path_and_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

char	*find_cmd_in_path(char **path_values, char *cmd)
{
	int		i;
	char	*actual_path;

	i = -1;
	while (path_values[++i])
	{
		actual_path = join_path_and_cmd(path_values[i], cmd);
		if (!access(actual_path, F_OK | X_OK))
			return (actual_path);
		free(actual_path);
	}
	return (NULL);
}

char	*get_cmdpath(char *cmd)
{
	char	**path_values;
	char	*actual_path;
	char	*getenv;

	getenv = ft_getenv("PATH", mini()->env);
	if (getenv)
	{
		if (ft_strchr(cmd, '/') && (!access(cmd, F_OK | X_OK)))
		{
			free(getenv);
			return (cmd);
		}
		path_values = ft_split(getenv, ':');
		actual_path = find_cmd_in_path(path_values, cmd);
		free_matriz(&path_values);
		free(getenv);
		return (actual_path);
	}
	return (NULL);
}

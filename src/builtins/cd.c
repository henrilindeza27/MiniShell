/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:26:12 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 17:14:01 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pwd_update(char ***env, char *path)
{
	char	*content;

	content = ft_strjoin("PWD=", path);
	ft_export(env, content);
	free(content);
}

void	oldpwd_update(char ***env, char *path)
{
	char	*content;

	if (!path)
		return ;
	content = ft_strjoin("OLDPWD=", path);
	ft_export(env, content);
	free(content);
}

void	go_dir(char *path, char ***env)
{
	char	*curr_path;
	char	*temp;

	temp = ft_getenv("PWD", *env);
	if (chdir(path) == -1)
	{
		ft_printf("SillyShell😿: cd: no such file or directory\n");
		mini()->status = 1;
		free(temp);
		return ;
	}
	curr_path = getcwd(NULL, 0);
	if (curr_path)
	{
		oldpwd_update(env, temp);
		pwd_update(env, curr_path);
		free(curr_path);
	}
	free(temp);
}

void	go_old_pwd(char ***env)
{
	char	*path;

	path = ft_getenv("OLDPWD", *env);
	if (!path)
	{
		ft_printf("SillyShell😿: cd: OLDPWD not set\n");
		mini()->status = 1;
		return ;
	}
	go_dir(path, env);
	free(path);
}

void	ft_cd(char *dirpath)
{
	char	*home;

	home = ft_getenv("HOME", mini()->env);
	if (!dirpath)
		go_dir(home, &mini()->env);
	else if (!ft_strcmp(dirpath, "-"))
		go_old_pwd(&mini()->env);
	else
		go_dir(dirpath, &mini()->env);
	free(home);
}

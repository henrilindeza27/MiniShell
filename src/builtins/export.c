/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:05:54 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 17:48:56 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	declare_x(char **envp)
{
	char	**split;
	int		i;

	i = -1;
	while (envp[++i])
	{
		split = ft_split(envp[i], '=');
		printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		free_matriz(&split);
	}
}

void	add_new_var(char ***envp, char *content)
{
	int		i;
	char	**new;

	i = -1;
	if (!ft_strchr(content, '='))
		return ;
	new = (char **)malloc(sizeof(char *) * (len_mtz(*envp) + 2));
	if (!new)
		return ;
	while ((*envp)[++i])
		new[i] = ft_strdup((*envp)[i]);
	new[i] = ft_strdup(content);
	new[i + 1] = NULL;
	free_matriz(envp);
	*envp = new;
}

void	ft_export(char ***envp, char *content)
{
	int	i;

	if (!content)
		declare_x(*envp);
	else
	{
		i = check_in_env(content, *envp);
		if (i != -1)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(content);
		}
		else
			add_new_var(envp, content);
	}
}

int	is_valid_string(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0' || !ft_isalpha(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=' \
			&& str[i] != ':' && str[i] != '/')
			return (0);
		i++;
	}
	return (1);
}

void	ft_run_export(char **content)
{
	int	i;

	i = 1;
	if (!content[i])
		ft_export(&mini()->env, NULL);
	while (content[i])
	{
		if (is_valid_string(content[i]))
			ft_export(&mini()->env, content[i]);
		i++;
	}
}

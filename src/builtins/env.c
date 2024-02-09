/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:18:34 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 14:54:54 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**save_when_null(void)
{
	char	**new;
	char	*temp;
	char	*temp2;

	new = malloc(sizeof(char *) * 4);
	if (!new)
		return (NULL);
	temp2 = getcwd(NULL, 0);
	temp = ft_strjoin("PWD=", temp2);
	free(temp2);
	new[0] = ft_strdup(temp);
	free(temp);
	new[1] = ft_strdup("SHLVL=1");
	new[2] = ft_strdup("_=./minishell");
	new[3] = NULL;
	return (new);
}

int	handle_env_entry(char **new, int i, int *j, char **env)
{
	if (!ft_strncmp("_=", env[i], 2))
		new[(*j)++] = ft_strdup("_=./minishell");
	else if (!ft_strncmp("SHLVL=", env[i], 6))
		new[(*j)++] = shlvl();
	else if (!getenv("SHLVL"))
		new[(*j)++] = ft_strdup("SHLVL=1");
	else if (!ft_strncmp("OLDPWD=", env[i], 7))
		return (*j);
	else
		new[(*j)++] = ft_strdup(env[i]);
	return (*j);
}

char	**save_env(char **env)
{
	char	**new;
	int		i;
	int		j;

	if (!env || !*env)
		return (save_when_null());
	new = (char **)malloc(sizeof(char *) * (len_mtz(env) + 1));
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (env[++i])
		j = handle_env_entry(new, i, &j, env);
	new[j] = NULL;
	return (new);
}

char	*ft_getenv(char *var, char **env)
{
	char	*x;
	int		i;
	char	*result;

	i = -1;
	if (!var)
		return (NULL);
	x = ft_strjoin(var, "=");
	while (env[++i])
	{
		if (ft_strncmp(x, env[i], ft_strlen(x)) == 0)
		{
			result = ft_substr(env[i], ft_strlen(x), (ft_strlen(env[i])
						- ft_strlen(x)));
			free(x);
			return (result);
		}
	}
	if (x)
		free(x);
	return (NULL);
}

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:25:32 by rfontes-          #+#    #+#             */
/*   Updated: 2024/02/08 18:38:19 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_str(char **str, char **func)
{
	if (!*str)
		*str = ft_strdup("");
	if (!*str && *func)
		free(*func);
}

char	*get_var_value(char *input, int *i)
{
	int		j;
	char	*var;
	char	*env_value;

	j = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\''
		&& input[*i] != '\"' && input[*i] != '$')
		(*i)++;
	var = ft_substr(input, j, *i - j);
	env_value = ft_getenv(var, mini()->env);
	free(var);
	return (env_value);
}

void	expand_var(char **str, char *input, int *i)
{
	char	*env_value;
	char	*temp;

	env_value = get_var_value(input, i);
	temp = NULL;
	if (!*str)
		init_str(str, &env_value);
	if (env_value)
		temp = ft_strjoin(*str, env_value);
	free(env_value);
	if (temp)
	{
		free(*str);
		*str = temp;
	}
	else
	{
		free(*str);
		*str = NULL;
	}
}

void	expand_code(char **str)
{
	char	*code;
	char	*temp;

	code = ft_itoa(mini()->status);
	if (!*str)
		init_str(str, &code);
	if (code)
	{
		temp = ft_strjoin(*str, code);
		free(*str);
		free(code);
		*str = temp;
	}
}

void	ft_expander(char **str, char *input, int *i)
{
	int	dollar_count;

	(*i)++;
	if (!is_valid_char(input[*i]))
		return ;
	if (input[*i] == '?')
	{
		expand_code(str);
		return ;
	}
	dollar_count = count_dollars(input, i);
	if (dollar_count % 2 == 0)
	{
		(*i)--;
		add_dollars(str, dollar_count);
	}
	else
	{
		add_dollars(str, dollar_count - 1);
		expand_var(str, input, i);
		(*i)--;
	}
}

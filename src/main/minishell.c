/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:26:25 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 17:13:06 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_geral	*mini(void)
{
	static t_geral	mini;

	return (&mini);
}

void	init_mini(char **env)
{
	mini()->loop = 1;
	mini()->env = save_env(env);
	mini()->redir_error = 0;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argv;
	(void)argc;
	init_mini(env);
	while (mini()->loop)
	{
		ft_signal();
		input = readline(YELLOW "SillyShell😼 ▸ " RESET);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		else
		{
			free(input);
			continue ;
		}
		mini()->token = parse(input, 0);
		run(mini());
		free_everything(0, 0, 1);
		free(input);
	}
	free_everything(1, 1, 0);
	return (mini()->status);
}

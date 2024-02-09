/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:57:46 by hlindeza          #+#    #+#             */
/*   Updated: 2024/01/24 13:02:16 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		mini()->status = 130;
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_sigtemp(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", 0);
	else if (sig == SIGQUIT)
		ft_printf("Quit (core dumped)\n");
	mini()->status = 128 + sig;
}

void	ft_handler(int sig)
{
	close(mini()->here_fd[0]);
	close(mini()->here_fd[1]);
	free_everything(1, 1, 1);
	exit(128 + sig);
}

void	ft_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
}

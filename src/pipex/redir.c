/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:12:27 by hlindeza          #+#    #+#             */
/*   Updated: 2024/02/08 18:08:53 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_redir_msg(void)
{
	ft_printf("SillyShell😿: error opening file\n");
	mini()->redir_error = 1;
	mini()->status = 1;
}

void	handle_heredoc(t_token *token)

{
	token->std_in = run_heredoc(token);
	if (token->std_in == -1)
		error_redir_msg();
}

void	handle_output_redir(t_token *token, int i, int flag)
{
	if (token->std_out != -1)
		close(token->std_out);
	if (flag)
		token->std_out = open(&token->redir[i][1], O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	else
		token->std_out = open(&token->redir[i][2],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (token->std_out == -1)
		error_redir_msg();
}

void	handle_input_redir(t_token *token, int i)
{
	if (token->std_in != -1)
		close(token->std_in);
	if (access(&token->redir[i][1], F_OK) == -1)
	{
		error_redir_msg();
		return ;
	}
	token->std_in = open(&token->redir[i][1], O_RDONLY);
	if (token->std_in == -1)
		error_redir_msg();
}

void	ft_openredirs(t_token *token, int i)
{
	while (token)
	{
		i = 0;
		if (token->redir)
		{
			while (token->redir[i])
			{
				if (token->redir[i][0] == '>'
					&& !ft_isredir(token->redir[i][1]))
					handle_output_redir(token, i, 1);
				else if (token->redir[i][0] == '<'
					&& !ft_isredir(token->redir[i][1]))
					handle_input_redir(token, i);
				else if (token->redir[i][0] == '>' && token->redir[i][1] == '>')
					handle_output_redir(token, i, 0);
				else if (token->redir[i][0] == '<' && token->redir[i][1] == '<')
					add_str_to_array(&token->heredoc, &token->redir[i][2]);
				i++;
			}
		}
		if (token->heredoc)
			handle_heredoc(token);
		token = token->next;
	}
}

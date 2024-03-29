/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:38:35 by chustei           #+#    #+#             */
/*   Updated: 2023/08/10 11:20:14 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*create_token(char *str, enum e_token type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = ft_strdup(str);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_new_token(t_minishell *shell, t_token *new_token)
{
	t_token	*current;

	current = NULL;
	if (new_token != NULL)
	{
		if (shell->tokens == NULL)
			shell->tokens = new_token;
		else
		{
			current = shell->tokens;
			while (current->next != NULL)
				current = current->next;
			current->next = new_token;
		}
	}
}

t_token	*create_quoted_token(char *arg, char *set)
{
	t_token	*new_token;
	char	*dup;

	dup = ft_strtrim(arg, set);
	new_token = create_token(dup, T_1Q_WORD);
	free(dup);
	return (new_token);
}

void	append_token(t_minishell *shell, char *arg)
{
	t_token	*new_token;
	int		arg_len;

	new_token = NULL;
	arg_len = ft_strlen(arg);
	if (arg_len == 1 && arg[0] == '|')
		new_token = create_token(arg, T_PIPE);
	else if (arg_len == 1 && arg[0] == ' ')
		new_token = create_token(arg, T_SPACE);
	else if (arg[0] == '\'' && arg[arg_len - 1] && arg_len > 1)
		new_token = create_quoted_token(arg, "'");
	else if (arg[0] == '"')
		new_token = create_quoted_token(arg, "\"");
	else if (arg_len == 1 && arg[0] == '>')
		new_token = create_token(arg, T_REDIR_OUT);
	else if (arg_len == 1 && arg[0] == '<')
		new_token = create_token(arg, T_REDIR_IN);
	else if (arg_len == 2 && arg[0] == '>' && arg[1] == '>')
		new_token = create_token(arg, T_REDIR_OUT_APPEND);
	else if (arg_len == 2 && arg[0] == '<' && arg[1] == '<')
		new_token = create_token(arg, T_HEREDOC);
	else
		word_butcher(shell, arg);
	if (new_token)
		add_new_token(shell, new_token);
}

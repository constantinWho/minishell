/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:02 by chustei           #+#    #+#             */
/*   Updated: 2023/06/29 17:32:54 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* t_minishell	*create_struct(char **env)
{
	t_minishell	*shell;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	shell->head = NULL;
	shell->env = copy_realloc_data(env, 0);
	return (shell);
} */

t_token	*create_token(char *str, enum e_token type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->value = ft_strdup(str);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

int	ft_tokens_size(t_token *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	check_quotes(char *input)
{
	int	i;
	int	type;
	int	found;

	i = 0;
	type = 0;
	found = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (type == 0)
			{
				type = input[i];
				i++;
				while (input[i] && input[i] != type)
					i++;
				if (!input[i])
					return (0);
				found = type;
				type = 0;
			}
		}
		i++;
	}
	if (type != 0)
		return (0);
	return (1);
}

void	free_tokens(t_token *lst)
{
	t_token	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}

void	append_token(t_minishell *shell, char *arg)
{
	t_token	*new_token;
	t_token	*current;
	int		arg_len;

	new_token = NULL;
	arg_len = ft_strlen(arg);
	if (arg_len == 1 && arg[0] == '|')
		new_token = create_token(arg, T_PIPE);
	else if (arg_len == 1 && arg[0] == ' ')
		new_token = create_token(arg, T_SPACE);
	else if (arg[0] == '\'')
		new_token = create_token(ft_strtrim(arg, "'"), T_1Q_WORD);
	else if (arg[0] == '"')
		new_token = create_token(arg, T_2Q_WORD);
/* 	else if (args[i][0] == '\'' && args[i][arg_len - 1] == '\'')
		new_token = create_token(args[i], T_1Q_WORD); */
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
	printf("TYPE[%i]: %s\n", shell->tokens->type, shell->tokens->value);
}

void	ft_lexer(t_minishell *shell, char *input)
{
	int	i;

	if (!(check_quotes(input)))
	{
		printf("++++++++++++ Error: Missing closed quotes. ++++++++++++\n");
		return ;
	}
	i = 0;
	special_split(shell, input);
/* 	while (shell->args[i])
	{
		printf("[%i]: %s \n", i, shell->args[i]);
		i++;
	} */
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	while (shell->args[i])
	{
		append_token(shell, shell->args[i]);
		i++;
	}
	printf("list size: %i\n", ft_tokens_size(shell->tokens));
/* 	free_array(shell->env); */
}

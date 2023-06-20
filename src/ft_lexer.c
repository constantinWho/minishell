/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:02 by chustei           #+#    #+#             */
/*   Updated: 2023/06/20 12:32:42 by chustei          ###   ########.fr       */
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

int	find_type(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			return (i);
		i++;
	}
	return (-1);
}

int	check_closed(char *input, int type_pos)
{
	int	type;

	type = input[type_pos];
	type_pos++;
	while (input[type_pos] != type || input[type_pos])
		type_pos++;
	return (type_pos);
}

int	check_quotes(char *input)
{
	int	len;
	int	type_pos;

	len = ft_strlen(input);
	type_pos = 0;
	while (type_pos < len)
	{
		type_pos = find_type(&input[type_pos]);
		if (type_pos == -1)
			return (1);
		type_pos = check_closed(input, type_pos);
		if (type_pos >= len)
			return (0);
	}
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

void	append_token(t_minishell *shell, char **args, int i)
{
	t_token	*new_token;
	t_token	*current;
	int		arg_len;

	arg_len = ft_strlen(args[i]);
	if (arg_len == 1 && args[i][0] == '|')
		new_token = create_token(args[i], T_PIPE);
	else if (args[i][0] == '\'' && args[i][arg_len - 1] == '\'')
		new_token = create_token(args[i], T_1Q_WORD);
	else
		new_token = create_token(args[i], T_NULL);
	printf("%u:[%s] \n", new_token->type, new_token->value);
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

void	ft_lexer(t_minishell *shell, char *input)
{
	int	i;

	i = 0;
	shell->args = ft_split(input, ' ');
	while (shell->args[i])
	{
		printf("%s ", shell->args[i]);
		i++;
	}
	i = 0;
	printf("\n");
	if (!(check_quotes(input)))
	{
		printf("Error: Missing closed quotes.\n");
		return ;
	}
	// Free existing tokens
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	while (shell->args[i])
	{
		append_token(shell, shell->args, i);
		i++;
	}
	printf("list size: %i\n", ft_tokens_size(shell->tokens));
/* 	free_array(shell->env); */
}

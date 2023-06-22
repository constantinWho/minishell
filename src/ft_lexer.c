/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:03:02 by chustei           #+#    #+#             */
/*   Updated: 2023/06/22 13:19:35 by chustei          ###   ########.fr       */
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

int	count_strs(char *s)
{
	int	i;
	int	len;
	int	split;
	int	count;
	int	pos;

	len = ft_strlen(s);
	i = 0;
	count = 0;
	pos = -1;
	while (s[i])
	{
		split = 0;
		while ((s[i] == ' ' || s[i] == '\t') && i < len)
			i++;
		if (s[i] == '\'' || s[i] == '"')
		{
			split = s[i];
			pos = i;
			i++;
			while (s[i] != split)
				i++;
			if (i > pos + 1)
				count++;
			i++;
		}
		else
		{
			while (i < len && (s[i] != '\t' && s[i] != ' '
					&& s[i] != '"' && s[i] != '\''))
				i++;
			count++;
		}
		while ((s[i] == ' ' || s[i] == '\t') && i < len)
			i++;
	}
	return (count);
}

void	special_split(char *str)
{
	int		i;
	int		str_count;
	//char	**arr;

	i = 0;
	str_count = count_strs(str);
	printf("str_count: %i\n", str_count);
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
	special_split(input);
/* 	while (shell->args[i])
	{
		printf("[i]: %s \n", shell->args[i]);
		i++;
	} */
	// Free existing tokens
	free_tokens(shell->tokens);
	shell->tokens = NULL;
/* 	while (shell->args[i])
	{
		append_token(shell, shell->args, i);
		i++;
	} */
	//printf("list size: %i\n", ft_tokens_size(shell->tokens));
/* 	free_array(shell->env); */
}

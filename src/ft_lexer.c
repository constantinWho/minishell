/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/learning.c
/*   Created: 2023/06/07 12:03:02 by chustei           #+#    #+#             */
/*   Updated: 2023/06/12 17:31:02 by jalbers          ###   ########.fr       */
=======
/*   Created: 2023/06/13 11:36:32 by chustei           #+#    #+#             */
/*   Updated: 2023/06/13 11:45:22 by chustei          ###   ########.fr       */
>>>>>>> main:src/ft_lexer.c
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

<<<<<<< HEAD:src/learning.c
t_minishell	*create_struct(char **env)
{
	t_minishell	*shell;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	shell->head = NULL;
	shell->env = copy_realloc_data(env, 0);
	return (shell);
}

=======
>>>>>>> main:src/ft_lexer.c
t_token	*create_token(int len, char *str, char *type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->len = len;
	new_token->str = ft_strdup(str);
	new_token->type = ft_strdup(type);
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

int	check_closed_quotes(char **arr)
{
	int	i;
	int	len;

	i = 0;
	while (arr[i])
	{
		len = ft_strlen(arr[i]) - 1;
		if (arr[i][0] == 34 || arr[i][len] == 34)
			if (arr[i][0] != arr[i][len] || len == 0)
				return (0);
		if (arr[i][0] == 39 || arr[i][len] == 39)
			if (arr[i][0] != arr[i][len] || len == 0)
				return (0);
		i++;
	}
	return (1);
}

void	free_tokens(t_token *lst)
{
	t_token	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->str);
		free(lst->type);
		free(lst);
		lst = tmp;
	}
}

void	append_token(t_minishell *shell, char **args, int i)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(ft_strlen(args[i]), args[i], "word");
	printf("%i:[%s] '%s'\n", new_token->len, new_token->type, new_token->str);
	if (shell->tokens == NULL)
		shell->tokens = new_token;
	else
	{
		current = shell->tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
	if (args[i + 1])
	{
		new_token = create_token(1, " ", "sep");
		printf("0:[%s]\n", new_token->type);
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
	if (!(check_closed_quotes(shell->args)))
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
<<<<<<< HEAD:src/learning.c
	free_array(shell->env);
	return (0);
=======
	ft_printf("size of list:%i\n", ft_tokens_size(shell->tokens));
	free(shell->args);
>>>>>>> main:src/ft_lexer.c
}

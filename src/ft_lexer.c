/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:09:40 by chustei           #+#    #+#             */
/*   Updated: 2023/07/04 14:44:04 by jalbers          ###   ########.fr       */
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

void	print_linked_list(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		// printf("TYPE[%i]: %s\n", current->type, current->value);
		current = current->next;
	}
}

void	ft_lexer(t_minishell *shell, char *input)
{
	int	i;

	if (!(check_quotes(input)))
	{
		// printf("++++++++++++ Error: Missing closed quotes. ++++++++++++\n");
		return ;
	}
	i = 0;
	special_split(shell, input);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	while (shell->args[i])
	{
		append_token(shell, shell->args[i]);
		i++;
	}
	print_linked_list(shell->tokens);
	// printf("list size: %i\n", ft_tokens_size(shell->tokens));
/* 	free_array(shell->env); */
}

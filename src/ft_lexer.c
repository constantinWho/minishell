/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:09:40 by chustei           #+#    #+#             */
/*   Updated: 2023/07/11 13:18:59 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	shell->tokens = NULL;
	while (shell->args[i])
	{
		append_token(shell, shell->args[i]);
		i++;
	}
}

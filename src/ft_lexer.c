/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:09:40 by chustei           #+#    #+#             */
/*   Updated: 2023/07/18 17:42:43 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	shell->tokens = NULL;
	while (shell->args[i])
	{
		append_token(shell, shell->args[i]);
		i++;
	}
}

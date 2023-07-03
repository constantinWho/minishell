/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_butcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:46:10 by chustei           #+#    #+#             */
/*   Updated: 2023/07/03 20:13:54 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_split_tokens(t_minishell *shell, char **words, t_token *new_token)
{
	int		arg_len;
	int		i;

	arg_len = 0;
	i = 0;
	while (words[i])
	{
		arg_len = ft_strlen(words[i]);
		if (arg_len == 1 && words[i][0] == '|')
			new_token = create_token(words[i], T_PIPE);
		else if (arg_len == 1 && words[i][0] == '>')
			new_token = create_token(words[i], T_REDIR_OUT);
		else if (arg_len == 1 && words[i][0] == '<')
			new_token = create_token(words[i], T_REDIR_IN);
		else if (arg_len == 2 && words[i][0] == '>' && words[i][1] == '>')
			new_token = create_token(words[i], T_REDIR_OUT_APPEND);
		else if (arg_len == 2 && words[i][0] == '<' && words[i][1] == '<')
			new_token = create_token(words[i], T_HEREDOG);
		else
			new_token = create_token(words[i], T_WORD);
		if (new_token)
			add_new_token(shell, new_token);
		i++;
	}
}

void	word_butcher(t_minishell *shell, char *word)
{
	int		i;
	int		words_count;
	char	**words;
	t_token	*new_token;

	i = 0;
	new_token = NULL;
	words_count = get_words_count(word);
	printf("strings count: %i \n", words_count);
	words = word_split(word, words_count);
	add_split_tokens(shell, words, new_token);
}

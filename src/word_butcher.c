/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_butcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:46:10 by chustei           #+#    #+#             */
/*   Updated: 2023/07/20 12:30:43 by chustei          ###   ########.fr       */
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
			new_token = create_token(words[i], T_HEREDOC);
		else
			new_token = create_token(words[i], T_WORD);
		if (new_token)
			add_new_token(shell, new_token);
		i++;
	}
}

void	free_words(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	word_butcher(t_minishell *shell, char *word)
{
	int		words_count;
	char	**words;
	t_token	*new_token;

	new_token = NULL;
	words_count = get_words_count(word);
	words = word_split(word, words_count);
	add_split_tokens(shell, words, new_token);
	free_words(words);
}

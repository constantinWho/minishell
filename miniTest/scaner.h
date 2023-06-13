/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:58:12 by chustei           #+#    #+#             */
/*   Updated: 2023/06/07 16:02:46 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANER_H
# define SCANER_Hl

/* source of input */
/* length of token text */
/* token text */
struct	s_token
{
	struct source_s	*src;
	int				text_len;
	char			*text;
};

/* the special EOF token, which indicates the end of input */
extern struct s_token	eof_token;
struct s_tokentoken		*tokenize(struct source_s *src);
void					free_token(struct token_s *tok);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:53:33 by chustei           #+#    #+#             */
/*   Updated: 2023/06/07 15:53:44 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
# define SOURCE_H

# define EOF			(-1)
# define ERRCHAR		( 0)
# define INIT_SRC_POS	(-2)

typedef struct s_source
{
	char		*buffer;
	long		bufsize;
	long		curpos;
}				t_source;

char			next_char(struct source_s *src);
void			unget_char(struct source_s *src);
char			peek_char(struct source_s *src);
void			skip_white_spaces(struct source_s *src);

#endif

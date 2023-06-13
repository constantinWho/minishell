/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:44:04 by chustei           #+#    #+#             */
/*   Updated: 2023/06/13 11:45:17 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
		ft_printf("\nMinishell > ", signum);
}

// 1. ignore "Ctrl-C"
// 2. ignore "Ctrl-Z"
// 3. ignore "Ctrl-\"
void	ignore_signal_for_shell(void)
{
	void	(*sigint_handler)(int);

	sigint_handler = signal(SIGINT, handle_sigint);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

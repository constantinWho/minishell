/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:10:40 by jalbers           #+#    #+#             */
/*   Updated: 2023/08/04 16:08:32 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_successive_cats(t_group *group)
{
	t_group	*current;
	int		count;

	count = 0;
	current = group;
	while (current != NULL && str_match(current->cmd, "cat") == 1
		&& !current->args[0])
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	handle_user_input(t_process *process, t_minishell *shell, t_group *g)
{
	char	*input;
	int		cat_count;
	int		i;

	cat_count = count_successive_cats(g);
	i = 0;
	dup2(shell->original_stdout, 1);
	while (process->index == 0 && i < cat_count)
	{
		input = readline("");
		if (input == NULL)
			exit(EXIT_SUCCESS);
		if (input[0] == '\0')
			printf("\n");
		i++;
		free(input);
	}
	dup2(process->fd_write, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:39:55 by chustei           #+#    #+#             */
/*   Updated: 2023/05/22 15:59:27 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//The readline() function reads a line from the terminal and returns it,
//using prompt as a prompt. If no prompt is given as parameter, no prompt
//will be shown in the terminal. The line returned is allocated with malloc
//and we have to free it ourselves.

#include "../inc/minishell.h"

char	*ft_readline(void)
{
	char	*input;

	input = readline("Minishell > ");

	// Add the input to the command history
	if (input)
		add_history(input);

	return (input);
	// Process the input
	// printf("%s\n", input);
}

void	call_method(char **args)
{
	// Execute the "ls" command using execvp
	if (fork() == 0) {
		// Child process
		execvp(args[0], args);
		perror("Command execution failed");
		exit(EXIT_FAILURE);
	} else {
		// Parent process
		wait(NULL); // Wait for the child process to finish
	}
}

int	main(void)
{
	while (1)
	{
		char	*input;

		input = ft_readline();

		char	**args = malloc(3 * sizeof(char));
		args[0] = "ls";
		args[1] = "-l";
		args[2] = NULL;

		call_method(args);

	}
	// printf("%i \n", history_length);
	return (0);
}

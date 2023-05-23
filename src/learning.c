/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:39:55 by chustei           #+#    #+#             */
/*   Updated: 2023/05/23 16:11:15 by chustei          ###   ########.fr       */
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

	// Exits the minishell on CTRL-D
	if (input == NULL)
		exit(EXIT_SUCCESS);
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
	if (fork() == 0)
	{
		// Child process
		execvp(args[0], args);
		perror("Command execution failed");
		exit(EXIT_FAILURE);
	} else {
		// Parent process
		wait(NULL); // Wait for the child process to finish
	}
}

/* void	handle_sigquit(int signum)
{
	// signum 3 represents (CTRL+\)
	if (signum == SIGQUIT)
		ft_printf("", signum);
}
*/
void	handle_sigint(int signum)
{
	if (signum == SIGINT)
		ft_printf("\nMinishell > ", signum);
}

/* 	// Register the signal handler for SIGINT (CTRL+C)
	signal(SIGINT, handle_sigint);
	// Register the signal handler for SIGQUIT (CTRL+\)
	signal(SIGQUIT, handle_sigquit);
 */
void	ignore_signal_for_shell(void)
{
	void	(*sigint_handler)(int);

	// ignore "Ctrl-C"
	sigint_handler = signal(SIGINT, handle_sigint);
	// ignore "Ctrl-Z"
	signal(SIGTSTP, SIG_IGN);
	// ignore "Ctrl-\"
	signal(SIGQUIT, SIG_IGN);
}

int	main(void)
{
	ignore_signal_for_shell();

	while (1)
	{
		char	*input;

		input = ft_readline();
		char	**args = malloc(3 * sizeof(char));
		args[0] = "cat";
		args[1] = "text.txt";
		args[2] = NULL;

		call_method(args);

		free(args);
	}
	// printf("%i \n", history_length);
	return (0);
}

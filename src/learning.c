/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:39:55 by chustei           #+#    #+#             */
/*   Updated: 2023/05/25 16:39:23 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


t_minishell	*create_struct(void)
{
	t_minishell	*shell;

	shell = (t_minishell *)malloc(sizeof(t_minishell));
	shell->head = NULL;
	return (shell);
}


t_token	*create_token(int length, char *string, char *type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->len = length;
	new_token->str = ft_strdup(string);
	new_token->type = ft_strdup(type);
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_minishell *shell, char **args, int i)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(ft_strlen(args[i]), args[i], "test");
	if (shell->head == NULL)
		shell->head = new_token;
	else
	{
		current = shell->head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
	if (args[i + 1])
		printf("test\n");

}

// 1. Exits the minishell on CTRL-D
// 2. Add the input to the command history
char	*ft_readline(void)
{
	char	*input;

	input = readline("Minishell > ");
	if (input == NULL)
		exit(EXIT_SUCCESS);
	if (input)
		add_history(input);
	return (input);
}

// Calling the Methods
void	call_method(char **args)
{
	if (fork() == 0)
	{
		execvp(args[0], args);
		perror("Command execution failed");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

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

int	ft_tokens(t_token *lst)
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
	char	**args;
	int		i;

	i = 0;
	args = ft_split(input, ' ');
	while (args[i])
	{
		append_token(shell, args, i);
		i++;
	}
	ft_printf("size of list:%i\n", ft_tokens(shell->head));
	call_method(args);
	free(args);
}

int	main(void)
{
	char		*input;
	t_minishell	*shell;

	shell = create_struct();
	ignore_signal_for_shell();
	while (1)
	{
		input = ft_readline();
		ft_lexer(shell, input);
	}
	return (0);
}

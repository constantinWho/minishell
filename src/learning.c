/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:39:55 by chustei           #+#    #+#             */
/*   Updated: 2023/05/26 13:16:57 by chustei          ###   ########.fr       */
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


t_token	*create_token(int len, char *str, char *type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->len = len;
	new_token->str = ft_strdup(str);
	new_token->type = ft_strdup(type);
	new_token->next = NULL;
	return (new_token);
}

int	check_closed_quotes(char **arr)
{
	int	i;
	int	len;

	i = 0;
	while (arr[i])
	{
		len = ft_strlen(arr[i]) - 1;
		if (arr[i][0] == 34 || arr[i][len] == 34)
			if (arr[i][0] != arr[i][len] || len == 0)
				return (0);
		if (arr[i][0] == 39 || arr[i][len] == 39)
			if (arr[i][0] != arr[i][len] || len == 0)
				return (0);
		i++;
	}
	return (1);
}

void	append_token(t_minishell *shell, char **args, int i)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(ft_strlen(args[i]), args[i], "word");
	printf("ARG: {%s}\n", new_token->str);
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
	{
		new_token = create_token(1, " ", "sep");
		printf("SEP: [ ]\n");
		current = shell->head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
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
	if (!(check_closed_quotes(args)))
	{
		printf("Error: Missing closed qoutes.\n");
		return ;
	}
	while (args[i])
	{
		append_token(shell, args, i);
		i++;
	}
	ft_printf("size of list:%i\n", ft_tokens(shell->head));
	// call_method(args);
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

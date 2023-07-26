/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:39:11 by jalbers           #+#    #+#             */
/*   Updated: 2023/07/26 13:18:11 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_new_line_option(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	process_if_new_line(char **args, int *i, int *new_line_option)
{
	(*new_line_option) = check_new_line_option(args[*i]);
	if (args[*i + 1] && (*new_line_option) == 0)
	{
		if (args[*i + 1][0] == ' ' && ft_strlen(&args[*i + 1][0]) == 1)
			(*i) += 2;
		else
			(*new_line_option) = 1;
	}
	else if (!args[*i + 1] && *new_line_option == 0)
		(*i) += 1;
	else
		(*new_line_option) = 1;
}

void	skip_extra_new_lines(char **args, int *checked_n, int *i)
{
	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n'
	&& *checked_n == 0)
	{
		if (args[*i + 1] && check_new_line_option(args[*i]) == 0)
		{
			if (args[*i + 1][0] == ' '
				&& ft_strlen(&args[*i + 1][0]) == 1)
				(*i) += 2;
			else
				(*checked_n) = 1;
		}
		else if (!args[*i + 1] && check_new_line_option(args[*i]) == 0)
		{
			(*checked_n) = 1;
			(*i) += 1;
		}
		else
			(*checked_n) = 1;
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	j;
	int	new_line_option;
	int	checked_n;

	i = 1;
	checked_n = 0;
	new_line_option = 1;
	if (args[i] && args[i][0] == '-' && args[i][1] == 'n')
		process_if_new_line(args, &i, &new_line_option);
	if (i == 2 || i == 3)
		skip_extra_new_lines(args, &checked_n, &i);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			write(1, &args[i][j++], 1);
		i++;
	}
	if (new_line_option == 1)
		write(1, "\n", 1);
	return (0);
}

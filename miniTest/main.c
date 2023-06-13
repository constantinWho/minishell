/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:37:01 by chustei           #+#    #+#             */
/*   Updated: 2023/06/07 15:29:23 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

char	*read_cmd(char *buf)
{
	int		buflen;
	char	*tmp;

	get_next_line(0, &buf);
	buflen = ft_strlen(buf);
	while (buflen > 1 && buf[buflen - 1] == '\\')
	{
		buf[buflen - 1] = '\n';
		buf[buflen] = '\0';
		print_prompt2();
		tmp = buf;
		get_next_line(0, &buf);
		buf = ft_strjoin(tmp, buf);
		buflen = ft_strlen(buf);
	}
	return (buf);
}

int	main(void)
{
	char	*cmd;

	cmd = NULL;
	while (1)
	{
		print_prompt1();
		cmd = read_cmd(cmd);
		if (!cmd)
		{
			exit(EXIT_SUCCESS);
		}
		if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
		{
			free(cmd);
			continue ;
		}
		if (strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			break ;
		}
		write(1, cmd, ft_strlen(cmd));
		write(1, "\n", 1);
		free(cmd);
	}
	exit(EXIT_SUCCESS);
}

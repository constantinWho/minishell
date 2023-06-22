/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbers <jalbers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:18:55 by jalbers           #+#    #+#             */
/*   Updated: 2023/06/12 17:27:44 by jalbers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(void)
{
	char	cwd[500];

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	ft_putendl_fd(cwd, 1);
	return (0);
}
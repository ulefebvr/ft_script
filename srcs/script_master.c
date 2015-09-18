/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 16:01:24 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/09/16 16:01:25 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

#define BUFFSIZE	256

void		script_master(t_script *script)
{
	fd_set		readfds;
	int			cc;
	char		buffer[BUFFSIZE];

	FD_ZERO(&readfds);
	while (1)
	{
		FD_SET(script->fds[0], &readfds);
		FD_SET(0, &readfds);
		if (select(script->fds[0] + 1, &readfds, 0, 0, &STV) < 0)
			return ;
		if (FD_ISSET(0, &readfds))
		{
			if ((cc = read(0, buffer, BUFFSIZE)) <= 0)
				return ;
			write(script->fds[0], buffer, cc);
		}
		if (FD_ISSET(script->fds[0], &readfds))
		{
			if ((cc = read(script->fds[0], buffer, BUFFSIZE)) <= 0)
				return ;
			write(1, buffer, cc);
			write(script->out_file, buffer, cc);
		}
	}
}

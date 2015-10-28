/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 10:58:05 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/28 16:29:46 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

#include "ft_script.h"

#define START_M 	"Script started, output file is %s\n"
#define START_M_F	"Script started on %s"
#define END_M		"\nScript done, output file is %s\n"
#define END_M_F		"\nScript done on %s"

#define MASTER		0
#define SLAVE		1

void		ft_messages(int start, t_script *args)
{
	struct timeval	now_time;

	if (!(OPT_Q & args->option))
	{
		gettimeofday(&now_time, NULL);
		ft_print(start ? START_M : END_M, args->filename);
		ft_fdprint(args->out_file, start ? START_M_F : END_M_F,
			ctime(&(now_time.tv_sec)));
	}
}

int			launch_script(t_script *args)
{
	pid_t	pid;

	ft_messages(1, args);
	if (!ft_openpt(&args->fds[MASTER], &args->fds[SLAVE]) || !term_init(args))
		return (ft_fdprint(2, "Error opening pseudo-terminal\n"), 0);
	if ((pid = fork()) < 0)
		return (ft_fdprint(2, "Error : problem with fork\n"), 0);
	if (!pid)
	{
		close(args->fds[MASTER]);
		slave(args, args->fds[SLAVE], args->fds[MASTER]);
		_exit(0);
	}
	close(args->fds[SLAVE]);
	script_master(args);
	term_restore(args);
	ft_messages(0, args);
	return (1);
}

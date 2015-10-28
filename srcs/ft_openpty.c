/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openpty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 11:46:15 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/10/28 16:28:46 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <fcntl.h>

#include "libft.h"

/*
** posix_openpt :
**			opens the first available master pseudo-terminal device
**			equivalent to opening /dev/ptmx
** grantpt :
**			establish ownership and permissions of the slave device
**			TIOCPTYGRANT request using ioctl
** unlockpt :
**			unlocks the slave pseudo-terminal device
**			TIOCPTYUNLK request using ioctl
** ptsname :
**			full pathname of the slave device
**			TIOCPTYGNAME request using ioctl + open on file name
*/

int			ft_openpt(int *master, int *slave)
{
	struct winsize	win;
	char			ptsname[128];

	if (ioctl(0, TIOCGWINSZ, &win) != 0)
		return (0);
	if ((*master = open("/dev/ptmx", O_RDWR)) < 0)
		return (ft_fdprint(2, "Error opening master file\n"), 0);
	if (ioctl(*master, TIOCPTYGRANT) != 0)
		return (ft_fdprint(2, "Error grant tty\n"), 0);
	if (ioctl(*master, TIOCPTYUNLK) != 0)
		return (ft_fdprint(2, "Error unlocking tty\n"));
	if (ioctl(*master, TIOCPTYGNAME, ptsname) != 0)
		return (ft_fdprint(2, "Error getting tty name\n"), 0);
	if ((*slave = open(ptsname, O_RDWR)) < 0)
		return (ft_fdprint(2, "Error opening slave file\n"), 0);
	if (ioctl(*master, TIOCSWINSZ, &win) != 0)
		return (0);
	return (1);
}

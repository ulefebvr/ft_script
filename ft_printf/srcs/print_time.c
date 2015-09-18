/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/01 13:39:28 by ulefebvr          #+#    #+#             */
/*   Updated: 2015/07/01 13:39:28 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <time.h>

static const char g_day[7][3] = {
	"Sun",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat"
};

static const char g_month[12][3] = {
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

int			print_time(t_conv conv, va_list list)
{
	struct tm			*c_time;

	(void)conv;
	c_time = va_arg(list, struct tm*);
	return (ft_fdprintf(ft_out(NULL), "%.3s %.3s%3d %02.2d:%02.2d:%02.2d %d",
	g_day[c_time->tm_wday], g_month[c_time->tm_mon], c_time->tm_mday,
	c_time->tm_hour, c_time->tm_min, c_time->tm_sec,
	1900 + c_time->tm_year));
}

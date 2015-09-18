/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:12:05 by ulefebvr          #+#    #+#             */
/*   Updated: 2014/11/04 10:12:08 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		a;

	a = 0;
	str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str)
	{
		while (s1[a])
		{
			str[a] = s1[a];
			a++;
		}
		str[a] = '\0';
		return (str);
	}
	else
		return (NULL);
}

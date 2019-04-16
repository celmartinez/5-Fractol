/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 01:34:22 by cmartine          #+#    #+#             */
/*   Updated: 2018/09/20 01:43:13 by cmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len(double n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char			*ft_ftoa(double n)
{
	char	*strn;
	int		len_pt;
	int		i;

	len_pt = ft_len(n);
	if (!(strn = (char *)malloc(sizeof(char) * (len_pt + 1))))
		return (NULL);
	strn[len_pt] = '\0';
	while (n >= 1)
		n = n / 10;
	i = 0;
	while (len_pt-- > 0)
	{
		n = n * 10;
		strn[i] = (int)n + '0';
		n = n - (int)n;
		i++;
	}
	return (strn);
}

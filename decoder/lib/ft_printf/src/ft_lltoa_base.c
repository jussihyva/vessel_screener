/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 14:55:26 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/28 15:00:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int					count_chars(unsigned long long nbr, int base)
{
	int		c;

	c = 1;
	while (nbr /= base)
		c++;
	return (c);
}

static unsigned long long	unsign(long long nbr, int neg)
{
	if (neg)
		return (unsigned long long)(nbr * -1);
	else
		return (unsigned long long)(nbr);
}

static char					*long_to_string(unsigned long long nbr,
									unsigned int base, size_t index, char *s)
{
	static char		*letter = "0123456789abcdef";

	while (nbr >= (unsigned long long)base)
	{
		s[--index] = letter[nbr % base];
		nbr /= base;
	}
	s[--index] = letter[nbr % base];
	return (s);
}

char						*ft_lltoa_base(long long nbr, int base)
{
	char					*s;
	int						neg;
	size_t					num_of_chars;
	unsigned long long		un_nbr;

	neg = 0;
	if (nbr < 0 && base == 10)
		neg = 1;
	un_nbr = unsign(nbr, neg);
	num_of_chars = count_chars(un_nbr, base);
	s = (char *)ft_strnew(sizeof(*s) * (num_of_chars + neg));
	if (neg)
		s[0] = '-';
	s = long_to_string(un_nbr, base, num_of_chars + neg, s);
	return (s);
}

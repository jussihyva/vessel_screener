/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:59:01 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/28 15:24:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char						*ft_ulltoa_base(unsigned long long nbr, int base)
{
	char				*s;
	size_t				num_of_chars;

	num_of_chars = ft_numlen(nbr, base);
	s = (char *)ft_strnew(sizeof(*s) * (num_of_chars));
	s = long_to_string(nbr, base, num_of_chars, s);
	return (s);
}

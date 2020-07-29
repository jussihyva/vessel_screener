/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 15:05:00 by jkauppi           #+#    #+#             */
/*   Updated: 2020/01/11 08:13:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	unsign(long long nbr, int neg)
{
	if (neg)
		return (unsigned long long)(nbr * -1);
	else
		return (unsigned long long)(nbr);
}

static size_t				get_decimals(size_t precision, long double *nbr)
{
	static size_t	max_precision = 22;
	size_t			added_zeros;
	size_t			c;

	added_zeros = 0;
	c = 0;
	while (c++ < precision && c < max_precision)
	{
		*nbr *= 10;
		if (*nbr < 1 && *nbr > -1)
		{
			added_zeros++;
		}
	}
	return (added_zeros);
}

static void					add_digits(char *s, unsigned long long un_nbr,
													size_t base)
{
	static char				*letter = "0123456789abcdef";
	char					*sub_string;
	size_t					num_of_chars;

	num_of_chars = ft_numlen(un_nbr, base);
	sub_string = ft_strnew(num_of_chars);
	while (un_nbr >= (unsigned long long)base)
	{
		sub_string[--num_of_chars] = letter[un_nbr % base];
		un_nbr /= base;
	}
	sub_string[--num_of_chars] = letter[un_nbr % base];
	s = ft_strcat(s, sub_string);
	ft_strdel(&sub_string);
	return ;
}

static void					split_float_nbr(t_float *float_nbr,
												size_t precision, size_t base)
{
	float_nbr->neg = 0;
	if (float_nbr->nbr < 0 && base == 10)
		float_nbr->neg = 1;
	float_nbr->nbr_integer = unsign((long long)float_nbr->nbr, float_nbr->neg);
	float_nbr->nbr -= (long long)float_nbr->nbr;
	float_nbr->nbr = ft_round(float_nbr->nbr, base, precision, float_nbr->neg);
	if (float_nbr->nbr >= 1 || float_nbr->nbr <= -1)
	{
		float_nbr->nbr -= (int)float_nbr->nbr;
		float_nbr->nbr_integer++;
	}
	return ;
}

char						*ft_dtoa_base(long double nbr, size_t base,
												size_t precision, int add_dot)
{
	char					*s;
	size_t					added_zeros;
	t_float					float_nbr;

	float_nbr.nbr = nbr;
	split_float_nbr(&float_nbr, precision, base);
	added_zeros = get_decimals(precision, &float_nbr.nbr);
	float_nbr.nbr_decimal = unsign((long long)float_nbr.nbr, float_nbr.neg);
	s = (char *)ft_strnew((ft_numlen(float_nbr.nbr_integer, base) + precision +
															float_nbr.neg + 1));
	if (float_nbr.neg)
		s = ft_strcat(s, "-");
	add_digits(s, float_nbr.nbr_integer, base);
	if (precision || add_dot)
		s = ft_strcat(s, ".");
	precision -= added_zeros++;
	while (--added_zeros)
		s = ft_strcat(s, "0");
	if (float_nbr.nbr_decimal)
		add_digits(s, float_nbr.nbr_decimal, base);
	while (added_zeros++ + ft_numlen(float_nbr.nbr_decimal, base) < precision)
		s = ft_strcat(s, "0");
	return (s);
}

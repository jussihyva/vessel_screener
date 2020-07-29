/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 15:21:05 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/28 18:09:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_numlen(unsigned long long nbr, size_t base)
{
	size_t		c;

	c = 1;
	while (nbr /= base)
		c++;
	return (c);
}

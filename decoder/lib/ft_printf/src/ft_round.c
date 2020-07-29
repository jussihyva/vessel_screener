/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 08:12:32 by jkauppi           #+#    #+#             */
/*   Updated: 2019/12/30 12:51:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double			ft_round(double nbr, int base, size_t precision, int neg)
{
	double		round_value;

	round_value = (double)(base / 2);
	while (precision--)
		round_value /= base;
	round_value /= base;
	if (neg)
		nbr -= round_value;
	else
		nbr += round_value;
	return (nbr);
}

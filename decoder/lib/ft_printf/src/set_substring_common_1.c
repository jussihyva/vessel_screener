/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_substring_common_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:52:22 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/19 15:18:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				count_num_of_fillers(t_substring *substring, int min_len)
{
	int		num_of_fillers;

	num_of_fillers = min_len -
				substring->o_string.parameter.content_size -
				substring->o_string.zero_filler.content_size -
				substring->o_string.prefix.content_size -
				substring->o_string.sign.content_size;
	return (num_of_fillers);
}

static char		set_pre_filler_char(t_substring *substring)
{
	char		filler;

	filler = ' ';
	if (substring->flags & zero)
		filler = '0';
	if (substring->conv_type == 'o' && substring->precision == -1)
		;
	else if (substring->conv_type == 'c' ||
				substring->conv_type == '%' ||
				substring->conv_type == 's')
		filler = ' ';
	else
		filler = ' ';
	return (filler);
}

void			set_pre_filler(t_substring *substring)
{
	int			num_of_fillers;
	char		*s;
	char		filler;

	if (substring->conv_type != '%')
	{
		if (substring->width != -1 && !(substring->flags & minus))
		{
			num_of_fillers = count_num_of_fillers(substring, substring->width);
			if (num_of_fillers > 0)
			{
				s = ft_strnew(num_of_fillers);
				*(s + num_of_fillers) = '\0';
				substring->o_string.pre_filler.content_size = num_of_fillers;
				substring->o_string.pre_filler.content = s;
				filler = set_pre_filler_char(substring);
				while (num_of_fillers--)
					*(s + num_of_fillers) = filler;
			}
		}
	}
	return ;
}

void			set_post_filler(t_substring *substring)
{
	int			num_of_fillers;
	char		*s;
	char		filler;

	if (substring->conv_type != '%')
	{
		if ((substring->flags & minus) && substring->width != -1)
		{
			num_of_fillers = count_num_of_fillers(substring, substring->width);
			if (num_of_fillers > 0)
			{
				filler = ' ';
				s = ft_strnew(num_of_fillers);
				*(s + num_of_fillers) = '\0';
				substring->o_string.post_filler.content_size = num_of_fillers;
				substring->o_string.post_filler.content = s;
				while (num_of_fillers--)
					*(s + num_of_fillers) = filler;
			}
		}
	}
	return ;
}

void			set_sign(t_substring *substring)
{
	char		conv_type;

	conv_type = substring->conv_type;
	if (conv_type == 'f' || conv_type == 'd' || conv_type == 'i')
	{
		if (substring->par_value_is_neg)
		{
			substring->o_string.sign.content = ft_strdup("-");
			substring->o_string.sign.content_size = 1;
		}
		else if (substring->flags & plus)
		{
			substring->o_string.sign.content = ft_strdup("+");
			substring->o_string.sign.content_size = 1;
		}
		else if (substring->flags & space)
		{
			substring->o_string.sign.content = ft_strdup(" ");
			substring->o_string.sign.content_size = 1;
		}
	}
}

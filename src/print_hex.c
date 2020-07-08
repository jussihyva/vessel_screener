/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:07:38 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/08 14:33:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

static void			print_bin_string(ssize_t index, char *line, ssize_t size)
{
	ssize_t		end_point;
	ssize_t		i;
	ssize_t		j;

	end_point = index + 6;
	i = index;
	while (i < end_point)
	{
		if (i < size)
		{
			j = 8;
			while (j--)
			{
				if (!(((i - index) * 8 + 7 - j) % 6))
					ft_printf(" ");
				ft_printf("%d", (line[i] >> j) & 1);
			}
		}
		else
			ft_printf("         ");
		i++;
	}
	return ;
}

static void			print_hex_string(ssize_t index, char *line, ssize_t size)
{
	ssize_t		end_point;
	ssize_t		i;

	end_point = index + 16;
	i = index;
	while (i < end_point)
	{
		if (i < size)
			ft_printf("%02hhx", line[i]);
		else
			ft_printf("  ");
		i++;
		if (!(i % 2))
			ft_printf(" ");
	}
	return ;
}

static void			print_ascii_string(ssize_t index, char *line, ssize_t size)
{
	ssize_t		end_point;
	ssize_t		i;

	end_point = index + 8;
	i = index;
	while (i < end_point)
	{
		if (i < size)
		{
			if (ft_isprint(line[i]))
				ft_printf("%hhc", line[i]);
			else
				ft_printf(".");
		}
		else
			ft_printf("  ");
		i++;
	}
	return ;
}

void				print_hex(char *file_content, ssize_t size)
{
	ssize_t		index;
	size_t		chars_per_line;

	chars_per_line = 16;
	index = 0;
	while (index < size)
	{
		ft_printf("%08x: ", index);
		print_hex_string(index, file_content, size);
		print_ascii_string(index, file_content, size);
		ft_printf("\n");
		index += chars_per_line;
	}
	return ;
}

void				print_bin(char *file_content, ssize_t size)
{
	ssize_t		index;
	size_t		chars_per_line;

	chars_per_line = 6;
	index = 0;
	while (index < size)
	{
		ft_printf("%08x: ", index);
		print_bin_string(index, file_content, size);
		ft_printf("  ");
		print_hex_string(index, file_content, size);
		ft_printf("\n");
		index += chars_per_line;
	}
	return ;
}

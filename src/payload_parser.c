/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   payload_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:46:05 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/18 12:28:24 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

static void		remove_cr_char(char *line)
{
	size_t		length;

	length = ft_strlen(line);
	if (line[length - 1] == '\r')
		line[length - 1] = '\0';
	return ;
}

static char		*search_record_start_point(char *line)
{
	char	*start_ptr;

	start_ptr = ft_strstr(line, "!AIVDM");
	return (start_ptr);
}

char			**parse_input_line(char *line)
{
	char	*start_ptr;
	char	**aivdm_record;

	remove_cr_char(line);
	start_ptr = search_record_start_point(line);
	aivdm_record = (char **)ft_strsplit(start_ptr, ',');
	return (aivdm_record);
}

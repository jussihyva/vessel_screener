/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   payload_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:46:05 by ubuntu            #+#    #+#             */
/*   Updated: 2020/08/02 22:51:15 by ubuntu           ###   ########.fr       */
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

static char		*search_record_start_point(char *line, int *ais_dispatcher_timestamp)
{
	char	*start_ptr;
	char	*timestamp_str;
	char	saved_char;

	start_ptr = ft_strstr(line, "!AIVDM");
	saved_char = *start_ptr;
	*start_ptr = '\0';
	timestamp_str = ft_strstr(line, "c:");
	*start_ptr = saved_char;
	if (timestamp_str)
		*ais_dispatcher_timestamp = ft_atoi(timestamp_str + 2);
	return (start_ptr);
}

char			**parse_input_line(char *line, int *ais_dispatcher_timestamp)
{
	char	*start_ptr;
	char	**aivdm_record;

	remove_cr_char(line);
	start_ptr = search_record_start_point(line, ais_dispatcher_timestamp);
	aivdm_record = (char **)ft_strsplit(start_ptr, ',');
	return (aivdm_record);
}

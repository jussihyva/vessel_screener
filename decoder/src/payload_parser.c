/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   payload_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 11:46:05 by ubuntu            #+#    #+#             */
/*   Updated: 2020/08/06 13:36:09 by jkauppi          ###   ########.fr       */
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

static char		*search_record_start_point(char *line, t_message_123 *message_123)
{
	char			*start_ptr;
	char			*timestamp_str;
	char			saved_char;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start_ptr = ft_strstr(line, "!AIVDM");
	saved_char = *start_ptr;
	*start_ptr = '\0';
	timestamp_str = ft_strstr(line, "c:");
	*start_ptr = saved_char;
	message_123->timestamp.decoder = tv.tv_sec;
	if (timestamp_str)
		message_123->timestamp.ais_dispatcher = ft_atoi(timestamp_str + 2);
	return (start_ptr);
}

char			**parse_input_line(char *line, t_message_123 *message_123)
{
	char	*start_ptr;
	char	**aivdm_record;

	remove_cr_char(line);
	start_ptr = search_record_start_point(line, message_123);
	aivdm_record = (char **)ft_strsplit(start_ptr, ',');
	return (aivdm_record);
}

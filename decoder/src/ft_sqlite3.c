/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqlite3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 10:34:34 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/06 13:44:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

# define DB_PATH "../server/country.db"

void			open_sqlite3(sqlite3 **db)
{
	int			error_code;

	if ((error_code = sqlite3_open(DB_PATH, db)))
	{
		;
	}
	return ;
}

int				print_select_result(void *data, int argc, char **argv, char **column_name)
{
	(void)argc;
	(void)argv;
	(void)column_name;
	*(int *)data = 1;
	return (0);
}

void			insert_message_123(sqlite3 *db, char *line, t_message_123 *message_123)
{
	char		*sql_query_string;
	char		*error_message;
	int			error_code;

	error_message = NULL;
	print_message_123(line, message_123);
	if (message_123->message_id >= 1 && message_123->message_id <= 3)
	{
		sql_query_string = (char *)ft_memalloc(sizeof(*sql_query_string) * 100000);
		ft_sprintf(sql_query_string, "insert into message_%d (decoder_time, \
			ais_dispatcher_time, message_id, repeat_indicator, mmsi, \
			navigational_status, rate_of_turn, speed_over_ground, \
			position_accuracy, longitude, latitude, course_over_ground, \
			true_heading, timestamp, special_manoeuvre_indicator, spare, \
			raim_flag, communication_state, dummy) values (%d, %d, %d, %d, %d, %d, %d, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d%s",
			message_123->message_id,
			message_123->timestamp.decoder, message_123->timestamp.ais_dispatcher, 
			message_123->message_id,
			message_123->repeat_indicator, message_123->mmsi,
			message_123->navigational_status, message_123->rate_of_turn,
			message_123->speed_over_ground, message_123->position_accuracy,
			message_123->longitude, message_123->latitude,
			message_123->course_over_ground, message_123->true_heading,
			message_123->timestamp.vessel, message_123->special_manoeuvre_indicator,
			message_123->spare, message_123->raim_flag,
			message_123->communication_state, message_123->dummy, ")");
		if ((error_code = sqlite3_exec(db, sql_query_string, print_select_result, NULL, &error_message)))
		{
			;
		}
		ft_printf("%s\n", sql_query_string);
		ft_strdel(&sql_query_string);
	}
	return ;
}

void			select_sqlite3(sqlite3 *db, int mmsi_mid)
{
	char			*sql_query_string;
	char			*tmp1;
	char			*tmp2;
	char			*tmp3;
	int				error_code;
	int				data;
	char			*error_message;
	struct timeval	tv;

	sql_query_string = ft_strjoin("select * from country where mmsi_mid = ", ft_itoa(mmsi_mid));
	error_message = NULL;
	data = 0;
	if ((error_code = sqlite3_exec(db, sql_query_string, print_select_result, (void *)&data, &error_message)))
	{
		;
	}
	ft_strdel(&sql_query_string);
	gettimeofday(&tv, NULL);
	if (data)
	{
		tmp1 = ft_strjoin("update country set timestamp = ", ft_itoa(tv.tv_sec));
		tmp2 = ft_strjoin(" where mmsi_mid=", ft_itoa(mmsi_mid));
		sql_query_string = ft_strjoin(tmp1, tmp2);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		if ((error_code = sqlite3_exec(db, sql_query_string, print_select_result, (void *)&data, &error_message)))
		{
			;
		}
		ft_strdel(&sql_query_string);
		sql_query_string = ft_strjoin("update country set comment = '' where mmsi_mid=", ft_itoa(mmsi_mid));
		if ((error_code = sqlite3_exec(db, sql_query_string, print_select_result, (void *)&data, &error_message)))
		{
			;
		}
		ft_strdel(&sql_query_string);
	}
	else
	{
		tmp1 = ft_strjoin("insert into country (mmsi_mid,country,timestamp,comment) values (", ft_itoa(mmsi_mid));
		tmp2 = ft_strjoin(", '-', ", ft_itoa(tv.tv_sec));
		tmp3 = ft_strjoin(tmp1, tmp2);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		sql_query_string = ft_strjoin(tmp3, ", '')");
		ft_strdel(&tmp3);
		if ((error_code = sqlite3_exec(db, sql_query_string, print_select_result, NULL, &error_message)))
		{
			;
		}
		ft_strdel(&sql_query_string);
	}
	return ;
}

void			close_sqlite3(sqlite3 *db)
{
	sqlite3_close(db);
	return ;
}

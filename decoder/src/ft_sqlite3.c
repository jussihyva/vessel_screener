/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqlite3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 10:34:34 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/29 22:49:08 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"
#include <sys/time.h>

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

int		print_select_result(void *data, int argc, char **argv, char **column_name)
{
	(void)argc;
	(void)argv;
	(void)column_name;
	*(int *)data = 1;
	return (0);
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

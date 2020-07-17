/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqlite3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 10:34:34 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/16 18:11:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"
#include <sys/time.h>

void			open_sqlite3(sqlite3 **db)
{
	int			error_code;

	ft_printf("%p\n", *db);
	if ((error_code = sqlite3_open("country.db", db)))
	{
		;
	}
	ft_printf("Error: %d\n", error_code);
	ft_printf("%p\n", *db);
	return ;
}

int		print_select_result(void *data, int argc, char **argv, char **column_name)
{
	int			i;

	ft_printf("Data\n");
	*(int *)data = 1;
	ft_printf("Data: %d\n", *(int *)data);
	i = -1;
	while (++i < argc)
	{
		ft_printf("%-20s", column_name[i]);
	}
	ft_printf("\n");
	i = -1;
	while (++i < argc)
	{
		ft_printf("%-20s", argv[i]);
	}
	ft_printf("\n");
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
		ft_printf("Updated: %d\n", mmsi_mid);
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
		ft_printf("Created: %d\n", mmsi_mid);
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

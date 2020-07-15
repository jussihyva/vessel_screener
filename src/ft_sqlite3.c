/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqlite3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 10:34:34 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/15 12:02:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

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
//	int			i;

	(void)data;
	(void)argc;
	(void)argv;
	(void)column_name;
	ft_printf("Data\n");
//	ft_printf("Data: %s\n", data);
	// i = -1;
	// while (++i < argc)
	// {
	// 	ft_printf("%s\n", column_name[i]);
	// }
	// while (++i < argc)
	// {
	// 	ft_printf("%s\n", argv[i]);
	// }
	return (0);
}
void			select_sqlite3(sqlite3 *db)
{
	char		*sql_query_string;
	int			error_code;
	char		*data;
	char		*error_message;

	sql_query_string = ft_strdup("select mmsi_mid from country");
	data = ft_strdup("MOI\n");
	error_message = NULL;
	if ((error_code = sqlite3_exec(db, sql_query_string, (void *)data, print_select_result, &error_message)))
	{
		;
	}
	ft_printf("Error message: %s\n", error_message);
	ft_strdel(&sql_query_string);
//	ft_strdel(&data);
	return ;
}

void			close_sqlite3(sqlite3 *db)
{
	sqlite3_close(db);
	return ;
}
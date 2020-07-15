/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqlite3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 10:34:34 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/15 18:01:53 by jkauppi          ###   ########.fr       */
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
	int			i;

	(void)argc;
	(void)argv;
	(void)column_name;
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
void			select_sqlite3(sqlite3 *db)
{
	char		*sql_query_string;
	int			error_code;
	int			data;
	char		*error_message;

	sql_query_string = ft_strdup("select * from country where mmsi_mid = 230");
	error_message = NULL;
	data = 0;
	if ((error_code = sqlite3_exec(db, sql_query_string, print_select_result, (void *)&data, &error_message)))
	{
		;
	}
	if (data)
		ft_printf("Updated: %d\n", 230);
	else
		ft_printf("Created: %d\n", 230);
	ft_strdel(&sql_query_string);
	return ;
}

void			close_sqlite3(sqlite3 *db)
{
	sqlite3_close(db);
	return ;
}
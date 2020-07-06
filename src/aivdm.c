/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:21:53 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/06 08:09:16 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

static void		print_payload(char *payload)
{
	(void)payload;
	return ;
}

static int		validate_record(char validate_char, char *line, size_t *ok_cnt,
														size_t number_of_fields)
{
	t_error_code	error;

	error = 0;
	if (validate_char == '*' && number_of_fields == NUM_OF_FIELDS)
	{
		if (number_of_fields != NUM_OF_FIELDS)
			error = e_invalid_num_of_fields;
		else
			error = e_invalid_check_sum;
		(*ok_cnt)++;
		if (!(*ok_cnt % PRINT_OK))
			ft_printf("OK (%d)\n", *ok_cnt);
		return (0);
	}
	else
	{
		ft_printf("ERROR (%s)\n", line);
		return (1);
	}
}

static size_t	print_record(char **aivdm_record_array)
{
	size_t		i;
	int			is_first;
	int			length;

	is_first = 1;
	i = -1;
	while (aivdm_record_array[++i])
	{
		if(!is_first)
			is_first = 0;
		else
			ft_printf("\t");
		if (i == 5)
			ft_printf("???");
		else if (i == 6)
		{
			length = ft_strlen(aivdm_record_array[i]);
			aivdm_record_array[i][length - 1] = '\0';
			ft_printf("%s", aivdm_record_array[i]);
		}
		else
			ft_printf("%s", aivdm_record_array[i]);
	}
	ft_printf("\n");
	return (i);
}

int				main()
{
	char		*line;
	char		**aivdm_record_array;
	size_t		number_of_fields;
	size_t		ok_cnt;

	line = NULL;
	ok_cnt = 0;
	while (1)
	{
		ft_get_next_line(0, &line);
		aivdm_record_array = ft_strsplit(line, ',');
		number_of_fields = print_record(aivdm_record_array);
		if (validate_record(aivdm_record_array[number_of_fields - 1][1], line,
													&ok_cnt, number_of_fields))
			break ;
		print_payload(aivdm_record_array[0]);
		ft_strdel(&line);
	}
	return (0);
}

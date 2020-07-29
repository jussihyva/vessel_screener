/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 16:24:03 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/18 11:44:44 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aivdm.h"

void			ft_step_args(int *argc, char ***argv)
{
	(*argc)--;
	(*argv)++;
	return ;
}

static int		open_file(int *argc, char ***argv)
{
	int		fd;
	char	*file_path;

	fd = 0;
	if (*argc > 0)
	{
		file_path = (*argv)[0];
		fd = open(file_path, O_RDONLY);
	}
	return (fd);
}

void			ft_read_opt(t_opt *opt, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-f"))
		{
			ft_step_args(argc, argv);
			opt->flags |= e_file;
			opt->fd = open_file(argc, argv);
		}
		else if (ft_strequ((*argv)[0], "-l"))
			opt->flags |= e_leaks;
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}

int				validate_input_record(char **aivdm_record_array, char *line,
																size_t *ok_cnt)
{
	t_error_code	error;
	size_t			number_of_fields;
	char			validate_char;

	error = 0;
	number_of_fields = -1;
	while (aivdm_record_array[++number_of_fields])
		;
	if (number_of_fields && ft_strcmp(aivdm_record_array[0], "!AIVDM"))
		error = e_unknown_message_type;
	else if (number_of_fields != NUM_OF_FIELDS)
		error = e_invalid_num_of_fields;
	else
	{
		validate_char = aivdm_record_array[number_of_fields - 1][1];
		if (validate_char != '*')
			error = e_invalid_check_sum;
		else
		{
			(*ok_cnt)++;
			if (!(*ok_cnt % PRINT_OK))
				ft_printf("OK (%d)\n", *ok_cnt);
		}
	}
	if (error && *line)
		ft_printf("ERROR (%s)\n", line);
	return (error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 16:24:03 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/09 17:20:41 by jkauppi          ###   ########.fr       */
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
		ft_step_args(argc, argv);
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
			opt->fd = open_file(argc, argv);
		}
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}


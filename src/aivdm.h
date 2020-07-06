/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aivdm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:23:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/06 07:42:34 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AIVDM_H
# define AIVDM_H
# include "libft.h"
# include "ft_printf.h"

# define PRINT_OK 500
# define NUM_OF_FIELDS 7

typedef enum		e_error_code
{
	e_invalid_num_of_fields = 1,
	e_invalid_check_sum
}					t_error_code;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 18:00:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/10 08:57:18 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	size_t	count_len(t_substring *substring)
{
	size_t		string_len;

	string_len = 0;
	string_len += substring->o_string.pre_filler.content_size;
	string_len += substring->o_string.sign.content_size;
	string_len += substring->o_string.prefix.content_size;
	string_len += substring->o_string.zero_filler.content_size;
	string_len += substring->o_string.parameter.content_size;
	string_len += substring->o_string.post_filler.content_size;
	return (string_len);
}

static void		add_substrings(t_substring *substring, char *s)
{
	size_t				i;
	t_output_string		o_s;

	o_s = substring->o_string;
	i = 0;
	if (o_s.pre_filler.content)
		ft_strcat(s + i, o_s.pre_filler.content);
	if (o_s.sign.content)
		ft_strcat((s += o_s.pre_filler.content_size), o_s.sign.content);
	if (o_s.prefix.content)
		ft_strcat((s += o_s.sign.content_size), o_s.prefix.content);
	if (o_s.zero_filler.content)
		ft_strcat((s += o_s.prefix.content_size), o_s.zero_filler.content);
	if (o_s.parameter.content)
	{
		if (o_s.add_null)
			ft_strcat((s += o_s.zero_filler.content_size), "");
		else
			ft_strcat((s += o_s.zero_filler.content_size),
													o_s.parameter.content);
	}
	if (o_s.post_filler.content)
		ft_strcat((s += o_s.parameter.content_size), o_s.post_filler.content);
	return ;
}

static void		write_output_string(size_t *words, t_list **substring_list,
																char *buffer)
{
	size_t			string_len;
	t_list			*substring_elem;
	t_substring		*substring;
	char			*s;

	substring_elem = *substring_list;
	while (substring_elem)
	{
		substring = (t_substring *)(substring_elem->content);
		string_len = count_len(substring);
		if (string_len && buffer)
		{
			s = ft_strnew(string_len);
			s[0] = '\0';
			add_substrings(substring, s);
			ft_memcpy(buffer + *words, s, string_len);
			ft_strdel(&s);
		}
		*words += string_len;
		substring_elem = substring_elem->next;
	}
}

size_t			print_formatted_string(t_list **substring_list, int fd,
																char *str)
{
	size_t			words;
	char			*buffer;

	words = 0;
	write_output_string(&words, substring_list, NULL);
	buffer = ft_strnew(words);
	words = 0;
	write_output_string(&words, substring_list, buffer);
	if (str)
		ft_memcpy(str, buffer, words + 1);
	else
		ft_putlstr_fd(buffer, words, fd);
	ft_strdel(&buffer);
	return (words);
}

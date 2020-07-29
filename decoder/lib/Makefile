# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 10:35:04 by ubuntu            #+#    #+#              #
#    Updated: 2020/07/05 21:15:18 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LOG					=	/var/tmp/aivdm_decoder_lib_make_1.log
LIBFT_H				=	libft.h
FT_PRINTF_H			=	ft_printf.h
LIBFT_A				=	libft.a
FT_PRINTF_A			=	libftprintf.a

LIBFT_FOLDER		=	./libft
FT_PRINTF_FOLDER	=	./ft_printf/src

all: rm_log libft ft_printf headers archives

headers: $(LIBFT_H) $(FT_PRINTF_H)

$(LIBFT_H): $(LIBFT_FOLDER)/$(LIBFT_H)
	cp $(LIBFT_FOLDER)/$(LIBFT_H) ./ | tee $(LOG)

$(FT_PRINTF_H): $(FT_PRINTF_FOLDER)/$(FT_PRINTF_H)
	cp $(FT_PRINTF_FOLDER)/$(FT_PRINTF_H) ./ | tee $(LOG)

archives: $(LIBFT_A) $(FT_PRINTF_A)

$(LIBFT_A): $(LIBFT_FOLDER)/$(LIBFT_A)
	cp $(LIBFT_FOLDER)/$(LIBFT_A) ./ | tee $(LOG)

$(FT_PRINTF_A): $(FT_PRINTF_FOLDER)/../$(FT_PRINTF_A)
	cp $(FT_PRINTF_FOLDER)/../$(FT_PRINTF_A) ./ | tee $(LOG)

libft:
	@make -C ${LIBFT_FOLDER} >> $(LOG)

ft_printf:
	@make -C ${FT_PRINTF_FOLDER}/.. >> $(LOG)

rm_log:
	@\rm -f $(LOG)

log: all
	@cat $(LOG)

.PHONY: all libft ft_printf headers arcaives rm_log log

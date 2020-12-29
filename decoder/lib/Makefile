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

LIB_FILES			=	libft.a libjk.a libftprintf.a
H_FILES				=	$(patsubst %.a, %.h, $(LIB_FILES))
LIB_FOLDERS			=	$(patsubst %.a, %, $(LIB_FILES))

all: $(LIB_FOLDERS) make_libraries

$(LIB_FOLDERS):
	mkdir $@

make_libraries:
	for folder in $(LIB_FOLDERS) ; do \
		make -C $$folder ; \
	done

clean:
	for folder in $(LIB_FOLDERS) ; do \
		make -C $$folder clean ; \
	done

fclean:
	rm -f $(H_FILES)
	rm -f $(LIB_FILES)
	for folder in $(LIB_FOLDERS) ; do \
		make -C $$folder fclean ; \
	done

re: fclean all

.PHONY: all clean fclean re make_libraries

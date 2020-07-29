# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/04 11:34:07 by jkauppi           #+#    #+#              #
#    Updated: 2020/06/19 09:28:45 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libftprintf.a
SRC_FOLDER		=	./src

LIBFT_FOLDER	=	./libft
LIBFT_NAME		=	ft
OBJ_FOLDER		=	./obj
CC				=	clang

INCLUDES		=	-I ${SRC_FOLDER} -I ${LIBFT_FOLDER}
CFLAGS			=	-g -Wall -Werror -Wextra ${INCLUDES}

SRC_FILES		=	ft_printf.c split_input_string.c create_converters.c \
					ft_lltoa_base.c ft_ulltoa_base.c param_type.c \
					width_and_prediction.c modify_character.c \
					modify_string.c modify_pointer.c modify_integer.c \
					modify_octal.c modify_hex.c modify_unsigned_integer.c \
					release_memory_2.c read_param.c modify_float.c \
					formatters.c ft_dtoa_base.c ft_numlen.c ft_round.c \
					set_substring_common_1.c set_substring_common_2.c \
					set_substring_zero.c \
					print_output_string.c ft_putlstr_fd.c release_memory_1.c
HEADER_FILE		=	ft_printf.h
SRC_PATHS		=	${addprefix ${SRC_FOLDER}/, ${SRC_FILES}}
OBJ_PATHS		=	${addprefix ${OBJ_FOLDER}/, ${patsubst %.c,%.o,${SRC_FILES}}}
LIBFT_FILES		=	ft_putstr.o ft_putstr_fd.o ft_strlen.o ft_putchar.o \
					ft_putchar_fd.o ft_putnbr.o ft_putnbr_fd.o ft_lstadd_e.o \
					ft_memalloc.o ft_strchr.o ft_strnew.o ft_bzero.o \
					ft_memchr.o ft_memset.o ft_strdel.o ft_memdel.o ft_itoa.o \
					ft_strjoin.o ft_strcpy.o ft_memmove.o ft_toupper.o \
					ft_islower.o ft_lstdel.o ft_lstdelone.o ft_strdup.o \
					ft_putendl.o ft_lstnew.o ft_memcpy.o ft_strncmp.o \
					ft_atoi.o ft_isdigit.o ft_isspace.o ft_strcat.o \
					ft_strncpy.o ft_memccpy.o ft_strnequ.o ft_lstadd.o
LIBFT_PATHS		=	${addprefix ${LIBFT_FOLDER}/, ${LIBFT_FILES}}

all: ${NAME}

${NAME}:  ${OBJ_PATHS}
	ar -rcs ${NAME} ${OBJ_PATHS} ${LIBFT_PATHS}

${OBJ_PATHS}:${OBJ_FOLDER}/%.o: ${SRC_FOLDER}/%.c ${SRC_FOLDER}/${HEADER_FILE} | $(OBJ_FOLDER)
	make -C ${LIBFT_FOLDER}
	${CC} ${CFLAGS} -c -o $@ $<

$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

clean:
	\rm -f ${OBJ_FOLDER}/*.o
	make -C ${LIBFT_FOLDER} clean

fclean: clean
	\rm -f ${NAME}
	make -C ${LIBFT_FOLDER} fclean

re: fclean all

.PHONY: re fclean clean all


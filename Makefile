# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 11:36:37 by ubuntu            #+#    #+#              #
#    Updated: 2020/07/15 10:58:05 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	aivdm
CC			=	gcc
C_FLAGS		=	-g -Wall -Werror -Wextra
LIB_FOLDER	=	lib
INCLUDES	=	-I $(LIB_FOLDER)
LIB			=	-L $(LIB_FOLDER) -l ft -l ftprintf -l sqlite3

SRC			=	print_hex.c input.c memory.c message_123.c ft_sqlite3.c

HEADERS		=	*.h

SRC_FOLDER	=	src

NAME_MAIN	=	$(SRC_FOLDER)/aivdm.c

HEADER_LIST	=	$(addprefix $(SRC_FOLDER)/, $(HEADERS))

OBJ_FOLDER	=	obj
OBJ			=	$(addprefix $(OBJ_FOLDER)/, $(patsubst %.c, %.o, $(SRC)))

all: make_lib $(NAME)

$(NAME): $(OBJ) $(NAME_MAIN) $(HEADER_LIST)
	@echo "$@ created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -o $@ $(OBJ) $(NAME_MAIN) $(LIB)

$(OBJ): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER_LIST) | $(OBJ_FOLDER)
	@echo "$(@) created."
	@$(CC) $(C_FLAGS) $(INCLUDES) -c -o $@ $<

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

make_lib:
	@make -C ${LIB_FOLDER} 1>/dev/null

.PHONY: all make_lib

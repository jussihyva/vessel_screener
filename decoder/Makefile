# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 11:36:37 by ubuntu            #+#    #+#              #
#    Updated: 2020/07/18 11:51:52 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

APP_NAMES		=	aivdm
CC				=	clang
CFLAGS			=	-g -Wall -Werror -Wextra
SRC				=	src
OBJ				=	obj
INCLUDE			=	include
FOLDERS			=	$(SRC) $(OBJ) $(INCLUDE)
LIB_FOLDER		=	lib
INCLUDES		=	-I $(LIB_FOLDER)
LIBS			=	libftprintf.a libft.a libjk.a libsqlite3.a \
					libssl.a libcrypto.a
TMP_LIB_FILES	=	$(patsubst lib%.a, %, $(LIBS))
LIB_FILES		=	$(addprefix -l , $(patsubst lib%.so, %, $(TMP_LIB_FILES)))
INCLUDES		=	-I $(INCLUDE) -I $(LIB_FOLDER)

MAIN_C_FILES	=	$(addprefix $(SRC)/, $(patsubst %, %.c, $(APP_NAMES)))
C_FILE_NAMES	=	print_hex.c input.c memory.c message_123.c ft_sqlite3.c \
					payload_parser.c setup_influxdb_connection.c \
					write_influxdb.c store_messages.c
C_FILES			=	$(addprefix $(SRC)/, $(C_FILE_NAMES))
H_FILES			=	aivdm.h message_123.h
HEADERS			=	$(addprefix $(INCLUDE)/, $(H_FILES))
OBJECTS			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(C_FILE_NAMES)))

all: $(FOLDERS) $(MAIN_C_FILES) $(C_FILES) $(APP_NAMES)
	@echo "$(GREEN)Done!$(END)"

$(APP_NAMES): %: $(SRC)/%.c $(OBJECTS) $(HEADERS) $(MAIN_C_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< $(OBJECTS) \
							-L $(LIB_FOLDER) $(LIB_FILES)

$(OBJECTS): $(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(HEADERS):
	touch $@

$(MAIN_C_FILES):
	touch $@

$(C_FILES):
	touch $@

$(FOLDERS):
	mkdir $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(APP_NAMES)

re: fclean all

.PHONY: all clean fclean re

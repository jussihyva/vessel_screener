NAME				=	libjk.a
LIB_FOLDER			=	..
AR_FILE				=	$(LIB_FOLDER)/$(NAME)
SRC					=	src
OBJ					=	obj
INCLUDE				=	include
INCLUDES			=	-I $(INCLUDE) -I $(LIB_FOLDER)
FOLDERS				=	$(SRC) $(OBJ) $(INCLUDE)

SRC_FILES			=	jk_start_tls_client.c jk_setup_tls_connection.c \
						jk_create_ctx.c
H_FILES				=	libjk.h
HEADERS				=	$(addprefix $(INCLUDE)/, $(H_FILES))
LN_HEADERS			=	$(addprefix $(LIB_FOLDER)/, $(H_FILES))
C_FILES				=	$(addprefix $(SRC)/, $(SRC_FILES))
OBJECTS				=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_FILES)))

all: $(FOLDERS) $(HEADERS) $(C_FILES) $(NAME) $(AR_FILE) $(LN_HEADERS)
	@echo "Done!"

$(NAME): $(OBJECTS) Makefile
	ar -rcs $(NAME) $(OBJECTS)

$(AR_FILE): $(LIB_FOLDER)/%: %
	ln -s -r -t $(LIB_FOLDER) $<

$(LN_HEADERS): $(LIB_FOLDER)/%: $(INCLUDE)/%
	ln -s -r -t $(LIB_FOLDER) $<

$(OBJECTS): $(OBJ)/%.o: $(SRC)/%.c $(HEADERS) Makefile
	$(CC) $(TRUSTED_CFLAGS) $(INCLUDES) -c -o $@ $<

$(HEADERS):
	touch $@

$(C_FILES):
	touch $@

$(FOLDERS):
	mkdir $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	for folder in $(LN_HEADERS) ; do \
		rm -f $$folder ; \
	done

re: fclean all

.PHONY: all clean fclean re

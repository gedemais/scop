NAME=scop

CC=gcc
FLAGS= -Wall -Werror -Wextra -Weverything

# Flags variables
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    FLAGS += -g3 -fsanitize=address
endif

OPTI ?= 0
ifeq ($(OPTI), 1)
    FLAGS += -Ofast -march=native
endif

SRC_PATH=src/
SRC_NAME=main.c\
		 error.c\
		 free.c\
		 setup/settings.c\
		 setup/setup.c\
		 setup/setup_utils.c

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))

INC_PATH=include/
INC_NAME=main.h\
		 error.h
INC=$(addprefix $(INC_PATH), $(INC_NAME))

OBJS=$(SRC:.c=.o)

########################## Librarys ######################
LIB_PATH = libft/
LIB = libft/libft.a
LIB_GLAD = glad/include/
GLAD = glad/libglad.a
##########################################################

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -I$(LIB_GLAD) -o $(NAME) $(OBJS) $(LIB) $(GLAD) -lpthread -lglfw -framework OpenGL

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@tput civis
	@printf " Compiling $<"
	@printf "                                       \\r"
	@tput cnorm
	@$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -o $@ -c $<

$(LIB): $(LIB_PATH)
	@echo "Making Libft..."
	@make -C $(LIB_PATH) -j4

clean:
	@rm -rf $(OBJS)
	@make -C $(LIB_PATH) clean
	@echo "Libft clean"

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all

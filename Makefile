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
		 parser/load_obj_file.c\
		 parser/load_faces.c\
		 parser/load_mtl_file.c\
		 parser/mtl_loaders.c\
		 init/settings.c\
		 init/init.c\
		 init/init_utils.c

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))

INC_PATH=include/
INC_NAME=main.h\
		 error.h\
		 parser.h\
		 scene.h

INC=$(addprefix $(INC_PATH), $(INC_NAME))

OBJS=$(SRC:.c=.o)

########################## Librarys ######################
LIBS_PATH=libs

LIB_PATH=$(LIBS_PATH)/libft
LIB=$(LIB_PATH)/libft.a

LIB_VEC_PATH=$(LIBS_PATH)/lib_vec
LIB_VEC=$(LIB_VEC_PATH)/lib_vec.a

LIBBMP_PATH=$(LIBS_PATH)/libbmp
LIBBMP=$(LIBBMP_PATH)/libbmp.a
##########################################################

all: $(NAME)

$(NAME): $(LIB) $(LIB_VEC) $(LIBBMP) $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB) $(LIB_VEC) $(LIBBMP) -lpthread -framework OpenGL

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@tput civis
	@printf " Compiling $<"
	@printf "                                       \\r"
	@tput cnorm
	@$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -I$(LIB_VEC_PATH) -I$(LIBBMP_PATH) -o $@ -c $<

$(LIB): $(LIB_PATH)
	@echo "Making Libft..."
	@make -C $(LIB_PATH)

$(LIB_VEC): $(LIB_VEC_PATH)
	@echo "Making lib_vec..."
	@make -C $(LIB_VEC_PATH)

$(LIBBMP): $(LIBBMP_PATH)
	@echo "Making libbmp..."
	@make -C $(LIBBMP_PATH)

clean:
	@rm -rf $(OBJS)
	@make -C $(LIB_PATH) clean
	@make -C $(LIB_VEC_PATH) clean
	@make -C $(LIBBMP_PATH) clean

fclean: clean
	@make -C $(LIB_PATH) fclean
	@make -C $(LIB_VEC_PATH) fclean
	@make -C $(LIBBMP_PATH) fclean
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all

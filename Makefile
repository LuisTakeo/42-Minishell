CC := gcc
FLAGS := -Wall -Werror -Wextra

LIBS_FOLDER := ./libs
LIBFT := $(addprefix $(LIBS_FOLDER), /libft)
LIBS := $(addprefix $(LIBFT), /libft.a)

NAME := minishell

HEADER := src/includes/minishell.h

# SRC
SRC_FOLDER := src/
SRC_MAIN := $(addsuffix .c, main )
SRC := $(addprefix $(SRC_FOLDER), $(SRC_MAIN))
OBJS_FOLDER := obj/
OBJS := $(SRC:$(SRC_FOLDER)%.c=$(OBJS_FOLDER)%.o)

# Objects do SRC
$(OBJS_FOLDER)%.o:$(SRC_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJS_FOLDER)
	@$(CC) $(FLAGS) -o $@ -c $< && echo "Compilando: $(notdir $<)"

# CD
SRC_CD_FOLDER := $(SRC_FOLDER)cd/
SRC_CD := $(addprefix $(SRC_CD_FOLDER), $(addsuffix .c, cd))
OBJ_CD_FOLDER := $(OBJS_FOLDER)cd/
OBJS_CD := $(SRC_CD:$(SRC_CD_FOLDER)%.c=$(OBJ_CD_FOLDER)%.o)

# Objects do CD
$(OBJ_CD_FOLDER)%.o:$(SRC_CD_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_CD_FOLDER)
	@$(CC) $(FLAGS) -o $@ -c $< && echo "Compilando: $(notdir $<)"


# Variavel para receber todos os objects
ALL_OBJ := $(OBJS) $(OBJS_CD)

######################################################################
# $(NAME)

$(NAME): libft $(ALL_OBJ)
	@$(CC) $(ALL_OBJ) $(LIBS) -o $(NAME) -lreadline
	@echo "Compilando executável $@"

all: $(NAME)

teste:
	@echo $(SRC_CD)

libft:
	@echo "Compilando Libft..."
	@make all bonus new_fun -C $(LIBFT) --no-print-directory

clean:
	@echo "Removendo objects..."
	@rm -rf obj
	@make clean -C $(LIBFT) --no-print-directory
	@echo "Pronto!"

fclean: clean
	@echo "Removendo executáveis..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT) --no-print-directory
	@echo "Feito!"

re: fclean all

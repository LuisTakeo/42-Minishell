CC := gcc
FLAGS := -Wall -Werror -Wextra

LIBS_FOLDER := ./libs
LIBFT := $(addprefix $(LIBS_FOLDER), /libft)
LIBS := $(addprefix $(LIBFT), /libft.a)

NAME := minishell

HEADER := src/includes/minishell.h

# SRC
SRC_FOLDER := src/
SRC_MAIN := $(addsuffix .c, main)
SRC := $(addprefix $(SRC_FOLDER), $(SRC_MAIN))
OBJS_FOLDER := obj/
OBJS := $(SRC:$(SRC_FOLDER)%.c=$(OBJS_FOLDER)%.o)

# SRC Objects
$(OBJS_FOLDER)%.o:$(SRC_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJS_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# CD
SRC_CD_FOLDER := $(SRC_FOLDER)cd/
SRC_CD := $(addprefix $(SRC_CD_FOLDER), $(addsuffix .c, cd))
OBJ_CD_FOLDER := $(OBJS_FOLDER)cd/
OBJS_CD := $(SRC_CD:$(SRC_CD_FOLDER)%.c=$(OBJ_CD_FOLDER)%.o)

# CD Objects
$(OBJ_CD_FOLDER)%.o:$(SRC_CD_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_CD_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# TOKENS
SRC_TOKENS_FOLDER := $(SRC_FOLDER)tokens/
SRC_TOKENS := $(addprefix $(SRC_TOKENS_FOLDER), $(addsuffix .c, get_token free_token quotes))
OBJ_TOKENS_FOLDER := $(OBJS_FOLDER)tokens/
OBJS_TOKENS := $(SRC_TOKENS:$(SRC_TOKENS_FOLDER)%.c=$(OBJ_TOKENS_FOLDER)%.o)

# TOKENS Objects
$(OBJ_TOKENS_FOLDER)%.o:$(SRC_TOKENS_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_TOKENS_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# ENV
SRC_ENV_FOLDER := $(SRC_FOLDER)env/
SRC_ENV := $(addprefix $(SRC_ENV_FOLDER), $(addsuffix .c, get_env get_paths))
OBJ_ENV_FOLDER := $(OBJS_FOLDER)env/
OBJS_ENV := $(SRC_ENV:$(SRC_ENV_FOLDER)%.c=$(OBJ_ENV_FOLDER)%.o)

# ENV Objects
$(OBJ_ENV_FOLDER)%.o:$(SRC_ENV_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_ENV_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# EXEC
SRC_EXEC_FOLDER := $(SRC_FOLDER)exec/
SRC_EXEC := $(addprefix $(SRC_EXEC_FOLDER), $(addsuffix .c, exec_command verify_path ))
OBJ_EXEC_FOLDER := $(OBJS_FOLDER)exec/
OBJS_EXEC := $(SRC_EXEC:$(SRC_EXEC_FOLDER)%.c=$(OBJ_EXEC_FOLDER)%.o)

# EXEC Objects
$(OBJ_EXEC_FOLDER)%.o:$(SRC_EXEC_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_EXEC_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# Variavel para receber todos os objects
ALL_OBJ := $(OBJS) $(OBJS_CD) $(OBJS_TOKENS) $(OBJS_ENV) $(OBJS_EXEC)

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

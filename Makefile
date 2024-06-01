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

# TOKENS
SRC_TOKENS_FOLDER := $(SRC_FOLDER)tokens/
SRC_TOKENS := $(addprefix $(SRC_TOKENS_FOLDER), $(addsuffix .c, get_token get_token_utils get_quoted_token get_operator))
OBJ_TOKENS_FOLDER := $(OBJS_FOLDER)tokens/
OBJS_TOKENS := $(SRC_TOKENS:$(SRC_TOKENS_FOLDER)%.c=$(OBJ_TOKENS_FOLDER)%.o)

# TOKENS Objects
$(OBJ_TOKENS_FOLDER)%.o:$(SRC_TOKENS_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_TOKENS_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# EXPANSOR
SRC_EXPANSOR_FOLDER := $(SRC_FOLDER)expansor/
SRC_EXPANSOR := $(addprefix $(SRC_EXPANSOR_FOLDER), $(addsuffix .c, expand_env))
OBJ_EXPANSOR_FOLDER := $(OBJS_FOLDER)expansor/
OBJS_EXPANSOR := $(SRC_EXPANSOR:$(SRC_EXPANSOR_FOLDER)%.c=$(OBJ_EXPANSOR_FOLDER)%.o)

# EXPANSOR Objects
$(OBJ_EXPANSOR_FOLDER)%.o:$(SRC_EXPANSOR_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_EXPANSOR_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# ENV
SRC_ENV_FOLDER := $(SRC_FOLDER)env/
SRC_ENV := $(addprefix $(SRC_ENV_FOLDER), $(addsuffix .c, get_env get_paths env))
OBJ_ENV_FOLDER := $(OBJS_FOLDER)env/
OBJS_ENV := $(SRC_ENV:$(SRC_ENV_FOLDER)%.c=$(OBJ_ENV_FOLDER)%.o)

# ENV Objects
$(OBJ_ENV_FOLDER)%.o:$(SRC_ENV_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_ENV_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# EXEC
SRC_EXEC_FOLDER := $(SRC_FOLDER)exec/
SRC_EXEC := $(addprefix $(SRC_EXEC_FOLDER), $(addsuffix .c, exec_command verify_path))
OBJ_EXEC_FOLDER := $(OBJS_FOLDER)exec/
OBJS_EXEC := $(SRC_EXEC:$(SRC_EXEC_FOLDER)%.c=$(OBJ_EXEC_FOLDER)%.o)

# EXEC Objects
$(OBJ_EXEC_FOLDER)%.o:$(SRC_EXEC_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_EXEC_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# BUILTINS
SRC_BUILTINS_FOLDER := $(SRC_FOLDER)builtins/
SRC_BUILTINS := $(addprefix $(SRC_BUILTINS_FOLDER), $(addsuffix .c, change_dir pwd unset export export_utils echo is_builtin))
OBJ_BUILTINS_FOLDER := $(OBJS_FOLDER)builtins/
OBJS_BUILTINS := $(SRC_BUILTINS:$(SRC_BUILTINS_FOLDER)%.c=$(OBJ_BUILTINS_FOLDER)%.o)

# BUILTINS Objects
$(OBJ_BUILTINS_FOLDER)%.o:$(SRC_BUILTINS_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_BUILTINS_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# TREE
SRC_TREE_FOLDER := $(SRC_FOLDER)tree/
SRC_TREE := $(addprefix $(SRC_TREE_FOLDER), $(addsuffix .c, ft_newtreenode ft_treeaddonsides ft_generate_tree ft_generate_args))
OBJ_TREE_FOLDER := $(OBJS_FOLDER)tree/
OBJS_TREE := $(SRC_TREE:$(SRC_TREE_FOLDER)%.c=$(OBJ_TREE_FOLDER)%.o)

# TREE Objects
$(OBJ_TREE_FOLDER)%.o:$(SRC_TREE_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJ_TREE_FOLDER)
	@$(CC) $(FLAGS) -g3 -o $@ -c $< && echo "Compilando: $(notdir $<)"

# Variavel para receber todos os objects
ALL_OBJ := $(OBJS) $(OBJS_TOKENS) $(OBJS_ENV) $(OBJS_EXEC) $(OBJS_BUILTINS) $(OBJS_TREE) $(OBJS_EXPANSOR)

######################################################################
# $(NAME)

$(NAME): libft $(ALL_OBJ)
	@$(CC) $(ALL_OBJ) $(LIBS) -o $(NAME) -lreadline
	@echo "Compilando executável $@"

all: $(NAME)

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

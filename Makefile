CC := gcc
FLAGS := -Wall -Werror -Wextra

LIBS_FOLDER := ./libs/
LIBFT := $(addprefix $(LIBS_FOLDER), /libft)
LIBS := $(addprefix $(LIBFT), /libft.a)

NAME := minishell


HEADER := src/includes/minishell.h

SRC_FOLDER := src/
SRC_FILES := $(addsuffix .c, main )

SRC := $(addprefix $(SRC_FOLDER), $(SRC_FILES))

OBJS_FOLDER := obj/
OBJS := $(SRC:$(SRC_FOLDER)%.c=$(OBJS_FOLDER)%.o)


all: libft $(NAME)

bonus: libft $(NAME_BONUS)

libft:
	@echo "Compilando Libft..."
	@make all bonus new_fun -C $(LIBFT) $(FLAGS) --no-print-directory

clean:
	@echo "Removendo objects..."
	@rm -rf obj
	@make clean -C $(LIBFT) $(FLAGS) --no-print-directory
	@echo "Pronto!"

fclean: clean
	@echo "Removendo executáveis..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT) $(FLAGS) --no-print-directory
	@echo "Feito!"

re: fclean all

$(OBJS_FOLDER)%.o:$(SRC_FOLDER)%.c $(HEADER)
	@mkdir -p $(OBJS_FOLDER)
	@$(CC) $(FLAGS) -o $@ -c $< && echo "Compilando: $(notdir $<)"


$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "Compilando executável $@"

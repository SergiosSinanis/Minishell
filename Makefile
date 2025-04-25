NAME = minishell

INCLUDES = ./includes ./srcs/gnl ./srcs/libft

SRCS_DIR		= ./srcs
GNL_DIR			= ./srcs/gnl
LIBFT_DIR		= ./srcs/libft
BUILTINS_DIR		= ./srcs/builtins
EXECUTION_DIR		= ./srcs/execution
PARSING_DIR		= ./srcs/parsing
EXPAND_DIR		= ./srcs/expand
MAIN_DIR		= ./srcs/main
SIGNALS_DIR		= ./srcs/signals
TOKENIZATION_DIR	= ./srcs/tokenization
UTILS_DIR		= ./srcs/utils

BUILTINS_SRC		= ${addprefix ${BUILTINS_DIR}/, builtins_cd.c builtins_echo.c builtins_env.c builtins_exit.c builtins_pwd.c builtins_unset.c builtins_export.c builtins_export_utils.c builtins_utils.c}
EXECUTION_SRC		= ${addprefix ${EXECUTION_DIR}/, exec.c exec_utils.c exec_redirection.c exec_heredoc.c exec_path.c}
EXPAND_SRC		= ${addprefix $(EXPAND_DIR)/, expand.c expand_utils.c}
MAIN_SRC		= ${addprefix $(MAIN_DIR)/, shell_token.c shell_input.c shell_loop.c shell_exec.c main.c}
SIGNALS_SRC		= ${addprefix $(SIGNALS_DIR)/, signals.c}
TOKENIZATION_SRC	= ${addprefix $(TOKENIZATION_DIR)/, ft_split_args.c ft_split_args_utils.c token_to_list.c lexing.c}
UTILS_SRC		= ${addprefix $(UTILS_DIR)/, utils.c}
GNL_SRC			= ${addprefix ${GNL_DIR}/, get_next_line.c}
PARSING_SRC		= ${addprefix $(PARSING_DIR)/, parse_utils.c parse_heredoc.c parse_loop.c parse_operators.c parse_files.c parse_pipe.c parse_redirection.c unquote.c}

SRCS = $(GNL_SRC) $(UTILS_SRC) $(BUILTINS_SRC) $(EXECUTION_SRC) $(PARSING_SRC) $(EXPAND_SRC) $(MAIN_SRC) $(SIGNALS_SRC) $(TOKENIZATION_SRC)

OBJ = $(SRCS:%.c=%.o)

OBJS = $(OBJ)

CC = cc

CFLAGS 			= -Wall -Wextra -Werror -g3 -I./includes -I/usr/local/opt/readline/include

LDFLAGS			= -L/usr/local/opt/readline/lib -lreadline -lhistory

LIBFT 			= $(LIBFT_DIR)/libft.a

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)

clean:
		rm -rf $(OBJS)
		make -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(NAME)
		make -C $(LIBFT_DIR) fclean

re: fclean all

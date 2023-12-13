include makerc/colors.mk

################################################################################

NAME			:= cub3d
SRC_DIR			:= src
BUILD_DIR		:= build
MAIN			:= main.c
RM				:= rm -rvf

HEADERS			= include/cubed.h
CC				= gcc

################################################################################

# Includes
INCLUDES	= -I ./libft -I ./libft/ft_printf

# Libraries
PRINTF = ./libft/ft_printf/libftprintf.a
LIBFT = ./libft/libft.a

################################################################################

CFLAGS			= -Wall -Wextra -Werror -Wpedantic
INCLUDE_FLAGS	:= $(addprefix -I, $(sort $(dir $(HEADERS))))

ifdef	DEBUG
	CFLAGS		+=-g
endif

ifdef	FSAN
	CFLAGS		+=-fsanitize=address,undefined
endif

################################################################################

# Source files
SRC =	src/setup/input_error_handling.c \
		# setup/input_initialization.c \
		setup/input_parsing.c \



################################################################################

# Object files
OBJS       = $(addprefix $(BUILD_DIR)/, $(SRC:$(SRC_DIR)/%.c=%.o))
MAIN_OBJ   = $(addprefix $(BUILD_DIR)/, $(MAIN:%.c=%.o))

################################################################################

all: $(NAME)

$(NAME): SHELL :=/bin/bash

$(NAME): $(OBJS) $(MAIN_OBJ)
	$(MAKE) -C ./libft
	$(MAKE) -C ./libft/ft_printf
	$(CC) $(CFLAGS) $^ $(INCLUDE_FLAGS) $(LIBFT) $(PRINTF) -o $(NAME)
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"

$(MAIN_OBJ) $(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

################################################################################

clean:
	@$(RM) $(OBJS) $(MAIN_OBJ)
	$(MAKE) -C ./libft clean
	$(MAKE) -C ./libft/ft_printf clean

debug:
	$(MAKE) DEBUG=1
.PHONY: debug

rebug: fclean debug
.PHONY: rebug

fsan:
	$(MAKE) DEBUG=1 FSAN=1
.PHONY: debug

resan: fclean fsan
.PHONY: resan

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
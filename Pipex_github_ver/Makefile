## PROGRAM ##

NAME = pipex

## COMPILER ##

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

MAKE = make

## PATHS ##

SRCS_PATH = srcs
INCS_PATH = includes

## LIBS/PROGRAMS/EXTERN FUNCTIONS##

LFT_NAME = libft.a
LFT_DIR = libft
LFT = $(addprefix $(LFT_DIR)/, $(LFT_NAME))

LIB = -L libft -l ft

## INCLUDES ## 

INCLUDES = -I ./$(LFT_DIR)/$(INCS_PATH)

## SOURCES ##

SRCS_FILES = 	pipex.c \
				free.c \
				pipex_utils.c \
				childs.c \

OBJS = $(SRCS:%.c=%.o)

SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

## CLEAN ##

RM = rm -rf

## RULES ##

.PHONY: all clean fclean re

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

## ALL
all: $(NAME)

## NAME
$(NAME): $(OBJS)
	@$(MAKE) -C $(LFT_DIR)/
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB) $(OBJS) -o $(NAME)

## CLEAN	
clean:
	@$(MAKE) clean -C $(LFT_DIR) 
	$(RM) $(OBJS)
	@echo "object fies deleted!"

## FCLEAN
fclean: clean
	$(MAKE) fclean -C $(LFT_DIR) 
	$(RM) $(NAME)
	@echo "all files deleted!"
	
## RE
re: fclean all
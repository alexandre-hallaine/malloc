ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# Target file names
NAME		:= libft_malloc_$(HOSTTYPE).so
LINK		:= libft_malloc.so

# Directories
INC_DIR	:= include
SRC_DIR	:= src
OBJ_DIR	:= obj

# Source and object files
SRCS	:= $(shell find $(SRC_DIR) -name '*.c')
OBJS	:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Compiler and linker options
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -I$(INC_DIR) -fPIC
LDFLAGS	:= -shared

# Phony targets
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

# Link object files into the shared library and create a symbolic link
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	@ln -sf $(NAME) $(LINK)

# Clean compiled files
clean:
	@rm -rf $(OBJ_DIR)

# Remove all compiled files and the library
fclean: clean
	@rm -f $(NAME)

# Clean and rebuild
re: clean all

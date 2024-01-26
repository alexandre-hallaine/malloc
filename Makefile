# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror

# Target file names
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
NAME := libft_malloc_$(HOSTTYPE).so
LINK := libft_malloc.so

# Directories
SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include
LIBFT_DIR := libft

# Source and object files
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Compiler and linker options
CFLAGS += -I$(INCLUDE_DIR) -I$(LIBFT_DIR)
LDFLAGS := -L$(LIBFT_DIR) -lft

# Phony targets
.PHONY: all lib clean fclean re

# Default target
all: $(NAME)

# Build the library
lib:
	@$(MAKE) -C $(LIBFT_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

# Link object files into the shared library and create a symbolic link
$(NAME): $(OBJS) lib
	$(CC) $(OBJS) $(LDFLAGS) -o $@ -shared
	@ln -sf $(NAME) $(LINK)

# Clean compiled files
clean:
	@rm -rf $(OBJ_DIR)

# Remove all compiled files and the library
fclean: clean
	@rm -f $(NAME)

# Clean and rebuild
re: clean all

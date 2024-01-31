# Target file names
NAME		:= test

# Directories
INC_DIR	:= ../include
SRC_DIR	:= src
OBJ_DIR	:= obj

# Source and object files
SRCS	:= $(shell find $(SRC_DIR) -name '*.c')
OBJS	:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Compiler and linker options
CC		:= gcc
CFLAGS	:= -Wall -Wextra -I$(INC_DIR)
LDFLAGS	:= -L.. -lft_malloc

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

# Clean compiled files
clean:
	@rm -rf $(OBJ_DIR)

# Remove all compiled files and the library
fclean: clean
	@rm -f $(NAME)

# Clean and rebuild
re: clean all

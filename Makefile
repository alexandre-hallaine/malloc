HOSTTYPE	:= $(shell uname -m)_$(shell uname -s)
NAME		:= libft_malloc_$(HOSTTYPE).so
LINK		:= libft_malloc.so

HEADERS	:= -I ./include -I ./libft
LIBS	:= -L ./libft -lft
CFLAGS	:= -Wall -Wextra -Wunreachable-code
# CFLAGS	+= -Werror

SRCS	:= $(shell find src -type f -name "*.c")
OBJS	:= $(SRCS:src/%.c=obj/%.o)

all: $(NAME)

lib:
	make -C libft

obj/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiled: $(notdir $<)"

$(NAME): $(OBJS) lib
	$(CC) $(OBJS) $(LIBS) -o $(NAME) -shared && echo "Linked: $(NAME)"
	ln -sf $(NAME) $(LINK) && echo "Linked: $(LINK)"

clean:
	rm -rf $(OBJS) && echo "Removed: $(OBJS)"

fclean: clean
	rm -rf $(NAME) && echo "Removed: $(NAME)"

re: clean all

.PHONY: all, lib, clean, fclean, re
.SILENT:
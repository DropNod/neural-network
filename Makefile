NAME = neural-network

CC = cc

CFLAGS = -o2
IFLAGS = -Iinclude
LFLAGS = -Llib -lm -lcjson

FILES =	main neuron layer network dataset utils

SRCS = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJS = $(addprefix obj/, $(addsuffix .o, $(FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LFLAGS)
	@echo "✔ Executable created."

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo Compiling $<...
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean :
	@rm -rf obj/

fclean : clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
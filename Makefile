NAME = neural-network

CC = cc

CFLAGS = -o2 -g
IFLAGS = -Iinclude
LFLAGS = -Llib -lm -lcjson -lSDL2 -lSDL2_gfx

FILES =	main neuron layer network train dataset utils visualizer coordinate

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
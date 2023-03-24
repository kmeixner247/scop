NAME = scop

SRCS = parse.cpp parsetest.cpp Shader.cpp GLFW.cpp

LIBS = libglfw3.a

CC = c++

CFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1# -g -fsanitize=address

all: $(NAME)

$(NAME): $(SRCS)
		$(CC) -o $(NAME) $(SRCS) $(LIBS) $(CFLAGS) 

clean:
	@$(RM) $(NAME)

fclean: clean
	@$(RM) -rf $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re
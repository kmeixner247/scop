NAME = scop

SRCS = src/parse.cpp src/main.cpp src/objects/Shader.cpp src/objects/GLFW.cpp

LIBS = libglfw3.a

CC = c++

CFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1 -g -fsanitize=address

all: $(NAME)

$(NAME): $(SRCS)
		$(CC) -o $(NAME) $(SRCS) $(LIBS) $(CFLAGS)

clean:
	@$(RM) $(NAME)

fclean: clean
	@$(RM) -rf $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re
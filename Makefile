NAME = scop

SRCS = parse.cpp parsetest.cpp Shader.cpp

LIBS = libglfw3.a

CC = c++

CFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1

all: $(NAME)

$(NAME): $(SRCS)
		$(CC) $(SRCS) $(LIBS) $(CFLAGS) -o $(NAME)

clean:
	@$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
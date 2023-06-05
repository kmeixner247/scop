NAME = scop

SRCS =	src/main.cpp \
		src/objects/Shader.cpp \
		src/objects/GLFW.cpp \
		src/objects/Scene.cpp \
		src/objects/Material.cpp \
		src/utils.cpp src/objects/VertexArray.cpp \
		src/objects/WavefrontLoader.cpp \
		src/objects/VertexBuffer.cpp \
		src/objects/Camera.cpp \
		src/objects/LightSource.cpp \
		src/objects/WavefrontObject.cpp \
		src/parseBmp.cpp

LIBS = libglfw3.a

CC = c++

CFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -D GL_SILENCE_DEPRECATION=1 -Wno-c++11-extensions -g -fsanitize=address #-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCS)
		$(CC) -o $(NAME) $(SRCS) $(LIBS) $(CFLAGS)

test: $(TSRCS)
		$(CC) -o $(NAME)test $(TSRCS) $(LIBS) $(CFLAGS)

clean:
	@$(RM) $(NAME)

fclean: clean
	@$(RM) -rf $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re
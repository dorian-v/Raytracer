##
## Makefile for raytracer1 in /home/voravo_d/rendu/raytracer1
## 
## Made by dorian voravong
## Login   <voravo_d@epitech.net>
## 
## Started on  Sat Jul 16 17:43:30 2016 dorian voravong
## Last update Sun Oct 23 15:08:22 2016 dorian voravong
##

CC	= gcc

RM	= rm -f

NAME	= raytracer

SRCS	= src/main.c\
	  src/perlin.c\
	  src/my_putstr_err.c\
	  src/my_get_nbr.c\
	  src/normal.c\
	  src/translation.c\
	  src/camera.c\
	  src/free.c\
	  src/load.c\
	  src/shapes.c\
	  src/exotic_shapes.c\
	  src/light.c\
	  src/color.c\
	  src/intersection.c\
	  src/solution.c\
	  src/rotation.c\
	  src/draw.c\
	  src/aliasing/anti_alias.c\
	  src/aliasing/init_alias.c\
	  src/aliasing/multi_sample.c\
	  src/aliasing/usual_alias.c\
	  src/tcore/tekpixel.c\
	  src/bmp_load.c\
	  src/textures.c\
	  src/menu.c\

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -I./include/ -W -Wall -Wextra -Werror

LIB	= -I/home/${USER}/.froot/include\
	  -L/home/${USER}/.froot/lib -llapin -lsfml-audio -lsfml-graphics\
	  -lsfml-window -lsfml-system -lstdc++ -ldl -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIB) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

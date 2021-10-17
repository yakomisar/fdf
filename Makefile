TARGET		= fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FLAGS_MAC = -framework OpenGL -framework AppKit
RM = rm -f

SRC_S = fdf.c \
		includes/gnl.c \
		includes/read.c \
		includes/dda.c \
		includes/iso.c

MLX		=	minilibx_macos/libmlx.a

OBJ_S = $(SRC_S:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

all:	$(TARGET)

$(TARGET): $(OBJ_S)
	$(CC) $(CFLAGS) $(MLX) $(FLAGS_MAC) $^ -o $@

clean:
	$(RM) $(OBJ_S)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
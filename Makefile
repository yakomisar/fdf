TARGET		= fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror
FLAGS_MAC = -lmlx -framework OpenGL -framework AppKit
RM = rm -f

SRC_S = fdf.c \
		get_next_line.c \
		read.c \
		dda.c

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
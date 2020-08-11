NAME = fractol

SRCNAME =	fractal_m.c \
			init.c \
			fractal_julia.c \
			fractal_celtic.c \
			fractal_burningship.c \
			keys.c \
			mouse.c \
			errors.c \
			main.c

SRC = $(addprefix src/, $(SRCNAME))
OBJ = $(SRC:.c=.o)
FLAGS = -l mlx -framework OpenGL -framework AppKit
HDIR = includes
LFT = libft/libft.a

.SILENT:

all : $(NAME)

$(NAME): $(OBJ)
	make -C libft
	gcc -g $(OBJ) $(LFT) $(FLAGS) -o $(NAME)
	@echo "(*) fractol"

%.o: %.c
	gcc -o $@ -c $< -I $(HDIR)
	@echo "(+) $@"

clean:
	rm -f $(OBJ)
	make clean -C libft
	@echo "(-) *.o"

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	@echo "(-) libft"
	@echo "(-) fractol"

re: fclean all
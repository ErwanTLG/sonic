make :
	gcc -Wall -Wextra -o sonic board.h main.c
make_segfault :
	gcc -Wall -Wextra -fsanitize=address -o sonic board.h main.c
run :
	./sonic

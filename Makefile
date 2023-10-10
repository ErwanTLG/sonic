make :
	gcc -Wall -Wextra -o sonic board.h board.c main.c
make_segfault :
	gcc -Wall -Wextra -fsanitize=address -o sonic board.h board.c main.c
run :
	./sonic

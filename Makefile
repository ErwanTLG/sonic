make :
	gcc -Wall -Wextra -o sonic main.c
make_segfault :
	gcc -Wall -Wextra -fsanitize=address -o sonic main.c
run :
	./sonic

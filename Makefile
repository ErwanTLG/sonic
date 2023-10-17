make :
	gcc -Wall -Wextra -o sonic board.h board.c player.c player.h rule.c rule.h gamemaster.c gamemaster.h main.c
make_segfault :
	gcc -Wall -Wextra -fsanitize=address -o sonic board.h board.c player.c player.h rule.c rule.h gamemaster.c gamemaster.h main.c
run :
	./sonic

main: main.c ./immigrant_factory/immigrant_factory.c ./immigrant/immigrant.c ./judge/judge.c ./utils/utils.c
	gcc -pthread -std=gnu99 -Wall -Wextra -Werror -pedantic -o proj2  main.c ./immigrant_factory/immigrant_factory.c ./immigrant/immigrant.c ./judge/judge.c ./utils/utils.c 
clean:
	rm -f proj2.out proj2

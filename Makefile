default: main.c
	gcc -std=gnu99 -o proj2 -pthread main.c ./immigrant_factory/immigrant_factory.c ./immigrant/immigrant.c ./judge/judge.c ./utils/utils.c 

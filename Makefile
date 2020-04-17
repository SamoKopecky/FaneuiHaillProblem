default: main.c
	gcc -std=gnu99 -o proj2 -pthread main.c immigrant_factory.c immigrant.c -pthread judge.c

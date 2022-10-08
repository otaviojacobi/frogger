.PHONY: .all

all:
	gcc main.c utils.c frog.c car.c game.c -o frogger -lncurses -Wall -Werror -std=gnu99 -lm

old:
	g++ main2.c -o frogger2 -fpermissive -w
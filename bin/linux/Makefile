build:
	gcc ../../src/Main.c ../../src/Array.c ../../src/Server.c ../../src/Client.c -Wall -Wextra -Wfatal-errors -Wshadow -ggdb3 -o Program -std=c99 -lSDL2 -lSDL2_net -lSDL2_ttf -lSDL2_mixer -lSDL2_image -llua53 -lm
debug:
	gdb ./Program

run:
	./Program

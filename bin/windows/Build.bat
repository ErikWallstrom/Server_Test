@echo off
g++ ../../src/Main.cpp ../../src/Server.cpp -Wall -Wextra -Wfatal-errors -ggdb3 -o Program -std=c++11 -lSDL2 -lSDL2_net -lSDL2_ttf -lSDL2_mixer -lSDL2_image -llua53
echo(
pause

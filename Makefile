all:
	g++ main.cpp model/*.cpp view/*.cpp controller/*.cpp -lncurses -o hello

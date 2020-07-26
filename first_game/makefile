game:
	g++ main.cpp -o play game_functions.cpp MainCharacter.cpp -g -ggdb3 -I include -L lib -l SDL2-2.0.0 -l SDL2_image -std=c++17
valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes \
	--num-callers=20 --track-fds=yes --log-file="valgrind_output.txt" -s ./play
debug:
	lldb play
run:
	./play

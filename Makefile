cardgame: function.o main.o
	gcc -o cardgame -O2 -Werror -Wall -Wextra -Wpedantic -std=c11 function.o main.o

*.o: *.c
	gcc -O2 -Werror -Wall -Wextra -Wpedantic -std=c11 -c *.c
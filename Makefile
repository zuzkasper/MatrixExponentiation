all : exponentiation.c
	gcc -Wall -Werror -fsanitize=address -o exponentiation exponentiation.c
clean :
	rm -rf exponentiation

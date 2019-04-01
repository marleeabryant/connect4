connectFour : piece.c column.c board.c player.c connectFour.c
	gcc -g -std=c11 piece.c column.c board.c player.c connectFour.c -lncurses -o connectFour

test : ./connectFour
	./connectFour

clean :
	rm -rf *.out *.dSYM *.o connectFour

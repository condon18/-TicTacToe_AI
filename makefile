#define the compiler-executable path
COMPILE = gcc $(COMPILE_SWITCHES)
COMPILE_SWITCHES = -g
OFILES = tictactoe.o ttthelper.o gametree.o

game: $(OFILES)
	$(COMPILE) -o game $(OFILES)

tictactoe.o: tictactoe.c gametree.h
	$(COMPILE) -c tictactoe.c

ttthelper.o: ttthelper.c gametree.h
	$(COMPILE) -c ttthelper.c

gametree.o: gametree.c gametree.h
	$(COMPILE) -c gametree.c

# this defines the command for cleaning up
# all generated files
clean:
	/bin/rm -f *.o game

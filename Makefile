SRC=main.c
BIN=main
FNC=fonct

$(BIN): $(FNC).o $(SRC)
	gcc -Wall -g -std=c99 $(SRC) `sdl-config --cflags --libs` -lSDL_ttf $(FNC).o -o $(BIN)
$(FNC).o: $(FNC).c $(FNC).h $(SRC)
	gcc -Wall -Wextra -pedantic -g -std=c99 -c `sdl-config --cflags --libs` -lSDL_ttf -O3 $(FNC).c
clean:
	rm -f $(BIN)


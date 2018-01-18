CC=g++
NAME = scrabbleCheater
CFLAGS = -std=c++11
SRC = scrabbleCheat.cpp

all: $(NAME)

$(NAME) : $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)
clean:
	rm -f $(NAME)

distclean: clean

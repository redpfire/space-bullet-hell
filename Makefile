#LDFLAGS=-lncurses -lmpg123 -lao -lpthread

LDFLAGS=-lncurses

all:
	g++ $(LDFLAGS) -I. *.cpp -o sbh

debug:
	g++ $(LDFLAGS) -I. *.cpp -o sbh -g


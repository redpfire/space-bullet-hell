LDFLAGS=-lncurses -lmpg123 -lao -lpthread

all:
	g++ $(LDFLAGS) -I. *.cpp -o sbh

debug:
	g++ $(LDFLAGS) -I. *.cpp -o sbh -g


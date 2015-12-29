CPPFLAGS=-O2
all: index search
search: search.o common.o
	g++ ${CPPFLAGS} common.o search.o -o search
search.o: search.cpp
	g++ -c ${CPPFLAGS} search.cpp -o search.o
index: index.o sa.o common.o
	g++ ${CPPFLAGS} common.o index.o sa.o -o index
index.o: index.cpp
	g++ -c ${CPPFLAGS} index.cpp -o index.o
sa.o: sa.cpp
	g++ -c ${CPPFLAGS} sa.cpp -o sa.o
common.o: common.cpp
	g++ -c ${CPPFLAGS} common.cpp -o common.o
clean:
	rm -f *.o search index

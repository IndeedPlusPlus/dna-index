CPPFLAGS=-O2
search: search.o
	g++ ${CPPFLAGS} search.o -o search
search.o: search.cpp
	g++ -c ${CPPFLAGS} search.cpp -o search.o
index: index.o sa.o
	g++ ${CPPFLAGS} index.o sa.o -o index
index.o: index.cpp
	g++ -c ${CPPFLAGS} index.cpp -o index.o
sa.o: sa.cpp
	g++ -c ${CPPFLAGS} sa.cpp -o sa.o

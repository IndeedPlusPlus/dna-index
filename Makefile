CPPFLAGS=-O2
index: index.o sa.o
	g++ ${CPPFLAGS} index.o sa.o -o index
index.o: index.cpp
	g++ -c ${CPPFLAGS} index.cpp -o index.o
sa.o: sa.cpp
	g++ -c ${CPPFLAGS} sa.cpp -o sa.o

output: main.o sdisk.o filesys.o block.o shell.o table.o
	g++ main.o sdisk.o filesys.o block.o shell.o table.o -o output

main.o: main.cpp
	g++ -c main.cpp

sdisk.o: sdisk.cpp sdisk.h
	g++ -c sdisk.cpp

filesys.o: filesys.cpp filesys.h
	g++ -c filesys.cpp

block.o: block.cpp block.h
	g++ -c block.cpp

shell.o: shell.cpp shell.h
	g++ -c shell.cpp

table.o: table.cpp table.h
	g++ -c table.cpp

clean:
	rm *.o output

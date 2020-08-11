CFLAGS = -Wall -Wfatal-errors -Wno-unused-result -Wno-unknown-pragmas -Wno-pragma-once-outside-header
COMMON = $(CFLAGS) `pkg-config --cflags --libs libmariadb`

ejemplomain: ejemplo_testing.o database_handler.o user.o
	g++ -o ejemplomain ejemplo_testing.o database_handler.o user.o $(COMMON)

ejemplo_testing.o: ejemplo_testing.cpp
	g++ -c ejemplo_testing.cpp $(COMMON)

database_handler.o: database_handler.cpp database_handler.h user.o
	g++ -c database_handler.cpp database_handler.h $(COMMON)

user.o: user.cpp user.h
	g++ -c user.cpp user.h

clean: 
	rm *.o *.gch
CC = g++
LIBS = -L"C:/Program Files (x86)/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib" -static-libgcc "cppunitlite/CppUnitLite.a" 
OBJS = shape.o 
all:mainTest.exe 

clean:
	rm -rf *.o *.exe

mainTest.exe: mainTest.o $(OBJS)
	$(CC) -o mainTest.exe mainTest.o $(OBJS) $(LIBS)

shape.o: shape.cpp shape.h
	$(CC) -c shape.cpp -o shape.o

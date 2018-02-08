EXE := ConnectFour
CC := g++
COFLAGS := -O3 -c -g -std=c++14
CCFLAGS := -static-libgcc -static-libstdc++
USER_OBJS := src\board.o src\main.o src\negamax.o src\player.o src\state.o src\token.o
LIBS := -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2


all: bin\$(EXE)


bin\$(EXE): $(USER_OBJS)
	@echo 'Building target: $@'
	g++ -L bin\ $(CCFLAGS) -o bin\$(EXE) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'


src\board.o: src\board.cpp src\board.hpp
	g++ -I include\ $(COFLAGS) -o src\board.o src\board.cpp
	

src\main.o: src\main.cpp
	g++ -I include\ $(COFLAGS) -o src\main.o src\main.cpp
	
	
src\negamax.o: src\negamax.cpp src\negamax.hpp
	g++ -I include\ $(COFLAGS) -o src\negamax.o src\negamax.cpp
	
	
src\player.o: src\player.cpp src\player.hpp
	g++ -I include\ $(COFLAGS) -o src\player.o src\player.cpp
	
	
src\state.o: src\state.cpp src\state.hpp
	g++ -I include\ $(COFLAGS) -o src\state.o src\state.cpp
	
	
src\token.o: src\token.cpp src\token.hpp
	g++ -I include\ $(COFLAGS) -o src\token.o src\token.cpp
	
	
clean:
ifeq ($(OS), Windows_NT)
		del bin\$(EXE) $(USER_OBJS)
endif
ifeq ($(OS), Linux)
		rm -f bin\$(EXE) $(USER_OBJS)
endif
		
	
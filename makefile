EXE := ConnectFour
CXX := g++
CXXOFLAGS := -O3 -c -g -std=c++14
CXXFLAGS := -static-libgcc -static-libstdc++
USER_OBJS := src\board.o src\main.o src\menu.o src\negamax.o src\player.o src\resourcemanager.o src\state.o src\token.o src\useroptions.o
USER_OBJS_TEST := tests\tests.o src\board.o src\negamax.o src\player.o src\resourcemanager.o src\state.o src\token.o 
LIBS := -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2 -lthor -lsfgui
LIBS_TEST := -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2 -lthor -l$(BOOST_DLL)
BOOST_PATH :=
BOOST_DLL := libboost_unit_test_framework-mgw72-mt-x64-1_66



all: bin\$(EXE)


bin\$(EXE): $(USER_OBJS)
	@echo 'Building target: $@'
	$(CXX) -L bin\ $(CXXFLAGS) -o bin\$(EXE) $(USER_OBJS) $(LIBS)
	@echo ' Finished building target: $@'
	

tests: $(USER_OBJS_TEST)
	@echo 'Building target: $@'
	$(CXX) -L bin\ $(CXXFLAGS) -o bin\AllTests $(USER_OBJS_TEST) $(LIBS_TEST)


src\board.o: src\board.cpp src\board.hpp
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\board.o src\board.cpp
	

src\main.o: src\main.cpp
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\main.o src\main.cpp
	
	
src\menu.o: src\resourcemanager.o src\menu.cpp
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\menu.o src\menu.cpp
	
	
src\negamax.o: src\negamax.cpp src\negamax.hpp
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\negamax.o src\negamax.cpp
	
	
src\player.o: src\player.cpp src\player.hpp
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\player.o src\player.cpp
	
	
src\resourcemanager.o: src\resourcemanager.cpp
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\resourcemanager.o src\resourcemanager.cpp
	
	
src\state.o: src\state.cpp src\state.hpp 
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\state.o src\state.cpp
	
	
src\token.o: src\token.cpp src\token.hpp
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\token.o src\token.cpp
	
	
src\useroptions.o: src\useroptions.cpp src\useroptions.hpp
	$(CXX) -I src\ -I external\include $(CXXOFLAGS) -o src\useroptions.o src\useroptions.cpp
	

tests\tests.o: 
	$(CXX) -I. -I external\include -I $(BOOST_PATH) $(CXXOFLAGS) -o tests\tests.o tests\tests.cpp
	

	
	
clean:
ifeq ($(OS), Windows_NT)
	del "bin\$(EXE).exe" "bin\AllTests.exe" $(USER_OBJS) $(USER_OBJS_TEST)
	@echo 'Finished target: $@'
endif
ifeq ($(OS), Linux)
		rm -f bin\$(EXE) $(USER_OBJS) $(USER_OBJS_TEST)
		@echo 'Finished target: $@'
endif

		
	
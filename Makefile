COMPILER=c++
C_FLAGS=-Wall -Wextra -pedantic
L_FLAGS=-lIrrlicht

all: main.o general.o world.o frontend.o engine.o
	$(COMPILER) $(C_FLAGS) general.o world.o frontend.o engine.o main.o -o game $(L_FLAGS)

main.o: main.cpp
	$(COMPILER) $(C_FLAGS) main.cpp -c

general.o: general.cpp general.hpp
	$(COMPILER) $(C_FLAGS) general.cpp -c

world.o: world.cpp world.hpp
	$(COMPILER) $(C_FLAGS) world.cpp -c

frontend.o: frontend.cpp frontend.hpp
	$(COMPILER) $(C_FLAGS) frontend.cpp -c

engine.o: engine.cpp
	$(COMPILER) $(C_FLAGS) engine.cpp -c


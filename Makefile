COMPILER=c++
C_FLAGS=-std=c++11 -Wall -Wextra -pedantic
L_FLAGS=-lIrrlicht -lm

all: main.o general.o world.o frontend.o engine.o ai.o
	$(COMPILER) $(C_FLAGS) general.o world.o frontend.o engine.o main.o ai.o -o game $(L_FLAGS)

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

ai.o: ai.cpp
	$(COMPILER) $(C_FLAGS) ai.cpp -c


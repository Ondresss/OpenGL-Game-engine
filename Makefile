LIBS=-lglfw -lGL -lGLEW -lSOIL
FLAGS=-Wall -pedantic 
TARGET=main
SRCS=$(wildcard ./includes/cppfiles/*.cpp)
OBJS=$(SRCS:.cpp=.o)
.PHONY=clean
./includes/cppfiles/%.o: ./includes/cppfiles/%.cpp
	g++ $(FLAGS) -c -o $@ $<
%.o: %.cpp
	g++ $(FLAGS) -c -o $@ $^

clean: 
	rm -rf *.o ./includes/cppfiles/*.o
$(TARGET): $(OBJS)
	g++ -o $@ $^ $(LIBS) 



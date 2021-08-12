CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

LIBS = -L$(LIB)

LIB = ./boost/lib/
INCLUDE = ./boost/include/

SRC = $(shell find . -name "*.cpp")
OBJ = $(SRC:.cc=.o)
EXEC = Calculator

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS) $(LIBS) -I$(INCLUDE)

clean:
	rm -rf $(OBJ) $(EXEC)
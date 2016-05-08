
CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -Werror
BIN=n-queens

CWD=$(shell pwd)
SRCDIR=$(CWD)/src
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^ -I$(SRCDIR)

%.o: %.c
	$(CXX) $@ -c $< -I$(SRCDIR)

clean:
	-rm -f $(OBJ)
	-rm $(BIN)

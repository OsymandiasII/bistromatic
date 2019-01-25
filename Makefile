CXX=g++
CXXFLAGS= -std=c++17 -pedantic -Wall -Wextra -Werror -g

VPATH= src/
SRC_FIND= *c

OUT = binary

all: ${CXX} ${CXXFLAGS} ${SRC_FIND} -o ${OUT}

#.PHONY: test

#binary: ${CXX} ${CXXFLAGS} ${SRC_FIND} -o ${OUT}

#test:


#clean:
#	$(RM) 
#	$(RM) $(OBJ_FIND)

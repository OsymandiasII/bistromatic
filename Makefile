CXX=g++
CXXFLAGS= -std=c++17 -pedantic -Wall -Wextra -Werror -g -Isrc -fmax-errors=5

SRC= libbistro-example.cc #src/*.cc

FLEX= flex
FLXFLAGS= -f
FLXOUT= src/scan-bistro.cc
FLXIN= src/scan-bistro.ll

BISON= bison
BSNBIN= src/parse-bistro.yy
BSNOUT= src/parse-bistro.cc
BSNDEFINE= --defines=src/parse-bistro.hh

BSNGEN= location.hh parse-bistro.cc position.hh stack.hh src/location.hh src/position.hh src/stack.hh

TFOLD= -Isrc/

TESTSRC= tests/tests.cc
TLIB= -lcriterion
CXXFLAGSTST = --std=c++17
TSRC= -Itests/
TOUT= unit_test
TVFLAG= --verbose -j1 --full-stats

OUT= binary

all: flex
all: bison
all:
	${CXX} ${CXXFLAGS} ${SRC} -o ${OUT}

flex: 
	${FLEX} ${FLXFLAGS} -o ${FLXOUT} ${FLXIN}

bison: 
	${BISON} ${BSNBIN} -o ${BSNOUT} ${BSNDEFINE}

.PHONY: test


test:
	${CXX} ${CCXXFLAGSTST} ${TLIB} ${TSRC} ${TESTSRC} ${TFOLD} -o ${TOUT}

clean:
	$(RM) ${OUT} ${TOUT}
	$(RM) $(BSNGEN)

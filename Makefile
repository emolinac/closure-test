BIN := ./bin
INC := ./include
SRC := ./src

CXX    := g++ -std=c++11
CFLAGS := -Wall -g

ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTINCDIR  := $(shell root-config --incdir)
ROOTLIBS    := $(shell root-config --libs) -lEG

all: ${BIN}/acceptance ${BIN}/create-ntuples ${BIN}/integrate-phi-q2nuzhpt2

${BIN}/acceptance: ${SRC}/acceptance.cpp
	${CXX} ${ROOTCFLAGS} ${SRC}/acceptance.cpp -I${INC} ${ROOTLIBS} -o ${BIN}/acceptance

${BIN}/create-ntuples: ${SRC}/create-ntuples.cpp
	${CXX} ${ROOTCFLAGS} ${SRC}/create-ntuples.cpp -I${INC} ${ROOTLIBS} -o ${BIN}/create-ntuples

${BIN}/integrate-phi-q2nuzhpt2: ${SRC}/integrate-phi-q2nuzhpt2.cpp
	${CXX} ${ROOTCFLAGS} ${SRC}/integrate-phi-q2nuzhpt2.cpp -I${INC} ${ROOTLIBS} -o ${BIN}/integrate-phi-q2nuzhpt2

clean:
	rm ${BIN}/*

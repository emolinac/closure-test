BIN := ./bin
INC := ./include
SRC := ./src

CXX    := g++ -std=c++11
CFLAGS := -Wall -g

ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTINCDIR  := $(shell root-config --incdir)
ROOTLIBS    := $(shell root-config --libs) -lEG

all: ${BIN}/acceptance ${BIN}/create-ntuples ${BIN}/obtain-weights ${BIN}/apply-weights-5dim

${BIN}/acceptance: ${SRC}/acceptance.cpp
	${CXX} ${ROOTCFLAGS} ${SRC}/acceptance.cpp -I${INC} ${ROOTLIBS} -o ${BIN}/acceptance

${BIN}/create-ntuples: ${SRC}/create-ntuples.cpp
	${CXX} ${ROOTCFLAGS} ${SRC}/create-ntuples.cpp -I${INC} ${ROOTLIBS} -o ${BIN}/create-ntuples

${BIN}/obtain-weights: ${SRC}/obtain-weights.cpp
	${CXX} ${ROOTCFLAGS} ${SRC}/obtain-weights.cpp -I${INC} ${ROOTLIBS} -o ${BIN}/obtain-weights

${BIN}/apply-weights-5dim: ${SRC}/apply-weights-5dim.cpp
	${CXX} ${ROOTCFLAGS} ${SRC}/apply-weights-5dim.cpp -I${INC} ${ROOTLIBS} -o ${BIN}/apply-weights-5dim

clean:
	rm ${BIN}/*

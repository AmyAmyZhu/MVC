CXX=g++
CXXFLAGS=-Wall -MMD
OBJECTS=main.o cell.o controller.o game.o textdisplay.o view.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=flood

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}



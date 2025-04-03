CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror=vla -MMD #-fsanitize=address
LDLIBS = -lncurses
EXEC = cc3k

MAINSRC = $(wildcard *.cc)
MAINOBJ = $(MAINSRC:.cc=.o)
PLAYERSRC = $(wildcard Player/*.cc)
PLAYEROBJ = $(PLAYERSRC:.cc=.o)
ENEMYSRC = $(wildcard Enemy/*.cc)
ENEMYOBJ = $(ENEMYSRC:.cc=.o)
ITEMSRC = $(wildcard Item/*.cc)
ITEMOBJ = $(ITEMSRC:.cc=.o)
OBJECTS = ${PLAYEROBJ} ${ENEMYOBJ} ${ITEMOBJ} ${MAINOBJ}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDLIBS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

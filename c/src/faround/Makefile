

CC=gcc
LIBS= -lmenu -lncurses

SRC_DIR=.
EXE_DIR= ../../bin

EXES = \
	${EXE_DIR}/menu




${EXE_DIR}/%: %.o
	${CC} -o $@ $< ${LIBS}

%.o: ${SRC_DIR}/%.c
	${CC} -o $@ -c $<

all:    ${EXES}


clean:
	@rm -f ${EXES}

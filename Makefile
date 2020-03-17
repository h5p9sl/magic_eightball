# Compiler and linker
CC=gcc
LD=gcc

CFLAGS=--debug
LFLAGS=

SRC=$(wildcard *.c)
OBJ=${SRC:.c=.o}

OUT=a.out

all: options build

options:
	@echo CC	= ${CC}
	@echo LD	= ${LD}
	@echo CFLAGS	= ${CFLAGS}
	@echo LFLAGS	= ${LFLAGS}
	@echo SRC	= ${SRC}
	@echo OBJ	= ${OBJ}

.c.o:
	@echo ${CC} -c $<
	@${CC} -c $< ${CFLAGS} -o $@

build: ${OBJ}
	@echo ${LD} *.o
	@${LD} ${OBJ} ${LFLAGS} -o ${OUT}

clean:
	rm *.o -f
	#rm ${OUT}

CC = gcc
NAME = socket

MAJOR = 0.0.1
MINOR = -rc1

LIBS = 
INCS = -I src/headers/

TARGETS = src/core/*.c

.PHONY: socket
all: socket

socket:
	${CC} ${TARGETS} ${LIBS} ${INCS} -o ${NAME}
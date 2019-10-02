CC = gcc
NAME = socket

BUILDDIR = ./build
SRCDIR   = ./src

SRCS := ${shell find ${SRCDIR} -name *.c}
OBJS := ${SRCS:%=${BUILDDIR}/%.o}
DEPS := ${OBJS:.o=.d}

INCLIBS  := -lm
INCDIRS  := ${shell find ${SRCDIR} -type d}
INCFLAGS := ${addprefix -I,${INCDIRS}}

CFLAGS  := ${INCFLAGS} ${INCLIBS}
LDFLAGS := ${INCLIBS}

${BUILDDIR}/${NAME}: ${OBJS}
	${CC} ${OBJS} -o $@ ${LDFLAGS}

${BUILDDIR}/%.c.o: %.c
	mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: clean

clean:
	${RM} -r ${BUILDDIR}

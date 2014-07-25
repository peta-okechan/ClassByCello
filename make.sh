#!/bin/bash

FILENAME=human

gcc -std=gnu99 ${FILENAME}.c -E | cat -s > ${FILENAME}_nm.c

gcc -std=gnu99 ${FILENAME}.c -lCello -o ${FILENAME}

./${FILENAME}

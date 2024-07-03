#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "utils.h"

int asprintf(char **restrict strp, char *restrict fmt, ...) {
    int size = 0;
    va_list arguments;

    /*Initialising va_list*/
    va_start(arguments, fmt);
    /*Counting the size of memory that needs to be allocated including \0*/
    size = vsnprintf(NULL, 0, fmt, arguments) + sizeof(char);
    *strp = (char *)realloc(*strp, size * sizeof(char));
    *strp = (char *)memset(*strp, '\0', size * sizeof(char));

    /*Resetting va_list*/
    va_start(arguments, fmt);
    vsprintf(*strp, fmt, arguments);

    return(size);
}

void address_check (void *address, char *context) {
    if (address == NULL) {
        fprintf(stderr, "Memory allocation failed at :%s\nQuitting...\n", context);
        exit(-1);
    }
}
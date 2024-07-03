#pragma once

/*Replica of GNU extension. See man asprintf.*/
int asprintf(char **restrict strp, char *restrict fmt, ...);

void address_check (void *address, char *context);
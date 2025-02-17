#ifndef IOHELPER_H
#define IOHELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// Type definitions
typedef char * string;

// Public function declaration
char *get_string(char *output, ...);
long get_long(char *output, ...);
double get_double(char *output, ...);
float get_float(char *output, ...);
char get_char(char *output, ...);
int get_int(char *output, ...);
void free_string(char *str);


#endif // IOHELPER_H
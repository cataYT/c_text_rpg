#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#include <string.h>
#include <stdio.h>
#include <stddef.h>

#ifndef _MSC_VER
// Provide fallback function declarations
int strcpy_s(char *dest, size_t destsz, const char *src);
int strcat_s(char *dest, size_t destsz, const char *src);
#endif

#endif // COMPATIBILITY_H
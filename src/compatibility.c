/*! Used for compatability between OS for the secure versions. */

#include "headers/compatibility.h"

#ifndef _MSC_VER

int strcpy_s(char *dest, size_t destsz, const char *src)
{
    if (!dest || !src || destsz == 0) return 1;
    strncpy(dest, src, destsz);
    dest[destsz - 1] = '\0';
    return 0;
}

int strcat_s(char *dest, size_t destsz, const char *src)
{
    if (!dest || !src || destsz == 0) return 1;

    size_t dest_len = strnlen(dest, destsz);
    size_t src_len = strnlen(src, destsz);

    if (dest_len + src_len + 1 > destsz) {
        return 1; // Not enough space
    }

    strncat(dest, src, destsz - dest_len - 1);
    return 0;
}

#endif
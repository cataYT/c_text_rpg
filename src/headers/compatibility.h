/*! Compatibility declaration file */

#ifndef COMPATIBILITY_H
#define COMPATIBILITY_H

#include <string.h>
#include <stdio.h>
#include <stddef.h>

#ifndef _MSC_VER

/**
 * @brief Copies the string safely by taking additional parameter of size.
 * 
 * @param[in,out] dest Caller allocated string to copy to.
 * @param[in] destsz Size of the destination string.
 * @param[in] src String to copy from.
 * @return 0 if success, 1 otherwise.
 */
int strcpy_s(char *dest, size_t destsz, const char *src);
/**
 * @brief Concatenates the string safely by taking additional parameter of size.
 * 
 * @param[in,out] dest Caller allocated string to concatenate to.
 * @param[in] destsz Size of the string to concatenate.
 * @param[in] src String to concatenate.
 * @return 0 if success, 1 otherwise.
 */
int strcat_s(char *dest, size_t destsz, const char *src);
#endif

#endif // COMPATIBILITY_H
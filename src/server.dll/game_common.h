#ifndef GAME_COMMON_H
#define GAME_COMMON_H

/* Force windows.h first to get canonical types */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdio.h>
#include <string.h>

/* Rebrew/Ghidra exported standard types */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

/* Common Ghidra-isms */
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned char  byte;
typedef unsigned short ush;
typedef unsigned long  uLong;

/*
 * Wrapper for auto-generated types.h to avoid conflicts with windows.h.
 * Since we can't edit types.h, we use preprocessor defines to skip its
 * redundant definitions of standard types.
 */
#define _CONTEXT _SKIP_CONTEXT
#define _iobuf _SKIP_IOBUF
#define _LIST_ENTRY _SKIP_LIST_ENTRY
#define _EXCEPTION_RECORD _SKIP_EXCEPTION_RECORD
#define _EXCEPTION_POINTERS _SKIP_EXCEPTION_POINTERS
#define _OSVERSIONINFOA _SKIP_OSVERSIONINFOA
#define _OVERLAPPED _SKIP_OVERLAPPED
#define _SECURITY_ATTRIBUTES _SKIP_SECURITY_ATTRIBUTES
#define _STARTUPINFOA _SKIP_STARTUPINFOA
#define _CPINFO _SKIP_CPINFO
#define _SYSTEMTIME _SKIP_SYSTEMTIME

/*
 * Note: types.h must be included relatively from the source file.
 * We don't include it here to avoid complex path issues in common header.
 */

#endif /* GAME_COMMON_H */

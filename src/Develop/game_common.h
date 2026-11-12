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
typedef unsigned int   uint32_t;

/* Common Ghidra-isms */
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned char  byte;
typedef unsigned long  uLong;

/*
 * Historical skip macros for generated-type conflicts with windows.h.
 * This header defines scalar aliases above; no project types.h remains.
 * Retain the macros pending a compiler-context review.
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
 * Project type headers are client_types.h and Develop/rebrew_types.h.
 * This header has no generated types.h include requirement.
 */

#endif /* GAME_COMMON_H */

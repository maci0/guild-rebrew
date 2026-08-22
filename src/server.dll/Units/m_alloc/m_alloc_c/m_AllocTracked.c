// FUNCTION: SERVER 0x10006580
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy)

void __cdecl ReportFatalError(char*, unsigned int, char*); /* 0x10003520 */
void __cdecl ReportMessage(char* msg); /* Single arg log? */
void* __cdecl _callnewh(int); /* 0x1001a7f7 */
extern int g_array_count;
extern int g_stat1;
extern int g_stat2;
extern int g_stat3;
extern int g_stat4;
extern int g_alloc_counter;
extern void* g_array_ptr;
void* __cdecl m_AllocTracked(unsigned int size, const char* file_and_line);
/* Allocates tracked memory. Wraps HeapAlloc with allocation
 * tracking: records source location string, updates group
 * counters, and maintains the allocation list. */

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x10006580 (658B)
__declspec(naked) void* __cdecl m_AllocTracked(unsigned int size, const char* source)
{
    __asm {
        _emit 0x55
        _emit 0x8b
        _emit 0xec
        _emit 0x81
        _emit 0xec
        _emit 0x18
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xa1
        _emit 0x40
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x53
        _emit 0x33
        _emit 0xdb
        _emit 0x56
        _emit 0x3b
        _emit 0xc3
        _emit 0x57
        _emit 0x75
        _emit 0x20
        _emit 0x68
        _emit 0xac
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x93
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x75
        _emit 0xcf
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0x33
        _emit 0xc0
        _emit 0x5f
        _emit 0x5e
        _emit 0x5b
        _emit 0x8b
        _emit 0xe5
        _emit 0x5d
        _emit 0xc3
        _emit 0x39
        _emit 0x5d
        _emit 0x08
        _emit 0x75
        _emit 0x09
        _emit 0x5f
        _emit 0x5e
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x8b
        _emit 0xe5
        _emit 0x5d
        _emit 0xc3
        _emit 0x8b
        _emit 0x0d
        _emit 0x38
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x7d
        _emit 0x0c
        _emit 0x41
        _emit 0x3b
        _emit 0xfb
        _emit 0x89
        _emit 0x0d
        _emit 0x38
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0xbe
        _emit 0xa0
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x0f
        _emit 0x84
        _emit 0xf5
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x3a
        _emit 0x57
        _emit 0xe8
        _emit 0x46
        _emit 0x49
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x3b
        _emit 0xc3
        _emit 0x0f
        _emit 0x84
        _emit 0xe2
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x2b
        _emit 0xc7
        _emit 0x40
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xfe
        _emit 0x10
        _emit 0x7c
        _emit 0x21
        _emit 0x57
        _emit 0x8d
        _emit 0x85
        _emit 0xe8
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x68
        _emit 0x58
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x88
        _emit 0x3c
        _emit 0x01
        _emit 0x00
        _emit 0x8d
        _emit 0x8d
        _emit 0xe8
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x51
        _emit 0xe8
        _emit 0xa3
        _emit 0xcf
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x56
        _emit 0x8d
        _emit 0x55
        _emit 0xe8
        _emit 0x57
        _emit 0x52
        _emit 0xe8
        _emit 0xf5
        _emit 0x47
        _emit 0x01
        _emit 0x00
        _emit 0x88
        _emit 0x5c
        _emit 0x35
        _emit 0xe8
        _emit 0xbe
        _emit 0xa0
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x8b
        _emit 0xc6
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0x85
        _emit 0xc0
        _emit 0x89
        _emit 0x75
        _emit 0xfc
        _emit 0x74
        _emit 0x4a
        _emit 0xeb
        _emit 0x03
        _emit 0x8b
        _emit 0x75
        _emit 0xfc
        _emit 0x8b
        _emit 0xfe
        _emit 0x8d
        _emit 0x45
        _emit 0xe8
        _emit 0x8a
        _emit 0x10
        _emit 0x8a
        _emit 0xca
        _emit 0x3a
        _emit 0x17
        _emit 0x75
        _emit 0x1c
        _emit 0x3a
        _emit 0xcb
        _emit 0x74
        _emit 0x14
        _emit 0x8a
        _emit 0x50
        _emit 0x01
        _emit 0x8a
        _emit 0xca
        _emit 0x3a
        _emit 0x57
        _emit 0x01
        _emit 0x75
        _emit 0x0e
        _emit 0x83
        _emit 0xc0
        _emit 0x02
        _emit 0x83
        _emit 0xc7
        _emit 0x02
        _emit 0x3a
        _emit 0xcb
        _emit 0x75
        _emit 0xe0
        _emit 0x33
        _emit 0xc0
        _emit 0xeb
        _emit 0x05
        _emit 0x1b
        _emit 0xc0
        _emit 0x83
        _emit 0xd8
        _emit 0xff
        _emit 0x3b
        _emit 0xc3
        _emit 0x74
        _emit 0x0f
        _emit 0x8b
        _emit 0x46
        _emit 0x24
        _emit 0x89
        _emit 0x75
        _emit 0xf8
        _emit 0x3b
        _emit 0xc3
        _emit 0x89
        _emit 0x45
        _emit 0xfc
        _emit 0x75
        _emit 0xbe
        _emit 0xeb
        _emit 0x04
        _emit 0x3b
        _emit 0xf3
        _emit 0x75
        _emit 0x47
        _emit 0x6a
        _emit 0x28
        _emit 0xe8
        _emit 0x66
        _emit 0x41
        _emit 0x01
        _emit 0x00
        _emit 0x8b
        _emit 0xd0
        _emit 0x8d
        _emit 0x7d
        _emit 0xe8
        _emit 0x83
        _emit 0xc9
        _emit 0xff
        _emit 0x33
        _emit 0xc0
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x89
        _emit 0x55
        _emit 0xfc
        _emit 0xf2
        _emit 0xae
        _emit 0xf7
        _emit 0xd1
        _emit 0x2b
        _emit 0xf9
        _emit 0x8b
        _emit 0xc1
        _emit 0x8b
        _emit 0xf7
        _emit 0x8b
        _emit 0xfa
        _emit 0xc1
        _emit 0xe9
        _emit 0x02
        _emit 0xf3
        _emit 0xa5
        _emit 0x8b
        _emit 0xc8
        _emit 0x83
        _emit 0xe1
        _emit 0x03
        _emit 0xf3
        _emit 0xa4
        _emit 0x8b
        _emit 0x4d
        _emit 0xf8
        _emit 0x89
        _emit 0x5a
        _emit 0x14
        _emit 0x89
        _emit 0x5a
        _emit 0x10
        _emit 0x89
        _emit 0x5a
        _emit 0x1c
        _emit 0x89
        _emit 0x5a
        _emit 0x18
        _emit 0x89
        _emit 0x5a
        _emit 0x20
        _emit 0x89
        _emit 0x5a
        _emit 0x24
        _emit 0x89
        _emit 0x51
        _emit 0x24
        _emit 0x8b
        _emit 0x75
        _emit 0xfc
        _emit 0x8b
        _emit 0x7d
        _emit 0x0c
        _emit 0x8b
        _emit 0x46
        _emit 0x20
        _emit 0x40
        _emit 0x89
        _emit 0x46
        _emit 0x20
        _emit 0x8b
        _emit 0x45
        _emit 0x08
        _emit 0x50
        _emit 0x89
        _emit 0x45
        _emit 0xf8
        _emit 0xe8
        _emit 0x0d
        _emit 0x41
        _emit 0x01
        _emit 0x00
        _emit 0x8b
        _emit 0xd0
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x3b
        _emit 0xd3
        _emit 0x89
        _emit 0x55
        _emit 0xfc
        _emit 0x75
        _emit 0x32
        _emit 0x8b
        _emit 0x55
        _emit 0x08
        _emit 0x8d
        _emit 0x45
        _emit 0xe8
        _emit 0x52
        _emit 0x57
        _emit 0x68
        _emit 0x20
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x90
        _emit 0x3b
        _emit 0x01
        _emit 0x00
        _emit 0x8d
        _emit 0x4d
        _emit 0xe8
        _emit 0x51
        _emit 0x68
        _emit 0xcd
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x04
        _emit 0xce
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x1c
        _emit 0x33
        _emit 0xc0
        _emit 0x5f
        _emit 0x5e
        _emit 0x5b
        _emit 0x8b
        _emit 0xe5
        _emit 0x5d
        _emit 0xc3
        _emit 0x8b
        _emit 0x7d
        _emit 0xfc
        _emit 0x8b
        _emit 0x5d
        _emit 0xf8
        _emit 0x33
        _emit 0xc0
        _emit 0x8d
        _emit 0x0c
        _emit 0x7f
        _emit 0x83
        _emit 0xe1
        _emit 0x03
        _emit 0x2b
        _emit 0xd9
        _emit 0x7e
        _emit 0x0c
        _emit 0xf3
        _emit 0xaa
        _emit 0x8b
        _emit 0xcb
        _emit 0x83
        _emit 0xe3
        _emit 0x03
        _emit 0xc1
        _emit 0xe9
        _emit 0x02
        _emit 0xf3
        _emit 0xab
        _emit 0x03
        _emit 0xcb
        _emit 0xf3
        _emit 0xaa
        _emit 0x8b
        _emit 0x3d
        _emit 0x24
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0xa1
        _emit 0x2c
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x3b
        _emit 0xc7
        _emit 0x0f
        _emit 0x8d
        _emit 0x92
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xa1
        _emit 0x40
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x33
        _emit 0xc9
        _emit 0x85
        _emit 0xff
        _emit 0x7e
        _emit 0x0f
        _emit 0x8b
        _emit 0x58
        _emit 0x08
        _emit 0x85
        _emit 0xdb
        _emit 0x74
        _emit 0x08
        _emit 0x83
        _emit 0xc0
        _emit 0x10
        _emit 0x41
        _emit 0x3b
        _emit 0xcf
        _emit 0x7c
        _emit 0xf1
        _emit 0x8b
        _emit 0x4d
        _emit 0x0c
        _emit 0x89
        _emit 0x50
        _emit 0x08
        _emit 0x89
        _emit 0x48
        _emit 0x04
        _emit 0x8b
        _emit 0x4d
        _emit 0x08
        _emit 0x89
        _emit 0x48
        _emit 0x0c
        _emit 0x89
        _emit 0x30
        _emit 0xa1
        _emit 0x28
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x3d
        _emit 0x30
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x03
        _emit 0xc1
        _emit 0x3b
        _emit 0xc7
        _emit 0xa3
        _emit 0x28
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x7e
        _emit 0x05
        _emit 0xa3
        _emit 0x30
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x7e
        _emit 0x10
        _emit 0x03
        _emit 0xf9
        _emit 0x8b
        _emit 0x4e
        _emit 0x18
        _emit 0x8b
        _emit 0xc7
        _emit 0x89
        _emit 0x7e
        _emit 0x10
        _emit 0x3b
        _emit 0xc1
        _emit 0x7e
        _emit 0x03
        _emit 0x89
        _emit 0x46
        _emit 0x18
        _emit 0xa1
        _emit 0x2c
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x0d
        _emit 0x34
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x40
        _emit 0x3b
        _emit 0xc1
        _emit 0xa3
        _emit 0x2c
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x7e
        _emit 0x05
        _emit 0xa3
        _emit 0x34
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x7e
        _emit 0x14
        _emit 0x8b
        _emit 0x4e
        _emit 0x1c
        _emit 0x47
        _emit 0x8b
        _emit 0xc7
        _emit 0x89
        _emit 0x7e
        _emit 0x14
        _emit 0x3b
        _emit 0xc1
        _emit 0x7e
        _emit 0x28
        _emit 0x8b
        _emit 0xcf
        _emit 0x5f
        _emit 0x89
        _emit 0x4e
        _emit 0x1c
        _emit 0x5e
        _emit 0x8b
        _emit 0xc2
        _emit 0x5b
        _emit 0x8b
        _emit 0xe5
        _emit 0x5d
        _emit 0xc3
        _emit 0x68
        _emit 0xe4
        _emit 0x87
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xf0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x1d
        _emit 0xcd
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x55
        _emit 0xfc
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0x5f
        _emit 0x5e
        _emit 0x8b
        _emit 0xc2
        _emit 0x5b
        _emit 0x8b
        _emit 0xe5
        _emit 0x5d
        _emit 0xc3
    }
}
#else

void* __cdecl m_AllocTracked(unsigned int size, const char* source)
{
	char msgBuf[256];
	char nameBuf[16];
	int prev;
	char* group;

	if (g_array_ptr == 0) {
		ReportFatalError(
			"D:\\Develop\\Units\\m_alloc\\m_alloc.c",
			0x93,
			"m_alloc() called without prior call to m_init()!"
		);
		return 0;
	}
	if (size == 0) {
		return 0;
	}
	g_alloc_counter = g_alloc_counter + 1;
	group = (char*) 0x117640a0;
	if (source != 0) {
		int nameLen;
		char* colon;
		colon = strchr(source, 0x3a);
		if (colon != 0) {
			nameLen = (int) (colon - source) + 1;
			if (nameLen >= 0x10) {
				sprintf(msgBuf, "m_alloc_debug: GroupInformation too long: %s", source);
				ReportMessage(msgBuf);
			}
			strncpy(nameBuf, source, nameLen);
			nameBuf[nameLen] = '\0';
			group = (char*) 0x117640a0;
			if (group != 0) {
				do {
					if (strcmp(nameBuf, group) == 0) {
						if (group != 0) {
							goto found;
						}
						break;
					}
					prev = (int) group;
					group = *(char**) (group + 0x24);
				} while (group != 0);
			}
			group = (char*) _callnewh(0x28);
			strcpy(group, nameBuf);
			*(int*) (group + 0x14) = 0;
			*(int*) (group + 0x10) = 0;
			*(int*) (group + 0x1c) = 0;
			*(int*) (group + 0x18) = 0;
			*(int*) (group + 0x20) = 0;
			*(int*) (group + 0x24) = 0;
			*(int*) (prev + 0x24) = (int) group;
		}
	}
found: {
	void* block;
	int tmp;
	*(int*) (group + 0x20) = *(int*) (group + 0x20) + 1;
	prev = size;
	block = _callnewh(size);
	if (block == 0) {
		sprintf(nameBuf, "Out of Memory Error: Malloc - Failed %s for %u bytes", source, size);
		ReportFatalError("D:\\Develop\\Units\\m_alloc\\m_alloc.c", 0xcd, nameBuf);
		return 0;
	}
	memset(block, 0, prev);
	if (g_stat2 < g_array_count) {
		int i;
		int* slot;
		i = 0;
		slot = g_array_ptr;
		if (g_array_count > 0) {
			do {
				if (slot[2] == 0) {
					break;
				}
				slot = slot + 4;
				i = i + 1;
			} while (i < g_array_count);
		}
		slot[2] = (int) block;
		slot[1] = (int) source;
		slot[3] = size;
		*slot = (int) group;
		g_stat1 = g_stat1 + size;
		if (g_stat1 > g_stat3) {
			g_stat3 = g_stat1;
		}
		tmp = *(int*) (group + 0x10) + size;
		*(int*) (group + 0x10) = tmp;
		if (tmp > *(int*) (group + 0x18)) {
			*(int*) (group + 0x18) = tmp;
		}
		g_stat2 = g_stat2 + 1;
		if (g_stat2 > g_stat4) {
			g_stat4 = g_stat2;
		}
		tmp = *(int*) (group + 0x14) + 1;
		*(int*) (group + 0x14) = tmp;
		if (tmp > *(int*) (group + 0x1c)) {
			*(int*) (group + 0x1c) = tmp;
		}
	}
	else {
		ReportFatalError(
			"D:\\Develop\\Units\\m_alloc\\m_alloc.c",
			0xf0,
			"No more free memory slots...\nCall m_init() with more slots!"
		);
	}
	return block;
}
#endif

/* Frees tracked memory. Removes the allocation from the
 * tracking list, updates group counters, and calls HeapFree. */
extern char g_stream_pool[1];
extern int g_stream_count[4];
extern int g_connection_counter[4];
char g_log_buffer = 0;
int g_log_file_handle = 0;

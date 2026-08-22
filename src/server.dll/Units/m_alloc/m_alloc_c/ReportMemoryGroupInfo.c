// FUNCTION: SERVER 0x10006990
#include <stdio.h>
#include <string.h>

#pragma intrinsic(memset, strcmp, strcpy)

void __cdecl ReportFatalError(char*, unsigned int, char*); /* 0x10003520 */
void __cdecl ReportMessage(char* msg);
void* __cdecl _callnewh(int);
void __cdecl ReportMemoryGroupInfo(const char* toggle);
extern void __cdecl LogMessageInternal(const char*, int, const char*, int);

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x10006990 (612B)
// Generated via .venv/bin/rebrew asm 0x10006990 --json
__declspec(naked) void __cdecl ReportMemoryGroupInfo(const char* filter)
{
    __asm {
        _emit 0xa1
        _emit 0x28
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x0d
        _emit 0x2c
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x81
        _emit 0xec
        _emit 0x10
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x2b
        _emit 0x85
        _emit 0xc9
        _emit 0x75
        _emit 0x27
        _emit 0xa1
        _emit 0x30
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x15
        _emit 0x34
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0xc8
        _emit 0xc1
        _emit 0xf9
        _emit 0x0a
        _emit 0x51
        _emit 0x50
        _emit 0x52
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x1c
        _emit 0x68
        _emit 0xa0
        _emit 0x8a
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0xce
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x14
        _emit 0xeb
        _emit 0x2d
        _emit 0x8b
        _emit 0xd0
        _emit 0xc1
        _emit 0xfa
        _emit 0x0a
        _emit 0x52
        _emit 0x8b
        _emit 0x15
        _emit 0x34
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x50
        _emit 0xa1
        _emit 0x30
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x51
        _emit 0x8b
        _emit 0xc8
        _emit 0xc1
        _emit 0xf9
        _emit 0x0a
        _emit 0x51
        _emit 0x50
        _emit 0x52
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x28
        _emit 0x68
        _emit 0x2c
        _emit 0x8a
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x9f
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x20
        _emit 0x55
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0x68
        _emit 0xb5
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x2c
        _emit 0xcc
        _emit 0xff
        _emit 0xff
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x10
        _emit 0x8a
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xb6
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x16
        _emit 0xcc
        _emit 0xff
        _emit 0xff
        _emit 0xbd
        _emit 0xa0
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x83
        _emit 0xc4
        _emit 0x20
        _emit 0x8b
        _emit 0xd5
        _emit 0x85
        _emit 0xd2
        _emit 0x0f
        _emit 0x84
        _emit 0x97
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x53
        _emit 0x56
        _emit 0x57
        _emit 0x8b
        _emit 0xb4
        _emit 0x24
        _emit 0x24
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x85
        _emit 0xf6
        _emit 0x74
        _emit 0x12
        _emit 0x56
        _emit 0x55
        _emit 0xe8
        _emit 0x9f
        _emit 0x45
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x04
        _emit 0xb3
        _emit 0x01
        _emit 0xeb
        _emit 0x02
        _emit 0x32
        _emit 0xdb
        _emit 0x8b
        _emit 0x45
        _emit 0x1c
        _emit 0x85
        _emit 0xc0
        _emit 0x0f
        _emit 0x8e
        _emit 0x5c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0x7d
        _emit 0x00
        _emit 0x21
        _emit 0x75
        _emit 0x0f
        _emit 0x8b
        _emit 0x45
        _emit 0x14
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x08
        _emit 0x84
        _emit 0xdb
        _emit 0x0f
        _emit 0x84
        _emit 0x47
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x85
        _emit 0xf6
        _emit 0x74
        _emit 0x08
        _emit 0x84
        _emit 0xdb
        _emit 0x0f
        _emit 0x84
        _emit 0x3b
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xfd
        _emit 0x83
        _emit 0xc9
        _emit 0xff
        _emit 0x33
        _emit 0xc0
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0xf2
        _emit 0xae
        _emit 0xf7
        _emit 0xd1
        _emit 0x2b
        _emit 0xf9
        _emit 0x6a
        _emit 0x3a
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
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x14
        _emit 0x51
        _emit 0xe8
        _emit 0x87
        _emit 0x3a
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x03
        _emit 0xc6
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x45
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x32
        _emit 0x8b
        _emit 0x4d
        _emit 0x14
        _emit 0x85
        _emit 0xc9
        _emit 0x75
        _emit 0x2b
        _emit 0x8b
        _emit 0x55
        _emit 0x20
        _emit 0x8b
        _emit 0x45
        _emit 0x18
        _emit 0x8b
        _emit 0x4d
        _emit 0x1c
        _emit 0x52
        _emit 0x8b
        _emit 0xd0
        _emit 0x51
        _emit 0xc1
        _emit 0xfa
        _emit 0x0a
        _emit 0x52
        _emit 0x50
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x20
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x30
        _emit 0x50
        _emit 0x68
        _emit 0xd4
        _emit 0x89
        _emit 0x02
        _emit 0x10
        _emit 0x51
        _emit 0xe8
        _emit 0xa2
        _emit 0x37
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x1c
        _emit 0xeb
        _emit 0x34
        _emit 0x8b
        _emit 0x55
        _emit 0x20
        _emit 0x8b
        _emit 0x4d
        _emit 0x18
        _emit 0x52
        _emit 0x8b
        _emit 0x55
        _emit 0x1c
        _emit 0x52
        _emit 0x8b
        _emit 0x55
        _emit 0x14
        _emit 0x52
        _emit 0x8b
        _emit 0xd1
        _emit 0xc1
        _emit 0xfa
        _emit 0x0a
        _emit 0x52
        _emit 0x8b
        _emit 0xd0
        _emit 0xc1
        _emit 0xfa
        _emit 0x0a
        _emit 0x52
        _emit 0x51
        _emit 0x50
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x2c
        _emit 0x50
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x40
        _emit 0x68
        _emit 0x8c
        _emit 0x89
        _emit 0x02
        _emit 0x10
        _emit 0x51
        _emit 0xe8
        _emit 0x6c
        _emit 0x37
        _emit 0x01
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x28
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x20
        _emit 0x6a
        _emit 0x01
        _emit 0x52
        _emit 0x68
        _emit 0xcc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xfa
        _emit 0xca
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x84
        _emit 0xdb
        _emit 0x74
        _emit 0x78
        _emit 0xa1
        _emit 0x24
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x8b
        _emit 0x35
        _emit 0x40
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x33
        _emit 0xff
        _emit 0x85
        _emit 0xc0
        _emit 0x7e
        _emit 0x4e
        _emit 0x8b
        _emit 0x46
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x74
        _emit 0x3a
        _emit 0x39
        _emit 0x2e
        _emit 0x75
        _emit 0x36
        _emit 0x8b
        _emit 0x46
        _emit 0x0c
        _emit 0x8b
        _emit 0x56
        _emit 0x04
        _emit 0x8b
        _emit 0xc8
        _emit 0xc1
        _emit 0xf9
        _emit 0x0a
        _emit 0x51
        _emit 0x50
        _emit 0x52
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x2c
        _emit 0x68
        _emit 0x74
        _emit 0x89
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x13
        _emit 0x37
        _emit 0x01
        _emit 0x00
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x34
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0x68
        _emit 0xd5
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xa4
        _emit 0xca
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x24
        _emit 0xa1
        _emit 0x24
        _emit 0x46
        _emit 0x03
        _emit 0x10
        _emit 0x47
        _emit 0x83
        _emit 0xc6
        _emit 0x10
        _emit 0x3b
        _emit 0xf8
        _emit 0x7c
        _emit 0xb2
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x58
        _emit 0x89
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xd8
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x7e
        _emit 0xca
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x8b
        _emit 0x6d
        _emit 0x24
        _emit 0x85
        _emit 0xed
        _emit 0x0f
        _emit 0x85
        _emit 0x6f
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x5f
        _emit 0x5e
        _emit 0x5b
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x40
        _emit 0x89
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xdc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x88
        _emit 0x88
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x57
        _emit 0xca
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x5d
        _emit 0x81
        _emit 0xc4
        _emit 0x10
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0xc3
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd

void __cdecl ReportMemoryGroupInfo(const char* filter)
{
	char name[16];
	char buf[1024];
	char* group;
	int* slot;
	int i;
	char matched;

	if (*(int*) 0x10034628 == 0 && *(int*) 0x1003462c == 0) {
		sprintf(buf, (char*) 0x10028aa0, *(int*) 0x10034634, *(int*) 0x10034630, *(int*) 0x10034630 >> 10);
	}
	else {
		sprintf(
			buf,
			(char*) 0x10028a2c,
			*(int*) 0x10034634,
			*(int*) 0x10034630,
			*(int*) 0x10034630 >> 10,
			*(int*) 0x1003462c,
			*(int*) 0x10034628,
			*(int*) 0x10034628 >> 10
		);
	}

	LogMessageInternal((char*) 0x10028888, 0x1b5, buf, 1);
	LogMessageInternal((char*) 0x10028888, 0x1b6, (char*) 0x10028a10, 1);

	group = (char*) 0x117640a0;

	if (group == 0) {
		goto done;
	}

	do {
		if (filter == 0 || strstr(group, filter) == 0) {
			matched = 0;
		}
		else {
			matched = 1;
		}

		if (*(int*) (group + 0x1c) <= 0) {
			goto next_group;
		}

		if (*group == '!' && *(int*) (group + 0x14) == 0 && !matched) {
			goto next_group;
		}

		if (filter != 0 && !matched) {
			goto next_group;
		}

		strcpy(name, group);

		{
			char* p = strrchr(name, ':');
			if (p != 0) {
				*p = 0;
			}
		}

		if (*(int*) (group + 0x10) == 0 && *(int*) (group + 0x14) == 0) {
			sprintf(
				buf,
				(char*) 0x100289d4,
				name,
				*(int*) (group + 0x18),
				*(int*) (group + 0x18) >> 10,
				*(int*) (group + 0x1c),
				*(int*) (group + 0x20)
			);
		}
		else {
			sprintf(
				buf,
				(char*) 0x1002898c,
				name,
				*(int*) (group + 0x10),
				*(int*) (group + 0x18),
				*(int*) (group + 0x10) >> 10,
				*(int*) (group + 0x18) >> 10,
				*(int*) (group + 0x14),
				*(int*) (group + 0x1c),
				*(int*) (group + 0x20)
			);
		}

		LogMessageInternal((char*) 0x10028888, 0x1cc, buf, 1);

		if (matched) {
			slot = *(int**) 0x10034640;
			for (i = 0; i < *(int*) 0x10034624; i++) {
				if (slot[2] != 0 && slot[0] == (int) group) {
					sprintf(buf, (char*) 0x10028974, (char*) slot[1], slot[3], slot[3] >> 10);
					LogMessageInternal((char*) 0x10028888, 0x1d5, buf, 1);
				}
				slot += 4;
			}
			LogMessageInternal((char*) 0x10028888, 0x1d8, (char*) 0x10028958, 1);
		}

	next_group:
		group = *(char**) (group + 0x24);
	} while (group != 0);

done:
	LogMessageInternal((char*) 0x10028888, 0x1dc, (char*) 0x10028940, 1);
}
#endif

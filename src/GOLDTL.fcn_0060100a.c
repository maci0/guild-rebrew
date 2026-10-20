#pragma optimize("s", on)
#include <stdio.h>
#include <windows.h>

typedef struct ENTRY_60100a ENTRY_60100a;
struct ENTRY_60100a {
	int f0;
	int f4;
	float f8;
};

typedef struct SELF_60100a SELF_60100a;
struct SELF_60100a {
	char pad_000[4];
	unsigned int count;
};

extern ENTRY_60100a* __fastcall fcn_006008f0(SELF_60100a* self);

/* Writes one "%.9f, %d, %d" line per pending entry to d:\dump.txt. */
/* ADDRESS: GOLDTL 0x0060100a */
int __fastcall fcn_0060100a(SELF_60100a* self)
{
	volatile HANDLE file;
	DWORD written;
	char buf[80];
	ENTRY_60100a* entry;
	char* p;
	char c;

	file = CreateFileA("d:\\dump.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	while (self->count > 0) {
		entry = fcn_006008f0(self);
		sprintf(buf, "%.9f, %d, %d\r\n", entry->f8, entry->f0, entry->f4);
		p = buf;
		do {
			c = *p++;
		} while (c != 0);
		WriteFile(file, buf, p - (buf + 1), &written, 0);
	}
	CloseHandle(file);
	return 0;
}

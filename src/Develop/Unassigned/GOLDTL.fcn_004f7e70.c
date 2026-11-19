#include <string.h>

// SIZE 0x10
typedef struct {
	short x0;
	unsigned char b2;
	char pad3;
	int f4;
	int f8;
	int fc;
} Info;

extern char g_690560[];
extern char g_679060[];

void __cdecl fcn_004fcda0(short, int, Info*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl fcn_004fa5f0(void*, int, int);


/* ADDRESS: GOLDTL 0x004f7e70 */
int __cdecl fcn_004f7e70(unsigned char* entity, int* context)
{
	Info info;
	char buf[0x400];
	int base;

	if (*context != 3 && *context != 1)
		return 1;
	if (entity[0x166] == 0 && entity[0x169] == 0 && (*(int*) (entity + 0x1cc) & 0xe00) == 0)
		return 1;
	if (*context == 3 && entity[2] == 6) {
		fcn_004fcda0(*(short*) entity, 0, &info);
		memset(buf, 0, sizeof(buf));
		base = (entity[9] != 0 ? 0x28 : 0) + 0x253;
		io_FormatTextBuffer(buf, (int) g_690560, 0x1d96);
		if (entity[0x166] != 0)
			io_FormatTextBuffer(buf + strlen(buf), 0x1d97, entity[0x166] + base, info.f4);
		if (entity[0x169] != 0)
			io_FormatTextBuffer(buf + strlen(buf), 0x1d97, entity[0x169] + base, info.f8);
		if (info.b2 != 0)
			io_FormatTextBuffer(buf + strlen(buf), 0x1d97, info.b2 + base, info.fc);
		fcn_004fa5f0(buf, 1, 0x657c7);
	} else if (*context == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) context + 0x14, (int) "%s", 0x1d96);
	}
	return 2;
}

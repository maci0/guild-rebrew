


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_004f4f60(int, int, int, int, int);

void __cdecl fcn_00578860(char* e)
{
	char buf[0x400];
	char* p;
	char* o;

	if ((e[0x78] & 4) != 0) {
		return;
	}
	p = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
	for (o = fcn_005463a0(1, 0, 0x89); o != 0; o = he_fn_Handlung()) {
		if (o != e && *(unsigned short*) (o + 8) == *(unsigned short*) (e + 8) && *(int*) (o + 0xb0) == *(int*) (e + 0xb0)) {
			if (p != 0) {
				io_FormatTextBuffer(buf, 0x40a2, *(unsigned short*) p);
				fcn_00545d40(((struct house*)g_7f4ca0)[*(unsigned short*) (e + 8)].handle, -1, buf, 0, 0x5fa, 0);
			}
			*(int*) (e + 0x84) = fcn_004c5620(-1, e);
			fcn_00546190(e);
			return;
		}
	}
	if (gm_LookupEntityRecordById(*(int*) (e + 0xb4)) == 0) {
		fcn_00546190(e);
		return;
	}
	*(int*) (e + 0xbc) = 0;
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
	fcn_005100f0(((struct house*)g_7f4ca0)[*(unsigned short*) (e + 8)].handle, -*(int*) (e + 0xb8));
	*(int*) (e + 0x70) = 0;
	fcn_004f4f60(0x1b, 1, ((struct house*)g_7f4ca0)[*(unsigned short*) (e + 8)].handle, p != 0 ? *(int*) (p + 4) : -1,
	    p != 0 && *(char**) (p + 0x170) != 0 ? *(int*) (*(char**) (p + 0x170) + 1) : -1);
}

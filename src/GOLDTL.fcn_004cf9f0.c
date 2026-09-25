#include <string.h>

// FUNCTION: GOLDTL 0x4cf9f0
// SIZE: 11

int __cdecl fcn_004cf9f0(char* p)
{
	return *(int*) (p + 0x204);
}

/* 0x4d4790 lives in this file because it calls fcn_004cf9f0 and keeps a value
 * in edx across that call: msvc6 does that only for a callee compiled earlier in
 * the same translation unit, whose register use it has already seen. */

extern unsigned short* g_772e98;

void* __cdecl fcn_004ce610(char*);
float __cdecl fcn_004ff040(char*);
void __cdecl fcn_00417b50(int, int, float, float, float, float);
void __cdecl fcn_00406120(char*);
int __cdecl fcn_004d4700(void);
char* __cdecl fcn_0040c230(char*, int (__cdecl*)(void), int, int, int);
void __cdecl fcn_004234e0(int, char*, int, int, int, int, int);
unsigned int __cdecl fcn_004e6cb0(int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_004458a0(char*, char*, char*);
void __cdecl fcn_00442c00(char*, int);
void __cdecl fcn_00533a40(char*);

// FUNCTION: GOLDTL 0x004d4790
// SIZE: 447

int __cdecl fcn_004d4790(char* e)
{
	char buf[0x100];
	char* p;
	char* q;

	fcn_004ce610(e);
	if (fcn_004ff040(e) < 0.05) {
		fcn_00417b50(*(int*) (*(char**) (e + 0x184) + 0x34), 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
		fcn_00406120(*(char**) (e + 0x184));
		p = fcn_0040c230(*(char**) (e + 0x184), fcn_004d4700, 0x14, 0x36, 1);
		strcpy(p + 0xf0, "kampf/todumfallen");
		e[8] = 0;
		*(int*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x220) = 0;
		fcn_004234e0(0, "Schmerzschrei", 1, 0x3f, 0x7f, 0, 0);
		if (fcn_004e6cb0(100) > 50) {
			*(int*) (e + 0x24) = (int) (-(int) *(float*) (e + 0x1c) - 20.0);
			fcn_0051af00(buf, 0x1181, *(unsigned short*) e);
		} else {
			*(int*) (e + 0x24) = (int) (10.0 - (int) *(float*) (e + 0x1c));
			fcn_0051af00(buf, 0x1182, *(unsigned short*) e);
		}
		q = *(char**) (e + 0x1ac);
		if (q != 0) {
			fcn_004458a0(q, *(char**) (*(char**) (e + 0x184) + 0x34) + 0x4c, *(char**) (*(char**) (e + 0x184) + 0x34) + 0x18c);
			fcn_00442c00(q, 1);
			*(char**) (e + 0x1ac) = 0;
			*(int*) (fcn_004cf9f0(q) + 0xa) = *g_772e98;
		}
		fcn_00533a40(buf);
		return 1;
	}
	return 0;
}

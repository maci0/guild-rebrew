#include <stdio.h>

typedef void (__cdecl* dispose_fn_4398d0)(char* obj);

extern int g_6b8010;
extern int g_67a370;
extern char g_10432c0[];
extern char g_1040640[];

void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_0041ddd0(void* p);
void __cdecl fcn_00452420(char* p);
void __cdecl fcn_00433780(char* obj);
void __cdecl fcn_00439b30(char* obj);
void __cdecl fcn_00456d50(void);
void __cdecl fcn_004379a0(char* u, int b, int c, void (__cdecl* cb)(void), char* obj);
void __cdecl fcn_00456b80(char* obj);
void __cdecl fcn_00418f90(int a);
void __cdecl fcn_00439d80(char* obj);

// FUNCTION: GOLDTL 0x4398d0
// SIZE: 450

/* Disposes a scene object and its children, switching to its universe first. */
void __cdecl fcn_004398d0(char* obj)
{
	char* u;
	char* p;
	char* next;
	int saved;
	int idx;
	char msg[0x400];

	if (obj == 0) {
		return;
	}
	saved = g_6b8010;
	u = *(char**) (obj + 0x20c);
	idx = -1;
	if (((char*)g_67a370) != u) {
		sprintf(msg, "d3_DisposeObject(): invalid universe by object %s", obj);
		idx = (unsigned int) (u - g_10432c0) / 0x3dc;
		fcn_004432d0(idx, 1);
	}
	if (*(dispose_fn_4398d0**) (obj + 0x1ec) != 0 && **(dispose_fn_4398d0**) (obj + 0x1ec) != 0) {
		(**(dispose_fn_4398d0**) (obj + 0x1ec))(obj);
	}
	if (*(void**) (obj + 0x1d4) != 0) {
		fcn_0041ddd0(*(void**) (obj + 0x1d4));
		*(void**) (obj + 0x1d4) = 0;
	}
	if (*(int*) (obj + 0x218) == 1 && *(int*) (obj + 0x21c) != 1) {
		*(int*) (obj + 0x218) = *(int*) (obj + 0x21c);
	}
	for (p = *(char**) (u + 0xa4); p != g_1040640; p = next) {
		next = *(char**) (p + 0x314);
		if (*(char**) (p + 0x2e4) == obj) {
			fcn_00452420(p);
		}
	}
	if (*(int*) (obj + 0x1d0) != 0) {
		fcn_00433780(obj);
	}
	if (*(unsigned char*) (obj + 0x214) & 2) {
		fcn_00439b30(obj);
	}
	if (*(int*) (obj + 0x218) == 8) {
		fcn_004379a0(u, 0, 0xc0, fcn_00456d50, obj);
	}
	if (*(unsigned char*) (obj + 0x215) & 1) {
		fcn_00456b80(obj);
	}
	if (*(void**) (obj + 0x1e8) != 0) {
		fcn_0041ddd0(*(void**) (obj + 0x1e8));
		*(void**) (obj + 0x1e8) = 0;
	}
	if (*(char**) (obj + 0x200) != 0) {
		fcn_004398d0(*(char**) (obj + 0x200));
	}
	if (*(char**) (obj + 0x1f4) != 0 && !(*(unsigned char*) (*(char**) (obj + 0x1f4) + 0x214) & 1)) {
		fcn_004398d0(*(char**) (obj + 0x1f4));
	}
	fcn_00418f90(*(int*) (obj + 0x210));
	fcn_00439d80(obj);
	fcn_0041ddd0(obj);
	if (idx != -1) {
		fcn_004432d0(saved, 1);
	}
}

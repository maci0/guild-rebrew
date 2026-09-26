// FUNCTION: GOLDTL 0x00427f00
// SIZE: 803

#include <string.h>

extern char* g_6b7e98;
extern char g_6795b4[];
extern char g_6795a8[];
extern char g_679584[];
extern char g_679564[];
extern char g_679554[];
extern char g_679540[];

void* __cdecl fcn_0041db70(int size, char* tag);
void __cdecl fcn_0041ddd0(void* p);
void __cdecl fcn_00426680(int, int*);
int __cdecl fcn_00427830(char* g, int v);
void __cdecl fcn_00427480(void);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_00427f00(char* g)
{
	int tok[0x19];
	int* a;
	int* b;
	char* saved;
	int depth;

	depth = 0;
	a = (int*) fcn_0041db70(0x5300, g_6795b4);
	b = (int*) fcn_0041db70(0x1800, g_6795a8);
	*a = 0;
	*b = 0;
	*(void**) (g + 0x108) = fcn_0041db70(0x1800, g_6795a8);
	*(void**) (g + 0x10c) = fcn_0041db70(0x5300, g_6795b4);
	saved = g_6b7e98;
	g_6b7e98 = g;
	*(int*) (g + 0x118) = *(int*) (g + 0x11c);
	for (;;) {
		fcn_00426680(*(int*) (g_6b7e98 + 0x118), tok);
		if (tok[0] == 8 && depth == 0) {
			if (fcn_00427830(g, tok[1]) == 0) {
				fcn_0041ddd0(a);
				fcn_0041ddd0(b);
				fcn_0041ddd0(*(void**) (g + 0x108));
				*(void**) (g + 0x108) = 0;
				fcn_0041ddd0(*(void**) (g + 0x10c));
				*(void**) (g + 0x10c) = 0;
				return 0;
			}
			continue;
		}
		if (tok[0] == 1) {
			if (tok[1] == 8) {
				depth++;
			} else if (tok[1] == 9) {
				depth--;
			}
		}
		if (depth < 0) {
			fcn_00425bf0(g, *(int*) (g + 0x118), g_679564);
			fcn_0041ddd0(a);
			fcn_0041ddd0(b);
			fcn_0041ddd0(*(void**) (g + 0x108));
			*(void**) (g + 0x108) = 0;
			fcn_0041ddd0(*(void**) (g + 0x10c));
			*(void**) (g + 0x10c) = 0;
			return 0;
		}
		if (tok[0] == 0xa) {
			if (tok[1] == 5) {
				fcn_00427480();
			}
		} else if (tok[0] == 0xc) {
			break;
		}
	}
	if (depth != 0) {
		fcn_00425bf0(g, 0, g_679584);
		fcn_0041ddd0(a);
		fcn_0041ddd0(b);
		fcn_0041ddd0(*(void**) (g + 0x108));
		*(void**) (g + 0x108) = 0;
		fcn_0041ddd0(*(void**) (g + 0x10c));
		*(void**) (g + 0x10c) = 0;
		return 0;
	}
	if (*(int*) (g + 0x114) != 0) {
		memcpy(b, *(void**) (g + 0x108), *(int*) (g + 0x114) * 0x30);
		fcn_0041ddd0(*(void**) (g + 0x108));
		*(void**) (g + 0x108) = 0;
		*(void**) (g + 0x108) = fcn_0041db70(*(int*) (g + 0x114) * 0x30, g_679554);
		memcpy(*(void**) (g + 0x108), b, *(int*) (g + 0x114) * 0x30);
	} else {
		fcn_0041ddd0(*(void**) (g + 0x108));
		*(void**) (g + 0x108) = 0;
	}
	if (*(int*) (g + 0x110) != 0) {
		memcpy(a, *(void**) (g + 0x10c), *(int*) (g + 0x110) * 0x14c);
		fcn_0041ddd0(*(void**) (g + 0x10c));
		*(void**) (g + 0x10c) = 0;
		*(void**) (g + 0x10c) = fcn_0041db70(*(int*) (g + 0x110) * 0x14c, g_679540);
		memcpy(*(void**) (g + 0x10c), a, *(int*) (g + 0x110) * 0x14c);
	} else {
		fcn_0041ddd0(*(void**) (g + 0x10c));
		*(void**) (g + 0x10c) = 0;
	}
	g_6b7e98 = saved;
	fcn_0041ddd0(a);
	fcn_0041ddd0(b);
	return 1;
}

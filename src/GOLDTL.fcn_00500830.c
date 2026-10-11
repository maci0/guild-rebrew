// FUNCTION: GOLDTL 0x00500830

#include <string.h>

extern int g_773d3c;
extern int g_773d40;
extern char* g_773d44;

int __cdecl fcn_00475830(char* path);
int __cdecl fcn_00475c10(char* path);
int __cdecl fcn_004788b0(int a, int b, int c, int d, int h, int e, int f);
void __cdecl fcn_004798c0(int o, int x);
void __cdecl m_FreeTracked(int o);
void __cdecl fcn_00475f80(int h);

void __cdecl fcn_00500830(char* path)
{
	int k;
	int h;
	int o;
	char* d;

	k = fcn_00475830(path);
	if (k == -1) {
		return;
	}
	h = fcn_00475c10(path);
	if (h == 0) {
		return;
	}
	o = fcn_004788b0(0, 0, k & 0xffff, k >> 16, h, 0, 1);
	if (o != 0) {
		fcn_004798c0(o, g_773d3c);
		m_FreeTracked(o);
		strcpy(g_773d44 + g_773d40 * 0x30, strrchr(path, '\\') + 1);
		d = strrchr(g_773d44 + g_773d40 * 0x30, '.');
		if (d != 0) {
			*d = 0;
		}
		g_773d40++;
	}
	fcn_00475f80(h);
}

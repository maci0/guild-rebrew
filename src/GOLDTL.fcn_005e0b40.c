// FUNCTION: GOLDTL 0x005e0b40
// SIZE: 259

#include <string.h>

extern char* g_1015ea0;
extern int g_1015ea4;
extern char g_102d150[];
extern char g_102d29c[];
extern int g_7e46ac;
extern unsigned char g_14cf950;
extern int g_774654;
extern int g_14ce8e0;
extern int g_7725d0;

int __cdecl fcn_00467240(int, int, int, int, int);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_00472380(int, char*);
void __cdecl fcn_00474cf0(int);
void __cdecl fcn_00472770(int, int);
int __cdecl fcn_005373e0(void*, int);
char* __cdecl fcn_00471f80(int);
void __cdecl fcn_0046b2b0(int);

int __cdecl fcn_005e0b40(int a, int b, char* text)
{
	int result;
	int h;

	result = 0;
	h = fcn_00467240(a, b, 0, g_1015ea4, 1);
	fcn_00472900(h, 0x53);
	fcn_00472380(h, text);
	fcn_00474cf0(h);
	*(int*) (g_102d150 + *(int*) (g_1015ea0 + h * 0x2f4 + 0x88) * 0x160) = 0x80;
	*(int*) (g_102d29c + *(int*) (g_1015ea0 + h * 0x2f4 + 0x88) * 0x160) = 0x110;
	fcn_00472770(h, 0x1f);
	while (fcn_005373e0(fcn_005e0b40, g_7e46ac) != 0) {
		if (g_14cf950 == 0x1c) {
			strcpy(text, fcn_00471f80(h));
			g_774654 = 1;
			result = 1;
		}
		if (g_14ce8e0 != 0 || g_7725d0 == 0) {
			g_774654 = 1;
		}
	}
	fcn_0046b2b0(h);
	return result;
}

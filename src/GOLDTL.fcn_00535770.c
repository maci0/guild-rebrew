extern int g_14a5508;
extern int g_7e46ac;

// FUNCTION: GOLD 0x0052fc40
// FUNCTION: GOLDTL 0x535770

#include <string.h>

__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
int __cdecl fcn_004c5790(int, char*);
int __cdecl fcn_005268c0(int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_00535770(int flags)
{
	char buf[0x7c];
	unsigned int start;
	int s;
	int h;

	start = timeGetTime();
	memset(buf, 0, sizeof(buf));
	strcpy(buf, "sv_NetworkSync");
	s = fcn_004c5790(0xe, buf);
	g_7e46ac = flags;
	flags |= 0x300000;
	h = fcn_005268c0(g_14a5508, 0);
	fcn_00471af0(h, 0);
	while (fcn_004c4450(s) == 0) {
		if (timeGetTime() > start + 0x5dc) {
			fcn_00471af0(h, 1);
		}
		fcn_005373e0(0, flags);
	}
	fcn_00471e30(h);
}

// FUNCTION: GOLD 0x004d1e00
// SIZE: 173
// FUNCTION: GOLDTL 0x4d2e60
// SIZE: 173

extern int g_7725c8;
extern int g_774930;
extern int g_7e46ac;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_68bd68[];
extern char g_68bd54[];
extern char g_68bd44[];
extern char g_68bd2c[];
extern char g_68bd14[];
extern char g_68bcec[];

unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_004c2c50(char*);
void __cdecl fcn_00536bb0(void);
void __cdecl fcn_0052a960(char*);
char* __cdecl fcn_00426fd0(char*);
void __cdecl fcn_00428230(char*);
void __cdecl fcn_004cfa00(int);

void __cdecl fcn_004d2e60(void)
{
	int r;
	char* p;

	g_7725c8 = 1;
	if (g_774930 != 0) {
		r = fcn_0042e410(100);
		if (r < 20)
			fcn_004c2c50(g_68bd68);
		else if (r < 40)
			fcn_004c2c50(g_68bd54);
		else if (r < 60)
			fcn_004c2c50(g_68bd44);
		else if (r < 80)
			fcn_004c2c50(g_68bd2c);
		else
			fcn_004c2c50(g_68bd14);
	}
	g_7e46ac = 0x7d6c6;
	fcn_00536bb0();
	fcn_0052a960(((char*)&g_7f4c00));
	p = fcn_00426fd0(g_68bcec);
	if (p != 0) {
		fcn_00428230(p);
		fcn_004cfa00(*(int*) (p + 0x100));
	}
	g_7725c8 = 0;
}

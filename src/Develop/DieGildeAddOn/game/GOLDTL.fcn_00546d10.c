extern int g_7749d4;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern void (__cdecl* g_7dc440[])(unsigned char*);

// SIZE 0x14c
struct s_77e980 {
	unsigned char b0;
	char pad[0x51];
	char f52[0x26];
	unsigned char b78;
	char pad2[0xd3];
};

extern unit_77e980 g_77e980[1024];




void __cdecl fcn_00546b40(void);
void __cdecl fcn_00546850(struct s_77e980*);
int __cdecl fcn_00500cb0(char*, char*);
void __cdecl fcn_00546be0(struct s_77e980*);

void __cdecl fcn_00546d10(void)
{
	int i;

	fcn_00546b40();
	for (i = 0; i <= g_7749d4 && i < 1024; i++) {
		if (((struct s_77e980*)g_77e980)[i].b0 != 0 && (((struct s_77e980*)g_77e980)[i].b78 & 0x18) == 0) {
			fcn_00546850(&((struct s_77e980*)g_77e980)[i]);
			if (fcn_00500cb0(((char*)&g_7f4c00), ((struct s_77e980*)g_77e980)[i].f52) > 0 && ((struct s_77e980*)g_77e980)[i].b0 < 0xa7) {
				fcn_00546be0(&((struct s_77e980*)g_77e980)[i]);
				g_7dc440[((struct s_77e980*)g_77e980)[i].b0](&((struct s_77e980*)g_77e980)[i].b0);
			}
		}
	}
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_77dda0[3040];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_77dda1[383];
unsigned char _dpad_77df21[255];
unsigned char _dpad_77e021[127];
unsigned char _dpad_77e0a1[3];
unsigned char _dpad_77e0ac[2036];
unsigned char _dpad_77e8a8[24];
unsigned char _dpad_77e900[128];
#endif
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_77e980[340992];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_77f980[335872];
unsigned char _dpad_7d1984[1020];
#endif

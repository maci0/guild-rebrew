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

// FUNCTION: GOLD 0x53efd0
// SIZE: 117
// FUNCTION: GOLDTL 0x546d10
// SIZE: 117

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

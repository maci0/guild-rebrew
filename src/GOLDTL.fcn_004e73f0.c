// FUNCTION: GOLDTL 0x4e73f0
// SIZE: 159
// FUNCTION: GOLD 0x004e58e0
// SIZE: 159

extern int g_7f4c00;
extern char g_68d8a8[];
extern char g_68d870[];
extern char g_68d780[];
extern char* g_14a6544[];
extern char* g_14a6538[];
extern char* g_14a5770[];
extern char* g_14a57e0[];
extern char* g_14a5b54[];

int __cdecl fcn_0064d41a(char*, char*, ...);

void __cdecl fcn_004e73f0(unsigned char* e, char* out)
{
	char* name;

	if (e[2] >= 10)
		name = g_68d870;
	else
		name = g_68d780 + e[2] * 0x18;
	fcn_0064d41a(out, g_68d8a8, g_7f4c00, *(int*) (e + 4), *(unsigned short*) e, name, e + 0x30, e[8],
	    g_14a6544[e[9]], *(unsigned short*) (e + 0xa), g_14a6538[e[0xc]], g_14a5770[e[0xd]], g_14a57e0[e[0x164]],
	    g_14a5b54[e[0x165]]);
}

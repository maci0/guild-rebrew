typedef struct {
	int who;
	unsigned short op;
} fcn_004bbbd0_msg;

typedef int(__cdecl* fcn_004bbbd0_handler)(fcn_004bbbd0_msg*);

extern int g_7f4c00;
extern fcn_004bbbd0_handler g_6811b8[];

char* __cdecl fcn_00508e40(int);

// FUNCTION: GOLD 0x4bb6c0
// SIZE: 96
// FUNCTION: GOLDTL 0x4bbbd0
// SIZE: 95

int __cdecl fcn_004bbbd0(fcn_004bbbd0_msg* m)
{
	char* p;

	if (g_7f4c00 < 8)
		return 0;
	if (m == 0)
		return -1;
	p = fcn_00508e40(m->who);
	if (p == 0 || *(unsigned char*) (p + 0x1b1) > 0)
		return 0x400;
	if (m->op < 0x45)
		return g_6811b8[m->op](m);
	return -2;
}

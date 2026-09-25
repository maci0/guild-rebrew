// FUNCTION: GOLD 0x004c4030
// SIZE: 73
// FUNCTION: GOLDTL 0x4c49a0
// SIZE: 73

extern volatile unsigned int g_6b7fac;
extern char* g_aed324;

void __cdecl fcn_004c3ff0(void);
int __cdecl fcn_004c4940(void);

char* __cdecl fcn_004c49a0(char a1, int a2)
{
	unsigned int end;
	char* p;

	end = g_6b7fac + a2;
	while (g_6b7fac < end) {
		fcn_004c3ff0();
		fcn_004c4940();
		for (p = g_aed324; p != 0; p = *(char**) (p + 0x95)) {
			if (*p == a1) {
				return p;
			}
		}
	}
	return 0;
}

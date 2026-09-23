// GLOBAL: GOLDTL 0x68a9cc
extern char g_68a9cc[];
// GLOBAL: GOLD 0x60bd64
extern char g_68a9cc[];
// FUNCTION: GOLD 0x004c3f20
// SIZE: 37
// FUNCTION: GOLDTL 0x4c4890
// SIZE: 37

void __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_004c4890(void)
{
	char buf[0x7c];

	if (*(unsigned*) g_68a9cc < 4) {
		*(int*) buf = *(unsigned*) g_68a9cc + 1;
		fcn_004c5790(0x12, buf);
	}
}

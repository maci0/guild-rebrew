extern char g_68a9cc[];
// FUNCTION: GOLD 0x004c3f50
// FUNCTION: GOLDTL 0x4c48c0

void __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_004c48c0(void)
{
	char buf[0x7c];

	if (*(unsigned*) g_68a9cc > 0) {
		*(int*) buf = *(unsigned*) g_68a9cc - 1;
		fcn_004c5790(0x12, buf);
	}
}

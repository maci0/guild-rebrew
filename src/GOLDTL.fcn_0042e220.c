extern char* g_6b7fd0;
extern char* g_6b7fd8;

void __cdecl fcn_0041da60(char* a, int b, char* c, int n);

/* ADDRESS: GOLDTL 0x0042e220 */
void __cdecl fcn_0042e220(void)
{
	char* p;

	p = g_6b7fd0;
	while (p > g_6b7fd8) {
		p -= 0x84;
		fcn_0041da60(p + 0x3e, *(int*) (p + 0x70), p + 0xe, 0x400);
	}
}

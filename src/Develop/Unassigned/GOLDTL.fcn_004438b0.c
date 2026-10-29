extern char g_1040640[];

void __cdecl fcn_00452420(char* p);

/* ADDRESS: GOLDTL 0x004438b0 */
char __cdecl fcn_004438b0(char* a, char** b)
{
	char* p;
	char* n;

	*(int*) (a + 0x20c) = (int) b[1];
	p = *(char**) (b[0] + 0xa4);
	while (p != g_1040640) {
		n = *(char**) (p + 0x314);
		if (*(char**) (p + 0x2e4) == a) {
			fcn_00452420(p);
		}
		p = n;
	}
	return 1;
}

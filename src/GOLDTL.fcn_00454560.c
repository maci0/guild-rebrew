extern char g_6b89a4[];
extern char g_6b89a0[];

void __cdecl fcn_0041e2e0(int* pool, void* p);

// FUNCTION: GOLD 0x00457c20
// FUNCTION: GOLDTL 0x454560
void __cdecl fcn_00454560(char** n)
{
	char* p;
	char* nx;
	unsigned int i;

	if (n != 0) {
		p = n[0xf];
		while (p != 0) {
			nx = *(char**) (p + 4);
			fcn_0041e2e0(&(*(int*)g_6b89a4), p);
			p = nx;
		}
		for (i = 0; i < 4; i++) {
			if (n[i] != 0) {
				fcn_00454560((char**) n[i]);
			}
		}
		fcn_0041e2e0(&(*(int*)g_6b89a0), n);
	}
}

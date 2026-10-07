// FUNCTION: GOLD 0x00568d40
// FUNCTION: GOLDTL 0x571100

char* __cdecl fcn_005463a0(int, ...);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_005492e0(char*);

void __cdecl fcn_00571100(char* a)
{
	char* u;

	for (u = fcn_005463a0(1, 0, 0x23); u != 0; u = fcn_005462a0()) {
		if ((u[0x78] & 3) && *(int*) (u + 0xb0) == *(int*) (a + 4)) {
			fcn_005492e0(u);
		}
	}
}

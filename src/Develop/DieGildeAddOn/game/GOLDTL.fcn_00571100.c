


char* __cdecl fcn_005463a0(int, ...);
char* __cdecl he_fn_Handlung(void);
void __cdecl fcn_005492e0(char*);

void __cdecl fcn_00571100(char* a)
{
	char* u;

	for (u = fcn_005463a0(1, 0, 0x23); u != 0; u = he_fn_Handlung()) {
		if ((u[0x78] & 3) && *(int*) (u + 0xb0) == *(int*) (a + 4)) {
			fcn_005492e0(u);
		}
	}
}

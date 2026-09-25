void __cdecl fcn_004c4510(char* p, int id);
void __cdecl fcn_004c4700(int a, int b, int c, int* d);
void __cdecl fcn_004c53a0(void);

// FUNCTION: GOLD 0x00504840
// SIZE: 156
// FUNCTION: GOLDTL 0x00507870
// SIZE: 156
int __cdecl fcn_00507870(char* e)
{
	int v;

	v = 0;
	if (*(char**) (e + 0x16c) != 0 && **(char**) (e + 0x16c) == 0x20) {
		v = 0xc;
	} else if (*(char**) (e + 0x16c) != 0 && **(char**) (e + 0x16c) == 0x1f) {
		v = 0xb;
	} else {
		v = *(unsigned char*) (e + 0x165) - 1;
	}
	fcn_004c4510(e, *(int*) (e + 4));
	fcn_004c4700(1, 1, 0x165, &v);
	fcn_004c53a0();
	v = 0;
	fcn_004c4510(e, *(int*) (e + 4));
	fcn_004c4700(4, 1, 0x174, &v);
	fcn_004c53a0();
	return -1;
}

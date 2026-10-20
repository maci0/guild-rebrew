typedef struct Stat0049c800 {
	int v[9];
} Stat0049c800;

extern void __cdecl fcn_004f4830(int a, Stat0049c800* p);
extern void __cdecl fcn_004a4680(void* a0, void* a1, int a2, int a3, Stat0049c800* p);
extern void __cdecl fcn_004a4410(void* a0, void* a1, int a2, int a3, int a4, int a5, int a6);

/* ADDRESS: GOLDTL 0x0049c800 */

void __cdecl fcn_0049c800(int* a0, int* a1, int a2, int a3, int a4, int a5, int a6)
{
	Stat0049c800 st;

	*a0 = 0;
	*a1 = 0;
	fcn_004f4830(0x13, &st);
	if (st.v[6] != 0) {
		fcn_004a4680(a0, a1, a2, a3, &st);
		return;
	}
	fcn_004a4410(a0, a1, a2, a3, a4, a5, a6);
}

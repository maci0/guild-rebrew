typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

void __cdecl fcn_004f4830(int a, Stat* st);
int __cdecl fcn_004a4680(float* o1, float* o2, int a3, char* e, Stat* st);
int __cdecl fcn_004a4410(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x0049cee0 */
int __cdecl fcn_0049cee0(float* o1, float* o2, int a3, char* e, int skip, int a6, int a7)
{
	Stat st;

	if (skip) {
		*o1 = -1.0e30f;
		*o2 = -1.0e30f;
		return 0;
	}
	*o1 = 0;
	*o2 = 0;
	fcn_004f4830(4, &st);
	if (st.v[6]) {
		return fcn_004a4680(o1, o2, a3, e, &st);
	}
	return fcn_004a4410(o1, o2, a3, e, 0, a6, a7);
}

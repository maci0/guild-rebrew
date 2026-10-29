typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

void __cdecl fcn_004f4830(int a, Stat* st);
int __cdecl fcn_004a4680(float* o1, float* o2, int a3, char* e, Stat* st);
int __cdecl fcn_004a4410(float* o1, float* o2, int a3, char* e, int a5, int a6, char* p);

/* ADDRESS: GOLDTL 0x0049bb00 */
int __cdecl fcn_0049bb00(float* o1, float* o2, int a3, char* e, int a5, int a6, char* p)
{
	Stat st;

	*o1 = 0;
	*o2 = 0;
	if (*(int*) (p + 0x10) < 0x1c || *(int*) (p + 0x10) > 0x22) {
		return 0;
	}
	fcn_004f4830(0x11, &st);
	if (st.v[6]) {
		return fcn_004a4680(o1, o2, a3, e, &st);
	}
	return fcn_004a4410(o1, o2, a3, e, a5, a6, p);
}

typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

void __cdecl fcn_004f4830(int a, Stat* st);
int __cdecl fcn_004a4680(float* o1, float* o2, int a3, char* e, Stat* st);
int __cdecl fcn_004a4410(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLD 0x004995c0 */
/* ADDRESS: GOLDTL 0x00499000 */
int __cdecl fcn_00499000(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7)
{
	Stat st;

	*o1 = 0;
	*o2 = 0;
	fcn_004f4830(0x18, &st);
	if (st.v[6] && (e[2] != 5 || !(e[0x1c8] & 2))) {
		return fcn_004a4680(o1, o2, a3, e, &st);
	}
	return fcn_004a4410(o1, o2, a3, e, a5, a6, a7);
}

typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

void __cdecl fcn_004f4830(int a, Stat* st);
int __cdecl ai_ComputeActionScore(float* o1, float* o2, int a3, char* e, Stat* st);
int __cdecl fcn_004a4410(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLDTL 0x00499000 */
int __cdecl fcn_00499000(float* o1, float* o2, int a3, char* entity, int a5, int a6, int a7)
{
	Stat st;

	*o1 = 0;
	*o2 = 0;
	fcn_004f4830(0x18, &st);
	if (st.v[6] && (entity[2] != 5 || !(entity[0x1c8] & 2))) {
		return ai_ComputeActionScore(o1, o2, a3, entity, &st);
	}
	return fcn_004a4410(o1, o2, a3, entity, a5, a6, a7);
}

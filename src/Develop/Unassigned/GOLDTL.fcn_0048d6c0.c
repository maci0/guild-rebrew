extern char* g_entity_type_table;
extern unsigned char g_773d75;
extern float g_6628bc;

int __cdecl fcn_0048d610(char*, char**);
int __cdecl fcn_005463a0(int, ...);
int __cdecl fcn_0050d170(int);
int __cdecl fcn_0050d200(char*, int);
int __cdecl fcn_0050b810(int, unsigned char);
int __cdecl fcn_004a4bb0(int, char*, int, int*, int*, int);
int __cdecl fcn_0049e900(int, char*, int, int*, int*);

/* ADDRESS: GOLDTL 0x0048d6c0 */
int __cdecl fcn_0048d6c0(int a0, char* a1, int a2, int* a3, int* a4)
{
	int v12[6];
	int v13[6];
	int first;
	int second;
	int rem;
	int i;

	if (!fcn_0048d610(a1, (char**) &a1))
		return 0;
	if (a2 != 0)
		return 0;
	if (a0 != 0x40 && a0 != 0)
		return 0;
	if (fcn_005463a0(2, 0, 0xd, 2, *(unsigned short*) a1) != 0)
		return 0;
	if (a1 != 0) {
		if (*(unsigned char*) (g_entity_type_table + *(unsigned char*) a1 * 0x24d + 0x247) > 2)
			return 0;
		if (a1[0x5a] & 0x41)
			return 0;
		v13[1] = *a1 + 1;
		v13[2] = 1;
		v12[0] = 4;
		v12[1] = *(int*) (a1 + 1);
		v12[2] = 1;
		first = (int) (fcn_0050d170(v13[1]) * 0.3f);
		if (fcn_004a4bb0(a0, a1, 0, v13, v12, 0) == 0)
			return 0;
		second = (int) (fcn_0050b810(*(int*) (a1 + 0x178), g_773d75) * 0.95f);
		if (first <= second) {
			for (i = 0; i < 6; i++) {
				a3[i] = v13[i];
				a4[i] = v12[i];
			}
			return 0x40;
		}
		rem = first - second;
		if ((float) rem / (float) first < g_6628bc) {
			a3[2] = rem;
			*(char*) a3 = 0x12;
			return fcn_0049e900(0x40, a1, 0, a3, a4);
		}
	} else {
		v12[0] = 5;
		v12[1] = 0x4b;
		v12[2] = 1;
		if (fcn_004a4bb0(a0, a1, 0, v12, v13, 1) == 0)
			return 0;
		first = fcn_0050d200(a1, v12[1]);
		second = (int) (fcn_0050b810(*(int*) (a1 + 0x178), g_773d75) * 0.95f);
		if (first <= second) {
			for (i = 0; i < 6; i++) {
				a3[i] = v12[i];
				a4[i] = v13[i];
			}
			return 0x40;
		}
		rem = first - second;
		if ((float) rem / (float) first < g_6628bc) {
			a3[2] = rem;
			*(char*) a3 = 0x12;
			return fcn_0049e900(0x40, a1, 0, a3, a4);
		}
	}
	return 0;
}

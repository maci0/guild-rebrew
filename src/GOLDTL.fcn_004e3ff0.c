unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl fcn_00508e40(int);
int __cdecl gm_AccumulateTyped2(char*);
float __cdecl fcn_004e6d20(void);
unsigned int __cdecl fcn_004e6cb0(int);

/* ADDRESS: GOLD 0x004e26d0 */
/* ADDRESS: GOLDTL 0x004e3ff0 */

void __cdecl fcn_004e3ff0(char* a, int* b)
{
	int i;
	int val;
	int n;
	float fv;
	char* o;

	*(int*) (a + 0x98) = 0;
	for (i = 0; i < b[0x12]; i++) {
		if (b[9 + i] == *(int*) (a + 0x10))
			break;
	}
	if (i >= b[0x12])
		return;
	if (b[i] == -1)
		return;
	*(int*) (a + 0x94) = b[8];
	gm_StartFilteredEntitySearch(1, 1, b[0x11]);
	val = b[8];
	o = fcn_00508e40(*(int*) (a + 0x10));
	if (o == 0)
		return;
	fv = (float) (val + b[0x13] * 32000);
	n = (int) ((fcn_004e6d20() / 6.0f + 0.3f) * gm_AccumulateTyped2(o) < fv
	    ? (fcn_004e6d20() / 6.0f + 0.3f) * gm_AccumulateTyped2(o) : fv);
	if (n < val)
		return;
	if (!(fcn_004e6d20() > (float) val / n))
		return;
	if (n > val * 2)
		n = val * 2;
	n -= val;
	*(int*) (a + 0x98) = 1;
	n = (int) ((float) val + fcn_004e6cb0(n) * (b[0x13] * 0.1f));
	*(int*) (a + 0x94) = n % 32 + n;
}

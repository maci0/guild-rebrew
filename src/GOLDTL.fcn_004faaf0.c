// FUNCTION: GOLD 0x004f8700
// SIZE: 400
// FUNCTION: GOLDTL 0x004faaf0
// SIZE: 400

unsigned short __cdecl fcn_0042e410(int n);
char* __cdecl gm_StartFilteredEntitySearch(int mode, int kind, int type);
char* __cdecl gm_AddObjekt(void);

int __cdecl fcn_004faaf0(char* o)
{
	int types[20];
	int cand[16];
	char* e;
	int k;
	int tries;
	int t;
	int n;

	types[0] = 1;
	types[1] = 2;
	types[2] = 5;
	types[3] = 7;
	types[4] = 10;
	types[5] = 6;
	types[6] = 4;
	types[7] = 19;
	types[8] = 22;
	types[9] = 9;
	types[10] = 15;
	types[11] = 23;
	types[12] = 25;
	types[13] = 26;
	types[14] = 24;
	types[15] = 8;
	types[16] = 14;
	types[17] = 18;
	types[18] = 20;
	types[19] = 21;
	if (o == 0) {
		return -1;
	}
	n = 0;
	tries = 32;
	e = *(char**) (o + 0x16c);
	if (e != 0 && *(int*) (e + 0x61) != 0) {
		cand[n++] = *(int*) (e + 1);
	}
	e = *(char**) (o + 0x170);
	if (e != 0 && *(int*) (e + 0x61) != 0) {
		cand[n++] = *(int*) (e + 1);
	}
	while (n < 16 && tries != 0) {
		tries--;
		t = types[fcn_0042e410(4) * 5 + fcn_0042e410(5)];
		k = 0;
		for (e = gm_StartFilteredEntitySearch(1, 5, t); e != 0 && k < 3; e = gm_AddObjekt()) {
			if (n >= 16) {
				break;
			}
			if (fcn_0042e410(4) < 3) {
				cand[n++] = *(int*) (e + 1);
				k++;
			}
		}
	}
	return cand[fcn_0042e410(n)];
}

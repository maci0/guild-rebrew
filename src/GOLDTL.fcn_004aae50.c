int __cdecl fcn_004e8af0(int, void*);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004e7c70(char*, int, float*);
double __cdecl fcn_0050f980(int, int, int);
int __cdecl fcn_005c6270(void*, int);
unsigned short __cdecl fcn_0042e410(unsigned short);

struct info_4aae50 {
	int pad0[2];
	unsigned char kind;
	char pad9[15];
};
// SIZE 0x18

// FUNCTION: GOLD 0x004aad30
// FUNCTION: GOLDTL 0x4aae50

int __cdecl fcn_004aae50(int a1, unsigned short* a2, int* a3, int* a4)
{
	float score[4];
	char* ents[4];
	struct info_4aae50 info;
	float bonus;
	float best;
	char* e;
	int i;
	int tie;
	int idx;
	int k;

	*a4 = 0;
	if (fcn_004e8af0(a1, &info) == 0)
		return -1;
	for (i = 0; i < 4; i++) {
		e = fcn_00508e40(a3[i]);
		ents[i] = e;
		if (e != 0 && fcn_004e7c70(e, info.kind, &bonus) != 0) {
			score[i] = fcn_0050f980(*(unsigned short*) e, *a2, 1) + bonus;
			if (fcn_005c6270(e, 0x2be) != 0)
				score[i] += 0.2f;
			if ((*(int*) (e + 0x1cc) & 0x400000) != 0)
				score[i] -= 0.2f;
		} else {
			score[i] = -1000.0f;
		}
	}
	best = -206158529088.0;
	tie = 0;
	idx = -1;
	for (i = 0; i < 4; i++) {
		if (ents[i] != 0 && score[i] > best) {
			best = score[i];
			tie = 0;
			idx = i;
		} else if (ents[i] != 0 && score[i] == best) {
			tie = 1;
		}
	}
	if (idx < 0)
		return -1;
	if (tie == 0)
		return *(int*) (ents[idx] + 4);
	idx = -1;
	i = fcn_0042e410(4);
	for (k = 4; k != 0; k--, i = (i + 1) % 4) {
		if (score[i] == best && ents[i] != 0) {
			idx = i;
			break;
		}
	}
	if (idx < 0)
		return -1;
	return *(int*) (ents[idx] + 4);
}

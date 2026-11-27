int __cdecl fcn_00507b00(int);
float __cdecl gm_GetEntitySkill(char*, int);
int __cdecl fcn_004fbd20(int);
int __cdecl gm_SumStraftatSeverity(int);
void __cdecl gm_GetLawEntry(int, char*);
int __cdecl fcn_0042e410(int);

/* ADDRESS: GOLDTL 0x004903c0 */
int __cdecl ai_EvaluateLaw0x00(char* obj, int unused, int* out)
{
	float skill;
	float fA;
	float fC;
	float fB;
	float sum;
	float q;
	int kind;
	int n;
	int e;
	char info[0x24];

	kind = fcn_00507b00((unsigned char) obj[0x164]);
	skill = gm_GetEntitySkill(obj, 4);
	n = fcn_004fbd20(4) & 0xff;
	sum = (skill - ((float) n + *(float*) 0x6628a0) * *(float*) 0x66416c) *
	    *(float*) 0x664168;
	fA = (*(float*) (obj + 0xf4) - *(double*) 0x662a48) * *(float*) (obj + 0xfc);
	fB = (*(float*) (obj + 0x100) - *(double*) 0x662a48) * *(float*) (obj + 0x108);
	fC = (*(float*) (obj + 0x10c) - *(double*) 0x662a48) * *(float*) (obj + 0x114);
	e = gm_SumStraftatSeverity(*(int*) (obj + 4));
	if (kind == 0xb || kind == 0xc) {
		sum += *(float*) 0x664164;
	} else if (kind == 9 || kind == 7) {
		sum += *(float*) 0x662918;
	} else {
		sum += *(float*) 0x662ac8;
	}
	q = (float) e / sum;
	gm_GetLawEntry(0, info);
	if (q > *(float*) 0x6628a0) {
		if (fC > fA && *(int*) (info + 0x18) < 2) {
			*out = (fcn_0042e410(2) & 0xffff) + *(int*) (info + 0x18) + 1;
			return 1;
		}
		if (q > *(float*) 0x662998) {
			*out = 4;
			return 1;
		}
	} else {
		if (fA > fB && *(int*) (info + 0x18) > 2) {
			*out = *(int*) (info + 0x18) - (fcn_0042e410(3) & 0xffff) - 1;
			return 1;
		}
	}
	return 0;
}

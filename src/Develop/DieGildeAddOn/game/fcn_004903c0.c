int __cdecl fcn_00507b00(int);
float __cdecl fcn_00507f10(char*, int);
int __cdecl fcn_004fbd20(int);
int __cdecl fcn_004f5dd0(int);
void __cdecl fcn_004f4830(int, char*);
int __cdecl fcn_0042e410(int);

/* ADDRESS: GOLDTL 0x004903c0 */
int __cdecl fcn_004903c0(char* obj, int unused, int* out)
{
	float t;
	float v10;
	float fB;
	float fC;
	float sum;
	float q;
	int kind;
	int n;
	int e;
	char info[0x24];

	kind = fcn_00507b00((unsigned char) obj[0x164]);
	t = fcn_00507f10(obj, 4);
	n = fcn_004fbd20(4) & 0xff;
	sum = (t - ((float) n + *(float*) 0x6628a0) * *(float*) 0x66416c) *
	    *(float*) 0x664168;
	v10 = (*(float*) (obj + 0xf4) - *(double*) 0x662a48) * *(float*) (obj + 0xfc);
	fB = (*(float*) (obj + 0x100) - *(double*) 0x662a48) * *(float*) (obj + 0x108);
	fC = (*(float*) (obj + 0x10c) - *(double*) 0x662a48) * *(float*) (obj + 0x114);
	e = fcn_004f5dd0(*(int*) (obj + 4));
	if (kind == 0xb || kind == 0xc) {
		sum += *(float*) 0x664164;
	} else if (kind == 9 || kind == 7) {
		sum += *(float*) 0x662918;
	} else {
		sum += *(float*) 0x662ac8;
	}
	q = (float) e / sum;
	fcn_004f4830(0, info);
	if (q > *(float*) 0x6628a0) {
		if (fB > v10 && *(int*) (info + 0x18) < 2) {
			*out = (fcn_0042e410(2) & 0xffff) + *(int*) (info + 0x18) + 1;
			return 1;
		}
		if (q > *(float*) 0x662998) {
			*out = 4;
			return 1;
		}
	} else {
		if (v10 > fC && *(int*) (info + 0x18) > 2) {
			*out = *(int*) (info + 0x1c) - (fcn_0042e410(3) & 0xffff) - 1;
			return 1;
		}
	}
	return 0;
}

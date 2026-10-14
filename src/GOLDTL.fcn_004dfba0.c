extern unsigned short* g_772f24;

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_00493640(int*);
int __cdecl IsRandomSecondChoice(int*);
int __cdecl fcn_004937f0(int*);
int __cdecl fcn_00493800(int*);
void __cdecl fcn_004c54c0(int, int, int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_00493a30(char*, int*);
int __cdecl fcn_00493ce0(char*, int*);

/* ADDRESS: GOLDTL 0x004dfba0 */

void __cdecl fcn_004dfba0(char* a1, int* ev)
{
	char* e;

	*(int*) (a1 + 0x94) = -1;
	switch (ev[0]) {
	case 0:
		if (*(int*) (a1 + 0x10) == ev[6]) {
			e = fcn_00508e40(ev[6]);
			*(float*) (a1 + 0x98) = *(int*) (e + 0x24) + *(float*) (e + 0x1c);
			*(int*) (a1 + 0x94) = fcn_00493640(ev);
		}
		break;
	case 1:
		if (*(int*) (a1 + 0x10) == ev[5])
			*(int*) (a1 + 0x94) = IsRandomSecondChoice(ev);
		break;
	case 2:
		if (*(int*) (a1 + 0x10) == ev[5])
			*(int*) (a1 + 0x94) = fcn_004937f0(ev);
		break;
	case 3:
		if (*(int*) (a1 + 0x10) == ev[10]) {
			*(int*) (a1 + 0x94) = fcn_00493800(ev);
			if (*(int*) (a1 + 0x94) == 1)
				fcn_004c54c0(*(int*) (a1 + 0x10), ev[6], 0x23, 1);
		}
		break;
	case 6:
		if (*(int*) (a1 + 0x10) == ev[6])
			*(int*) (a1 + 0x94) = gm_RandomMod(2);
		break;
	case 4:
		if (*(int*) (a1 + 0x10) == ev[7] || *(int*) (a1 + 0x10) == ev[8] || *(int*) (a1 + 0x10) == ev[9]) {
			e = fcn_00508e40(((int*)g_772f24)[1]);
			*(int*) (a1 + 0x94) = fcn_00493a30(e, ev);
		}
		break;
	case 5:
		if (*(int*) (a1 + 0x10) == ev[7]) {
			e = fcn_00508e40(ev[7]);
			*(int*) (a1 + 0x94) = fcn_00493ce0(e, ev);
		}
		break;
	}
}

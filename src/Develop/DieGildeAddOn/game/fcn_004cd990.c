extern int g_14cbca0;
extern int g_699364;

int __cdecl fcn_004f2350(char*);
int __cdecl fcn_004f25a0(char*);
int __cdecl fcn_004f2880(char*);
int __cdecl fcn_004f2a80(char*);
int __cdecl fcn_004f2c00(char*);
int __cdecl fcn_004f2d90(char*);
int __cdecl fcn_004f2ee0(char*);
int __cdecl fcn_0064d3f8(void);

/* ADDRESS: GOLDTL 0x004cd990 */
int __cdecl fcn_004cd990(char* a1, char* a2)
{
	int r;
	char* p;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	if (*(int*) 0x14cbca0 != -1) {
		*(int*) 0x699364 = *(int*) (a1 + 0x27);
	} else {
		*(int*) (a1 + 0x2b) = fcn_0064d3f8();
	}
	p = a1 + 0x10;
	switch (*(int*) p) {
	case 0:
		r = fcn_004f2350(p);
		break;
	case 1:
		r = fcn_004f25a0(p);
		break;
	case 2:
		r = fcn_004f2880(p);
		break;
	case 3:
		r = fcn_004f2a80(p);
		break;
	case 4:
		r = fcn_004f2c00(p);
		break;
	case 5:
		r = fcn_004f2d90(p);
		break;
	case 6:
		r = fcn_004f2ee0(p);
		break;
	default:
		return -1;
	}
	if (a2 != 0 && r == 0)
		a2[0] = 1;
	return r;
}

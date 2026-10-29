extern int g_7f4ca0;
extern int g_14b5280;
extern int g_aed32c;
extern float flt_665ecc;

char* __cdecl fcn_00508e40(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_0051af00(char*, char*, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
int __cdecl fcn_00567170(char*, int*, int*, int);
int __cdecl fcn_004c5da0(int, int, int, int, int, int);
void __cdecl fcn_004c4510(char*, int);
int __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00546190(char*);
char* __cdecl fcn_0050dc90(int);
char* __cdecl he_RegisterApEvent(int, char*, int, int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl fcn_004c5530(int);

/* Entity event handler: state 0 builds and posts the event message, state -1
 * clears the entity's event flag and frees its track. */
/* ADDRESS: GOLDTL 0x00569760 */
void __cdecl fcn_00569760(char* a0)
{
	float f;
	char* p;
	int n;
	int idx;
	char* e;
	char* rec;
	char* pl;
	struct {
		char msg[0xf4];
		char text[0x200];
	} b;

	if (*(int*) (a0 + 0x70) < -2) {
		return;
	}
	if (*(int*) (a0 + 0x70) < 0) {
		e = fcn_00508e40(*(int*) (a0 + 0xac));
		if (e != 0) {
			e[0x1b1] = 0;
		}
		fcn_00546190(a0);
		return;
	}
	if (*(int*) (a0 + 0x70) != 0) {
		return;
	}
	e = fcn_00508e40(*(int*) (a0 + 0xac));
	rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xb0));
	if (rec == 0 || e == 0) {
		*(int*) (a0 + 0x70) = -1;
		return;
	}
	p = (char*) &g_7f4ca0 + (*(unsigned short*) (rec + 0x27)) * 0x21c;
	if (*(int*) (rec + 0x65) == -1) {
		*(int*) (rec + 0x65) = *(int*) (e + 4);
	}
	if (*(char*) (e + 0x1b1) != 0) {
		pl = fcn_0050dc90((int) rec);
		if ((*(unsigned char*) (a0 + 0x78) & 2) == 0) {
			return;
		}
		he_RegisterApEvent(*(unsigned short*) p, (char*) &g_14b5280, -2, 0);
		fcn_0051af00(b.text, (char*) 0x19c2, a0 + 0xb4);
		fcn_00545d40(*(int*) (e + 4), *(int*) (e + 4), b.text, 0, 0x5f0, 0);
		if (pl == 0) {
			return;
		}
		if ((pl[0x1b4] & 1) == 0) {
			return;
		}
		if (*(unsigned char*) (e + 0x1b1) >= 4) {
			f = 0.1f;
		} else if (*(unsigned char*) (e + 0x1b1) == 3) {
			f = 0.06f;
		} else if (*(unsigned char*) (e + 0x1b1) == 2) {
			f = 0.04f;
		} else if (*(unsigned char*) (e + 0x1b1) == 1) {
			f = 0.02f;
		}
		n = gm_WalkEntityChain(*(unsigned short*) e);
		f = (float) *(int*) &p;
		if (f < flt_665ecc) {
			f = flt_665ecc;
		}
		*(unsigned char*) (b.msg + 0) = 0x3e;
		*(int*) (b.msg + 4) = *(int*) (e + 4);
		*(int*) (b.msg + 8) = *(int*) (rec + 1);
		*(unsigned char*) (b.msg + 0x32) = 9;
		*(int*) (b.msg + 0x54) = *(int*) (e + 4);
		*(int*) (b.msg + 0x5c) = (int) (f * (float) n);
		*(int*) (b.msg + 0x58) = *(int*) ((char*) &g_7f4ca0
		                                  + (*(unsigned short*) (a0 + 8)) * 0x21c + 4);
		fcn_004c5530(idx);
		return;
	}
	rec = (char*) -1;
	if ((*(unsigned char*) (a0 + 0x78) & 2) == 0) {
		fcn_00546190(a0);
		return;
	}
	fcn_0051af00(b.text, (char*) 0x19da);
	fcn_00545d40(*(int*) (e + 4), *(int*) (e + 4), b.text, 0, 0x5fb, 0);
	if (*(int*) (e + 0x184) != 0) {
		if (fcn_00567170(e, &n, (int*) &f, 0) != 0) {
			fcn_004c5da0(*(int*) (e + 4), n, *(int*) &f, 0, 0, (char*) 0x6a69c8);
		}
	}
	fcn_004c4510(rec, *(int*) (rec + 1));
	fcn_004c4570(4, 1, (unsigned short) ((int) rec - g_aed32c + 0x65),
	             (char*) &idx);
	fcn_004c5360();
	fcn_00546190(a0);
}

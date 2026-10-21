extern char* g_aed32c;
extern unsigned short g_774970;

int __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00525f60(char*, int);
float __cdecl fcn_00507f10(char*, int);
void __cdecl fcn_004c4510(char*, int);
int __cdecl fcn_004c4570(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_004c6b20(int, int, int);
int __cdecl fcn_00567170(char*, int*, int*, int*);
int __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
int __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
void __cdecl fcn_00532ef0(void);
float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x005aee90 */
void __cdecl fcn_005aee90(char* rec)
{
	char text[0x400];
	char line[0x400];
	float f;
	int a;
	int b;
	char* ent;
	char* ent2;
	char* act;

	ent = (char*) (0x7f4ca0 + (unsigned int) g_774970 * 540);
	ent2 = (char*) (0x7f4ca0
	    + (unsigned int) *(unsigned short*) (rec + 0x27) * 540);
	fcn_00473a90(0, 0);
	fcn_0051af00(text, 0x3fea, *(unsigned char*) (ent + 0x1b1) * 2);
	if (fcn_00526120(text, 0x11) == 0) {
		goto done;
	}
	if (fcn_00525f60(ent, *(unsigned char*) (ent + 0x1b1) * 2) == 0) {
		goto done;
	}
	f = fcn_00507f10(ent, 4);
	f = fcn_00507f10(ent, 3) + f;
	f = fcn_00507f10(ent, 2) + f;
	f = f * *(float*) 0x6629d0 + *(float*) 0x664328;
	fcn_004c6ae0(*(int*) (ent + 4), -(int) *(unsigned char*) (ent + 0x1b1) * 2);
	if (gm_RandomFloat01() < f) {
		int flags = -1;

		fcn_004c4510(rec, *(int*) (rec + 1));
		fcn_004c4570(4, 1, (int) (rec - g_aed32c) + 0x65, &flags);
		fcn_004c5360();
		fcn_004c6b20(*(int*) (ent + 4), -(int) *(unsigned char*) (ent + 0x1b1), 0);
		if (*(int*) (ent + 0x184) != 0) {
			if (fcn_00567170(ent, &a, &b, 0) != 0) {
				fcn_004c5da0(*(int*) (ent + 4), a, b, 0, 0,
				    (char*) 0x6a69c8);
			}
		}
		act = fcn_005463a0(1, 0, 0x3d);
		while (act != 0) {
			if (*(int*) (act + 0xb0) == *(int*) (rec + 1)
			    && *(int*) (ent + 4) == *(int*) (act + 0xac)) {
				break;
			}
			act = fcn_005462a0();
		}
		if (act != 0) {
			*(int*) (act + 0x84) = fcn_004c5620(-1, act);
		}
		fcn_0051af00(line, 0x3feb);
		fcn_00545d40(*(int*) (ent + 4), -1, line, 0, 0x5f3, 0);
		fcn_0051af00(line, 0x3fed, *(unsigned short*) ent);
		fcn_00545d40(*(int*) (ent2 + 4), -1, line, 0, 0x5f3, 0);
		fcn_00532ef0();
		return;
	}
	fcn_0051af00(text, 0x3fec);
	fcn_00545d40(*(int*) (ent + 4), -1, text, 0, 0x5f3, 0);
	fcn_0051af00(text, 0x3fee, *(unsigned short*) ent);
	fcn_00545d40(*(int*) (ent2 + 4), -1, text, 0, 0x5f3, 0);
done:
	fcn_00532ef0();
}

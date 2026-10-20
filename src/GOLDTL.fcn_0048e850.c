int __cdecl fcn_0048e7f0(char* e, unsigned short** out);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_0050d170(int k);
int __cdecl fcn_0050d200(char* e, int k);
int __cdecl fcn_0050b810(int a, char b);
int __cdecl fcn_004a4bb0(int action, char* e, int a, char* b, char* c, int d);
int __cdecl fcn_0049e900(int a, char* e, int b, char* out1, char* out2);
int __cdecl fcn_0064d228(void);

typedef struct Rec6 {
	int v[6];
} Rec6;

/* ADDRESS: GOLDTL 0x0048e850 */
int __cdecl fcn_0048e850(int action, char* ent, char* opt, char* out1, char* out2)
{
	Rec6 rec1;
	Rec6 rec2;
	int c;
	char* e;
	int need;
	int have;
	int d;

	e = ent;
	if (fcn_0048e7f0(ent, (unsigned short**) &ent) != 0) {
		if (opt == 0 && (action == 0x43 || action == 0)) {
			if (fcn_005463a0(2, 0, 0xd, 2, *(unsigned short*) e) == 0) {
				if (ent != 0) {
					c = (int) *(unsigned char*) ent;
					if ((*(unsigned char*) ((*(char**) 0x868050) + c * 0x24c + c + 0x247)) < 3
						&& (*(unsigned char*) (ent + 0x5a) & 0x41) == 0) {
						*(int*) (rec2.v + 1) = c + 1;
						*(int*) (rec2.v + 2) = 1;
						*(unsigned char*) rec1.v = 4;
						*(int*) (rec1.v + 1) = *(int*) (ent + 1);
						*(int*) (rec1.v + 2) = 1;
						need = (int) ((float) fcn_0050d170(c + 1) * *(float*) 0x66414c);
						if (fcn_004a4bb0(action, e, 0, (char*) (rec2.v + 1), (char*) rec1.v, 0) != 0) {
							have = (int) ((float) fcn_0050b810(*(int*) (e + 0x178), *(char*) 0x773d75) * *(float*) 0x6628cc);
							if (have < need) {
								d = need - have;
								if ((float) d / (float) need < *(float*) 0x6628bc) {
									*(unsigned char*) out1 = 0x12;
									*(int*) (out1 + 8) = d;
									return fcn_0049e900(0x43, e, 0, out1, out2);
								}
							} else {
								*(Rec6*) out1 = rec2;
								*(Rec6*) out2 = rec1;
								return 0x43;
							}
						}
					}
				} else {
					*(unsigned char*) rec1.v = 5;
					*(int*) (rec1.v + 1) = 0x54;
					*(int*) (rec1.v + 2) = 1;
					if (fcn_004a4bb0(action, e, 0, (char*) rec1.v, (char*) rec2.v, 1) != 0) {
						need = fcn_0050d200(e, *(int*) (rec1.v + 1));
						have = (int) ((float) fcn_0050b810(*(int*) (e + 0x178), *(char*) 0x773d75) * *(float*) 0x6628cc);
						if (have < need) {
							d = need - have;
							if ((float) d / (float) need < *(float*) 0x6628bc) {
								*(unsigned char*) out1 = 0x12;
								*(int*) (out1 + 8) = d;
								return fcn_0049e900(0x43, e, 0, out1, out2);
							}
						} else {
							*(Rec6*) out1 = rec1;
							*(Rec6*) out2 = rec2;
							return 0x43;
						}
					}
				}
			}
		}
	}
	return 0;
}

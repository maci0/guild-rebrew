int __cdecl fcn_00503fe0(int, int, int);
char* __cdecl fcn_0050dc90(char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_004c5fa0(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x00563cc0 */
void __cdecl fcn_00563cc0(char* a0)
{
	char buf[0x400];
	char* rec;
	int i;
	char* ent;
	char* p;
	char* e;
	int mode;
	int state;

	state = *(int*) (a0 + 0x70);
	mode = 0x5f6;
	if (state < -2) {
		return;
	}
	if (state >= 0) {
		if (state != 0) {
			return;
		}
		ent = (char*) fcn_00503fe0(1, 1, *(int*) (a0 + 0xac));
		if (ent == 0) {
			fcn_00546190(a0);
			return;
		}
		p = fcn_0050dc90(ent);
		if (p != 0) {
			if (*(unsigned char*) (p + 0x1b4) & 1) {
				mode = 0x60b;
			}
		}
		rec = (char*) (0x7f4ca0 + (unsigned short) (*(unsigned short*) (a0 + 8)) * 0x21c);
		if (*(unsigned char*) (rec + 2) == 6) {
			fcn_0051af00(buf, 0x17e7, ent);
			fcn_00545e80(*(int*) (rec + 4), *(int*) (rec + 4), buf, 0, mode,
				*(int*) (ent + 1), -1, 0, 0x6a65e0);
		}
		if (*(unsigned char*) (rec + 2) == 5 || *(unsigned char*) (rec + 2) == 6) {
			i = 0;
			e = (char*) 0x7f4ca2;
			do {
				int c;

				if ((*e == 6 || *e == 7) && i != *(unsigned short*) rec) {
					c = (int) (*(unsigned char*) ent) * 14 + 0x49c;
					fcn_0051af00(buf, 0x1c32,
						(int) (*(unsigned short*) (a0 + 8)),
						(int) (*(unsigned short*) (a0 + 8)), c);
					fcn_00545e80(*(int*) (e + 2), -1, buf, 0, 0x607,
						*(int*) (ent + 1), -1, 0, 0x6a65cc);
				}
				e += 0x21c;
				i++;
			} while (e < (char*) 0x85a0a2);
		}
		fcn_004c5fa0(*(int*) (ent + 1));
		fcn_004c5420(*(int*) (ent + 1), 0x5a, 2, 0, 0x40);
		fcn_00546190(a0);
	} else {
		char* ne;

		ne = (char*) fcn_00503fe0(1, 1, *(int*) (a0 + 0xac));
		if (ne != 0) {
			fcn_004c5420(*(int*) (ne + 1), 0x5a, 2, 0, 0x40);
		}
		fcn_00546190(a0);
	}
}

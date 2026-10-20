/* Release the client path/mode tables and reset the scene clock state. */

void __cdecl fcn_004e48b0(void);
void __cdecl fcn_00442be0(int);
void __cdecl fcn_004230e0(int);
void __cdecl fcn_0044c440(int);
char* __cdecl fcn_00508e40(int);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_004030e0(int);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004c2d50(void);
void __cdecl fcn_00475220(char*);

/* ADDRESS: GOLDTL 0x004d2a60 */
void __cdecl fcn_004d2a60(int a0)
{
	int i;
	int v;
	char* p;
	int* q;

	fcn_004e48b0();
	if (*(int*) 0x772ea0) {
		fcn_00442be0(*(int*) 0x772ea0);
		*(int*) 0x772ea0 = 0;
	}
	fcn_004230e0(*(int*) 0x772ebc);
	fcn_004230e0(*(int*) 0x772ec0);
	fcn_004230e0(*(int*) 0x772ec4);
	fcn_004230e0(*(int*) 0x772ec8);
	fcn_004230e0(*(int*) 0x772ecc);
	fcn_004230e0(*(int*) 0x772ed0);
	fcn_004230e0(*(int*) 0x772ed4);
	fcn_004230e0(*(int*) 0x772edc);
	fcn_004230e0(*(int*) 0x772ee4);
	fcn_004230e0(*(int*) 0x772eec);
	fcn_004230e0(*(int*) 0x772ef4);
	if (*(int*) 0x772f00 != *(int*) 0x772f04) {
		fcn_004230e0(*(int*) 0x772ed8);
		fcn_004230e0(*(int*) 0x772ee0);
		fcn_004230e0(*(int*) 0x772ee8);
		fcn_004230e0(*(int*) 0x772ef0);
		fcn_004230e0(*(int*) 0x772ef8);
	}
	for (i = 0; i < *(int*) 0x772f08; i++) {
		fcn_00442be0(*(int*) (0x9b9e40 + i * 4));
	}
	if (*(int*) 0x772f0c) {
		fcn_0044c440(*(int*) 0x772f0c);
		*(int*) 0x772f0c = 0;
	}
	q = (int*) 0x9b4bc4;
	do {
		if (*(unsigned short*) ((char*) q - 0x184) != 0xffff && *q) {
			v = *(int*) (a0 + 0xc);
			if (v ==
			        *(int*) ((unsigned short) *(unsigned short*) 0x774970 *
			                     0x21c +
			                 0x7f4ca4) ||
			    *(int*) 0x14cbca0 == -1) {
				p = fcn_00508e40(*(int*) ((char*) q - 0x180));
				if (p[2] != 11) {
					fcn_004ff210(*(unsigned short*) p,
					             *(int*) ((char*) q - 0x160) -
					                 *(int*) (p + 0x24));
				}
			}
			fcn_004030e0(*q);
			*q = 0;
		}
		q = (int*) ((char*) q + 0x21c);
	} while ((int) q < 0x9b8f44);
	*(float*) 0x6a2570 = 1.0f;
	if (*(int*) 0x6b8300) {
		*(int*) 0x6b89c0 = 0;
		*(int*) (0x1043378 + *(int*) 0x6b8010 * 0x3dc) = 0;
	}
	fcn_004e4910();
	fcn_004c2d50();
	*(char*) 0x6a2574 = 1;
	fcn_00475220((char*) 0x6b5c60);
}

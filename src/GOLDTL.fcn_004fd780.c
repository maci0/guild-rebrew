int __cdecl fcn_004f4830(int, void*);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c5480(int, int, float);
void __cdecl fcn_004c4510(void*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004f4f60(int, int, int, int, int);

extern int g_7f4c00;
extern int g_773d48;

/* Per-frame object tick: on every fourth frame, walks the object table and
 * either advances the animation of the visible objects or updates the state of
 * the objects selected by the current filter. */

/* ADDRESS: GOLDTL 0x004fd780 */
void __cdecl fcn_004fd780(void)
{
	char info[0x1c];
	char* p;
	int mode;
	int kind;
	int count;
	int arg;
	float now;

	if ((g_7f4c00 % 4) != 0) {
		return;
	}
	fcn_004f4830(2, info);
	mode = *(int*) (info + 0x18);
	if (mode == 2) {
		p = (char*) 0x7f4ca2;
		g_773d48 = 0;
		do {
			if (*(short*) (p - 2) != -1) {
				kind = p[0];
				if (kind <= 9 && kind != 0 && kind != 6 && kind != 7
					&& kind != 8 && *(unsigned short*) (p + 8) >= 0xc) {
					now = gm_RandomFloat01();
					if (*(float*) (p + 0x1ce) < now * *(float*) 0x6629d0) {
						count = (p[0xa] == 0);
						now = gm_RandomFloat01();
						fcn_004c5480(*(int*) (p + 2), 0x1d0,
							now * *(float*) 0x6628cc + *(float*) 0x6628bc);
						g_773d48++;
						fcn_004c4510(p - 2, *(int*) (p + 2));
						fcn_004c4570(1, 1, 0xc, &count);
						fcn_004c5360();
						g_773d48++;
						if (g_773d48 >= 0x41) {
							fcn_00535960();
							g_773d48 = 0;
						}
					}
				}
			}
			p += 0x21c;
		} while ((int) p < 0x85a0a2);
		g_773d48 = 0;
		return;
	}
	p = (char*) 0x7f4ca2;
	do {
		if (*(short*) (p - 2) != -1) {
			kind = p[0];
			if (kind <= 9 && kind != 0 && kind != 6 && kind != 7 && kind != 8
				&& *(unsigned short*) (p + 8) >= 0xc
				&& (p[0xa] != 0) != (mode != 0)) {
				arg = -1;
				if (*(int*) (p + 0x16e) != 0) {
					arg = *(int*) (*(int*) (p + 0x16e) + 1);
				}
				if (fcn_004f4f60(2, mode == 0, *(int*) (p + 2), -1, arg) != -1) {
					g_773d48++;
				}
				if (*(float*) 0x662a3c < *(float*) (p + 0x1ce)) {
					fcn_004c5480(*(int*) (p + 2), 0x1d0, -0.1f);
				}
				g_773d48++;
				if (g_773d48 >= 0x41) {
					fcn_00535960();
					g_773d48 = 0;
				}
			}
		}
		p += 0x21c;
	} while ((int) p < 0x85a0a2);
	g_773d48 = 0;
}

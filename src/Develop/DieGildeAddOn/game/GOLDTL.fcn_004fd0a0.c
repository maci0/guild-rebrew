/* Per-tick refresh of the visible entity rows: sends the three slot amounts
 * and the averaged fill level, then updates the row's animation values. */

extern int g_773d48;
extern int g_aed32c;
extern double g_6629c8;
extern double g_662908;
extern double g_6640f0;
extern float g_6628a0;

void __cdecl fcn_004fd400(short*, int*);
int __cdecl gm_WalkEntityChain(int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00535960(void);
void __cdecl fcn_004c5480(int, int, float);
void __cdecl fcn_004c47e0(int*);
int __cdecl fcn_004c4820(unsigned char, float);
void __cdecl fcn_004c53e0(void);

/* ADDRESS: GOLDTL 0x004fd0a0 */
void __cdecl fcn_004fd0a0(void)
{
	short flag;
	int n;
	int total;
	int count;
	int v;
	int r;
	int i;
	/* Unaligned 8-byte temp: the native body stores the ratio as a qword at
	 * [esp+0x24] without a /Oy frame, so it cannot be a plain `double` local. */
	float dmem[2];
	float inv;
	float x;
	char* e;

	fcn_004fd400(&flag, &n);
	g_773d48 = 0;
	for (e = (char*) 0x7f4ca0; e < (char*) 0x85a0a0; e += 0x21c) {
		if (g_773d48 > 0x40) {
			fcn_00535960();
			g_773d48 = 0;
		}
		if (*(short*) e == -1) {
			continue;
		}
		if (*(unsigned char*) (e + 2) >= 0xa) {
			continue;
		}
		if (*(unsigned char*) (e + 8) == 0) {
			continue;
		}
		r = gm_WalkEntityChain(*(short*) e);
		total = 0;
		count = 0;
		fcn_004c4510(e, *(int*) (e + 4));
		for (i = 0; i < 3; i++) {
			v = *(int*) (e + 0x1d8 + i * 4);
			total += v;
			if (v != 0) {
				count++;
			}
			fcn_004c4570(4, 1, (int) e + 0x1d4 + i * 4 - g_aed32c, &v);
		}
		count = (r + total) / (count + 1);
		fcn_004c4570(4, 1, (int) e + 0x1e0 - g_aed32c, &r);
		*(double*) dmem = (double) count / (double) r;
		if (g_6629c8 <= *(double*) dmem) {
			*(double*) dmem = 1.0;
		}
		inv = 1.0f - (float) r / (float) n;
		fcn_004c5360();
		x = (float) ((*(double*) dmem + inv) * g_662908);
		fcn_004c5480(*(int*) (e + 4), 0x1e4, x - *(float*) (e + 0x1e4));
		fcn_004c47e0((int*) e);
		fcn_004c4820(3, -(*(float*) (e + 0xb4) - (float) g_6640f0 * *(float*) (e + 0xb4)));
		fcn_004c53e0();
		g_773d48++;
	}
	g_773d48 = 0;
}

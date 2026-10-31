/* Settlement/party interaction step: resolves the current interaction entity,
 * scores the houses around the actor on the 0x90e0a0/0x869480 influence
 * matrices, then raises the script events (0x210..0x218) and the ambient
 * dialogue for the chosen house. */

extern signed char g_90e0a0[];
extern signed char g_869480[];
extern int g_7747b4;
extern char g_7f4ca0[];

int __cdecl fcn_0047d220(void*);
int __cdecl fcn_00508eb0(int, int);
float __cdecl fcn_0050f980(int, int, int);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c4670(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c54c0(int, int, int, int);
void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005b2560(void*, void*);
void* __cdecl fcn_005b2620(void*, void*);
void __cdecl fcn_005b24b0(void*, void*);

/* ADDRESS: GOLDTL 0x0047d2a0 */
int __cdecl fcn_0047d2a0(char* e)
{
	register char* h;
	register char* other;
	int best;
	float bestscore;
	register int i;
	int d;
	float f;
	unsigned char b;
	unsigned char v11;
	signed char flag2;

	if (*(int*) (e + 0x210) != -1) {
		goto other_path;
	}
	if (e[0x166] == 0 && e[0x169] == 0 && e[2] != 5) {
		return 0;
	}
	best = -1;
	bestscore = 128.0f;
	b = 0;
	i = 0;
	for (h = g_7f4ca0 + 2; (int) h < 0x85a0a2; h += 0x21c) {
		if (i != (int) *(unsigned short*) e && h[0] != 6 && h[0] != 7) {
			if (fcn_0047d220(&flag2) == 0 || (h[0x164] == 0 && h[0x167] == 0)) {
				i++;
				continue;
			}
		}
		d = fcn_00508eb0(i, 0) - fcn_00508eb0(*(unsigned short*) e, 0);
		if (d < 0) {
			d = -d;
		}
		f = (10.0f - (float) d * 0.5f) * 0.1f;
		if ((float) (signed char) g_90e0a0[*(unsigned short*) e + i * 0x300] * f
		    < bestscore) {
			if (fcn_0050f980(i, (int) *(unsigned short*) e, 1) < 34.0f) {
				best = i;
				bestscore = (float) (signed char) g_90e0a0[*(unsigned short*) e + i * 0x300]
				            * f;
			}
		}
		i++;
	}
	if (best == -1) {
		return 0;
	}
	if (((signed char) g_869480[*(unsigned short*) e + best * 0x300] / 2
	     + (signed char) g_90e0a0[*(unsigned short*) e + best * 0x300])
	    >= -50 - ((int) fcn_0042e410(0x20) & 0xffff)) {
		return 0;
	}
	b = 0;
	fcn_004c4510((int) e, *(int*) (e + 4));
	fcn_004c4570(1, 1, 0x215, &b);
	b = (unsigned char) ((int) bestscore / 3 + 1);
	if (b >= g_7747b4 + g_7747b4 + 0x23) {
		b = (unsigned char) (g_7747b4 + g_7747b4 + 0x23);
	}
	if (b <= g_7747b4 + g_7747b4 + 0xf) {
		b = (unsigned char) (g_7747b4 + g_7747b4 + 0xf);
	} else if (b >= g_7747b4 + g_7747b4 + 0x23) {
		b = (unsigned char) (g_7747b4 + g_7747b4 + 0x23);
	}
	fcn_004c4570(1, 1, 0x216, &b);
	h = g_7f4ca0 + best * 0x21c;
	fcn_004c4570(4, 1, 0x210, h + 4);
	fcn_004c4570(1, 1, 0x214, &g_90e0a0[*(unsigned short*) e + best * 0x300]);
	fcn_004c5360();
	fcn_004c54c0(*(int*) (h + 4), *(int*) (e + 4), 0, 2);
	fcn_005b2560(e, h);
	return 0;

other_path:
	other = (char*) gm_LookupEntityRecordById(*(int*) (e + 0x210));
	if ((e[0x166] == 0 && e[0x169] == 0 && e[2] != 5) || other == 0) {
		goto reset;
	}
	if (other[0x169] == 0 && other[0x166] == 0 && other[2] != 6
	    && other[2] != 7 && other[2] != 5) {
		goto reset;
	}
	if ((int) (unsigned char) e[0x215] > (int) (unsigned char) e[0x216] + 5) {
		goto reset;
	}
	if ((int) (unsigned char) e[0x215] >= (int) (unsigned char) e[0x216]) {
		goto pulse;
	}
	if ((signed char) g_90e0a0[*(unsigned short*) other * 0x300 + *(unsigned short*) e]
	    + (signed char) e[0x214] > 0) {
		goto pulse2;
	}
	if ((unsigned char) e[0x215] > 3) {
		return 0;
	}
	b = (unsigned char) ((int) fcn_0042e410(2) + 1);
	fcn_004c4510((int) e, *(int*) (e + 4));
	fcn_004c4670(1, 1, 0x215, &b);
	if ((int) (unsigned char) e[0x215] + b > 3) {
		fcn_004c4570(1, 1, 0x218, e + 0x217);
	}
	fcn_004c5360();
	if ((int) (unsigned char) e[0x215] + b <= 3) {
		return 0;
	}
	fcn_005b2620(e, other);
	return (int) other;

pulse:
	b = 1;
	fcn_004c4510((int) e, *(int*) (e + 4));
	fcn_004c4670(1, 1, 0x215, &b);
	b = 1;
	fcn_004c4570(1, 1, 0x218, &b);
	fcn_004c5360();
	return 0;

pulse2:
	b = (unsigned char) (e[0x216] + 1);
	fcn_004c4510((int) e, *(int*) (e + 4));
	fcn_004c4570(1, 1, 0x215, &b);
	b = 1;
	fcn_004c4570(1, 1, 0x218, &b);
	fcn_004c5360();
	return 0;

reset:
	b = 0;
	v11 = 0;
	fcn_004c4510((int) e, *(int*) (e + 4));
	fcn_004c4570(1, 1, 0x215, &b);
	fcn_004c4570(1, 1, 0x216, &b);
	best = -1;
	fcn_004c4570(4, 1, 0x210, &best);
	fcn_004c4570(1, 1, 0x214, &v11);
	b = 1;
	fcn_004c4570(1, 1, 0x218, &b);
	fcn_004c5360();
	if (other != 0) {
		fcn_004c54c0(*(int*) (e + 0x210), *(int*) (e + 4), 0x3c, 2);
		fcn_005b24b0(e, other);
	}
	return 0;
}
unsigned char _dpad_7747b4[76];

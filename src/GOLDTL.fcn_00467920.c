/*
 * Progress bar renderer for one HUD element.
 *
 * Reads the element's bar geometry, derives the fill ratio from the four
 * value fields of the 0x2f4-byte element record and clamps the two bar ends
 * away from the degenerate range. The two sprite handles are fetched before
 * the drawing branches run.
 *
 * Reconstructed range 0x467920..0x4679c6: the element fetch, the sprite handle
 * lookups, the ratio computation and both clamps. The native body continues at
 * 0x4679c6 with the drawing branches through 0x468b7a; that part is not
 * reconstructed here. The native return value leaves ST0.
 */

extern char* g_1015ea0;			/* 0x01015ea0 */
extern float g_6628a8;			/* 0x006628a8 */

char* __cdecl fcn_0047b620(int, int);

/* ADDRESS: GOLDTL 0x00467920 */
void __cdecl fcn_00467920(int a0, int a1)
{
	int* e;
	char* h1;
	char* h0;
	char* h3;
	char* h6;
	int v19;
	int v20;
	int v24;
	int v18;
	unsigned int flags;
	float ratio;
	float end;
	float start;

	e = (int*) (g_1015ea0 + a0 * 0x2f4);
	h1 = fcn_0047b620(e[3], 1);
	h0 = fcn_0047b620(e[3], 0);
	h3 = fcn_0047b620(e[3], 3);
	h6 = fcn_0047b620(e[3], 6);
	v19 = e[0x23];
	v20 = e[0x25];
	flags = (unsigned int) e[0x26];
	v24 = e[0x24];
	v18 = e[0x27];
	if (v20 - v24) {
		ratio = (float) v18 / (float) (v20 - v24);
		end = (float) (v19 - v24) * ratio;
		start = (float) (e[0x28] - v24) * ratio;
	}
	else {
		start = (float) v24;
		end = start;
	}
	if ((g_6628a8 < end) && (end < *(float*) 0x6628a0)) {
		end = 1.0f;
	}
	if ((g_6628a8 < start) && (start < *(float*) 0x6628a0)) {
		start = 1.0f;
	}
}

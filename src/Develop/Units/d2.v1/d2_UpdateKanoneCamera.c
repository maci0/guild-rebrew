#include <math.h>

extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
extern int g_14ce8d0;
extern char g_14cf718;
extern char g_14cf7c8;
extern char g_14cf7cb;
extern char g_14cf7cd;
extern char g_14cf7d0;
extern int d2_ScreenHeight;
extern int g_1040494;
extern float flt_1_0;
extern float flt_0_0;
extern float g_6628bc;
extern float g_662948;

extern float g_662acc;
extern float g_665f14;
extern float g_665f18;
extern float g_665f48;
extern float g_665f4c;
extern float g_665f50;
extern double g_662958;

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* ADDRESS: GOLDTL 0x005875c0 */
/* ADDRESS: GOLDDE 0x0056d280 */
void __cdecl d2_UpdateKanoneCamera(char* o, float dt)
{
	int drow;
	int dcol;
	int v;
	int h;

	v = 0;
	h = 0;
	if (*(int*) (o + 0x7c) != 0)
		return;
	if (g_14cf718 != 0)
		*(float*) (o + 0x20) += dt * 0.8f;
	else
		*(float*) (o + 0x20) -= dt * 1.6f;
	if (*(float*) (o + 0x20) > flt_1_0 || *(float*) (o + 0x20) > flt_0_0)
		*(float*) (o + 0x20) = (*(float*) (o + 0x20) > flt_1_0) ? flt_1_0 : *(float*) (o + 0x20);
	else
		*(float*) (o + 0x20) = flt_0_0;
	if (g_14ce8d0 != 0) {
		if (io_ActiveCursorY < 0x50 || (int) io_ActiveCursorY > d2_ScreenHeight - 0x50) {
			*(int*) (o + 0x88) = 0;
			goto tail;
		}
		if (*(int*) (o + 0x88) == 0) {
			*(int*) (o + 0x80) = (int) io_ActiveCursorX;
			*(int*) (o + 0x84) = (int) io_ActiveCursorY;
			*(int*) (o + 0x88) = 1;
			*(float*) (o + 0x60) = 0;
			*(float*) (o + 0x5c) = 0;
			*(float*) (o + 0x58) = 0;
			*(float*) (o + 0x54) = 0;
			goto tail;
		}
		if (*(int*) (o + 0x88) != 1)
			goto no_track;
		drow = (int) io_ActiveCursorX - *(int*) (o + 0x80);
		*(int*) (o + 0x80) = (int) io_ActiveCursorX;
		dcol = (int) io_ActiveCursorY - *(int*) (o + 0x84);
		*(int*) (o + 0x84) = (int) io_ActiveCursorY;
		*(float*) (o + 0x10) = *(float*) (o + 0x10) - (float) dcol * g_665f4c;
		*(float*) (o + 0x14) = *(float*) (o + 0x14) - (float) drow * g_665f48;
		goto tail;
	}
	if (*(int*) (o + 0x88) != 1)
		goto no_track;
	*(int*) (o + 0x88) = 0;
	goto tail;

no_track:
	if (g_14cf7c8 != 0 || io_ActiveCursorY <= 5)
		v = 1;
	if (g_14cf7d0 != 0 || (int) io_ActiveCursorY >= d2_ScreenHeight - 5)
		v--;
	if (g_14cf7cb != 0 || io_ActiveCursorX <= 5)
		h = 1;
	if (g_14cf7cd != 0 || (int) io_ActiveCursorX >= g_1040494 - 10)
		h--;
	if (*(float*) (o + 0x54) != flt_0_0 || h != 0) {
		if (h == 0) {
			if (*(float*) (o + 0x54) < flt_0_0) {
				*(float*) (o + 0x54) += dt * g_662948;
				if (*(float*) (o + 0x54) >= flt_0_0)
					*(float*) (o + 0x54) = flt_0_0;
			}
			else {
				*(float*) (o + 0x54) -= dt * g_662948;
				if (*(float*) (o + 0x54) <= flt_0_0)
					*(float*) (o + 0x54) = flt_0_0;
			}
		}
		else if (h > 0) {
			if (*(float*) (o + 0x54) < flt_0_0)
				*(float*) (o + 0x54) += dt * g_662948;
			else
				*(float*) (o + 0x54) += dt * g_6628bc;
			*(float*) (o + 0x54) = MIN(*(float*) (o + 0x54), flt_1_0);
		}
		else {
			if (*(float*) (o + 0x54) > flt_0_0)
				*(float*) (o + 0x54) -= dt * g_662948;
			else
				*(float*) (o + 0x54) -= dt * g_6628bc;
			*(float*) (o + 0x54) = *(float*) (o + 0x54) > (-1.0f) ? *(float*) (o + 0x54) : (-1.0f);
		}
		*(float*) (o + 0x5c) = dt * *(float*) (o + 0x54) * 1.5f;
	}
	if (*(float*) (o + 0x58) != flt_0_0 || v != 0) {
		if (v == 0) {
			if (*(float*) (o + 0x58) < flt_0_0) {
				*(float*) (o + 0x58) += dt * g_662948;
				if (*(float*) (o + 0x58) >= flt_0_0)
					*(float*) (o + 0x58) = flt_0_0;
			}
			else {
				*(float*) (o + 0x58) -= dt * g_662948;
				if (*(float*) (o + 0x58) <= flt_0_0)
					*(float*) (o + 0x58) = flt_0_0;
			}
		}
		else if (v > 0) {
			if (*(float*) (o + 0x58) < flt_0_0)
				*(float*) (o + 0x58) += dt * g_662948;
			else
				*(float*) (o + 0x58) += dt * g_6628bc;
			*(float*) (o + 0x58) = MIN(*(float*) (o + 0x58), flt_1_0);
		}
		else {
			if (*(float*) (o + 0x58) > flt_0_0)
				*(float*) (o + 0x58) -= dt * g_662948;
			else
				*(float*) (o + 0x58) -= dt * g_6628bc;
			*(float*) (o + 0x58) = *(float*) (o + 0x58) > (-1.0f) ? *(float*) (o + 0x58) : (-1.0f);
		}
		*(float*) (o + 0x60) = dt * *(float*) (o + 0x58) * g_662948;
	}
	*(float*) (o + 0x10) = *(float*) (o + 0x60) + *(float*) (o + 0x10);
	*(float*) (o + 0x14) = *(float*) (o + 0x5c) + *(float*) (o + 0x14);

tail:
	if (*(float*) (o + 0x10) < g_665f18 || *(float*) (o + 0x10) > g_665f14) {
		*(float*) (o + 0x10) = MIN(MAX(*(float*) (o + 0x10), g_665f18), g_665f14);
		*(float*) (o + 0x58) = 0;
	}
	*(float*) (o + 0x14) = (float) fmod(*(float*) (o + 0x14), g_662958);
}

extern int g_100f888;
#include "Develop/Units/d2.v1/d2_gui.h"
extern char tp_ch_PathGrid[];
extern int g_14ce8e8;
extern char g_14cf7c8;
extern char g_14cf7cb;
extern char g_14cf7cd;
extern char g_14cf7d0;
extern int d2_CurrentElementId;
extern int g_6a99e8;
extern int g_6ab3dc;
extern float g_6ab3e0;
extern volatile int gm_GameTicks;
extern int d2_CurrentWindowId;
extern char* d2_CurrentWindow;
extern unsigned char gm_ActiveTownIndex;
extern int g_778d20;
extern int g_778d24;
extern char gm_EntitySlotTable[];

int __cdecl d2_UpdateWindowDrag(char*);
int __cdecl d2_ScrollMapViewport(char*);
void __cdecl d2_RunPersonDialog(char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
int __cdecl d2_CreateElement(int, int, int);
void __cdecl d2_PositionControl(int, int, int);
void __cdecl d2_DestroyElement(int);
void __cdecl d2_ScrollWindow(int, int, int);
char* __cdecl fcn_0050d490(char*);

/* ADDRESS: GOLDTL 0x005b11f0 */
/* ADDRESS: GOLDDE 0x00595bf0 */
void __cdecl d2_UpdateCityScrollMap(int* state)
{
	char* view;
	char* t;
	char* e;
	char* p;
	float pos[4];
	float x;
	float y;
	float q;
	float qy;
	int i;
	int n;
	int ox;
	int oy;
	int id;
	int sx;
	int sy;
	int* slot;
	int list;
	int obj;
	unsigned short w;
	unsigned char kind;

	view = *(char**) tp_ch_PathGrid;
	ox = *(int*) (gm_ActiveTownIndex * 0x2f4 + 0x86834c);
	oy = *(int*) (gm_ActiveTownIndex * 0x2f4 + 0x868350);
	d2_CurrentWindowId = state[2];
	d2_CurrentWindow = (char*) (state[2] * 0x3cc + 0x1015f40);
	t = d2_CurrentWindow;
	if (g_6ab3dc) {
		state[0x9e7] = 0;
		state[0x9e7] = d2_UpdateWindowDrag((char*) (state[2] * 0x3cc + 0x1015f40));
		state[0x9e7] |= d2_ScrollMapViewport((char*) (state[2] * 0x3cc + 0x1015f40));
		if (state[0x9e7] != 0) {
			state[0x9e8] = gm_GameTicks;
		}
	}
	if (g_100f888 != -1 && (unsigned int) gm_GameTicks > (unsigned int) (state[0x9e8] + 0x4b)
	    && g_14ce8e8 && g_6a99e8 == -1 && state[0x9e9] > 0) {
		n = 0;
		p = (char*) (state + 0x38);
		i = d2_CurrentElementId;
		do {
			if (i != -1 && i == *(int*) (p - 4)) {
				w = *(unsigned short*) (*(int*) p + 0x27);
				if (w != 0xffff
				    && *(unsigned char*) (w * 0x21c + 0x7f4ca2) < 10) {
					d2_RunPersonDialog((char*) (w * 0x21c + 0x7f4ca0));
					i = d2_CurrentElementId;
				}
			}
			n += 1;
			p += 6 * 4;
		} while (n < state[0x9e9]);
	}
	d2_CurrentWindowId = state[2];
	list = 0x14d0020;
	slot = state + 0x637;
	for (;;) {
		obj = *(int*) list;
		if (obj == 0) {
			goto next;
		}
		if (*(int*) (obj + 0x88) != 0x10432c0) {
			goto check;
		}
		e = *(char**) (obj + 0x34);
		d3_TransformPoint(e, e + 0x4c, pos);
		x = (float) (((double) pos[0] - *(float*) t) / *(float*) (t + 0x10)
		    - *(int*) (view + 0x20) * 0.5);
		x = x * g_6ab3e0;
		y = (float) (((double) pos[2] - *(float*) (t + 8)) / *(float*) (t + 0x18)
		    - *(int*) (view + 0x20) * 0.5);
		y = y * g_6ab3e0;
		q = (float) ((double) fabs(x) / (g_778d24 * 0.5f));
		qy = (float) ((double) fabs(y) / (g_778d20 * 0.5f));
		if (x < 0) {
			x = x - q * 51.0f;
		} else {
			x = q * 51.0f + x;
		}
		if (y < 0) {
			y = y - qy * 51.0f;
		} else {
			y = qy * 51.0f + y;
		}
		sy = (int) ((float) (g_778d20 / 2) + (float) oy + y);
		sx = (int) ((float) (g_778d24 / 2) + (float) ox + x);
		if (*slot == -1) {
			e = *(char**) (obj + 0x34);
			if (*(int*) (e + 0x218) == 1 && *(int*) (obj + 0x124) == 0) {
				goto check;
			}
			id = *(int*) (e + 0x204);
			if (id != 0 && *(int*) (obj + 0x124) == 0) {
				if (*(int*) (id + 0x16c) == 0) {
					goto check;
				}
				w = *(unsigned short*) (*(int*) (id + 0x16c) + 0x27);
				if (w == 0xffff) {
					goto check;
				}
				kind = *(unsigned char*) (w * 0x21c + 0x7f4ca2);
				if (kind == 6 || kind == 7 || kind == 5) {
					n = d2_CreateElement(*(int*) (d2_CurrentWindow + 4) + sx, *(int*) (d2_CurrentWindow + 8) + sy,
					    *(int*) (w * 0x21c + 0x7f4cf4) - 0x53);
					*slot = n;
					if (n == -1) {
						goto next;
					}
					*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_left)) = *(int*) (d2_CurrentWindow + 4);
					*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_right)) = *(int*) (d2_CurrentWindow + 0xc) + *(int*) (d2_CurrentWindow + 4);
					*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_top)) = *(int*) (d2_CurrentWindow + 8);
					*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_bottom)) = *(int*) (d2_CurrentWindow + 0x10) + *(int*) (d2_CurrentWindow + 8);
					*(char**) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].value_050)) = (char*) (state[0] * 700 + 0x1038140);
					goto check;
				}
				goto check;
			}
			if (id != 0 && *(int*) (obj + 0x124) != 0) {
				p = fcn_0050d490((char*) id);
				if (p == 0) {
					goto check;
				}
				kind = p[2];
				if (kind != 6 && kind != 7 && kind != 5) {
					goto check;
				}
				n = d2_CreateElement(*(int*) (d2_CurrentWindow + 4) + sx, *(int*) (d2_CurrentWindow + 8) + sy,
				    *(int*) (p + 0x54) - 0x53);
				*slot = n;
				if (n == -1) {
					goto next;
				}
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_left)) = *(int*) (d2_CurrentWindow + 4);
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_right)) = *(int*) (d2_CurrentWindow + 0xc) + *(int*) (d2_CurrentWindow + 4);
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_top)) = *(int*) (d2_CurrentWindow + 8);
				*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_bottom)) = *(int*) (d2_CurrentWindow + 0x10) + *(int*) (d2_CurrentWindow + 8);
				*(char**) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].value_050)) = (char*) (state[0] * 700 + 0x1038140);
			}
		} else {
			e = *(char**) (obj + 0x34);
			if (*(int*) (e + 0x218) == 1 && *(int*) (obj + 0x124) == 0) {
				goto check;
			}
			d2_PositionControl(*(int*) (d2_CurrentWindow + 4) - *(int*) (d2_CurrentWindow + 0x268) + sx,
			    *(int*) (d2_CurrentWindow + 8) - *(int*) (t + 0x258) + sy, *slot);
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_left)) = *(int*) (d2_CurrentWindow + 4);
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_right)) = *(int*) (d2_CurrentWindow + 0xc) + *(int*) (d2_CurrentWindow + 4);
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_top)) = *(int*) (d2_CurrentWindow + 8);
			*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[*slot].clip_bottom)) = *(int*) (d2_CurrentWindow + 0x10) + *(int*) (d2_CurrentWindow + 8);
		}

check:
		if (*slot != -1
		    && (*(int*) (*(int*) (obj + 0x34) + 0x218) == 1
		        || *(int*) (obj + 0x88) != 0x10432c0)
		    && *(int*) (obj + 0x124) == 0) {
			d2_DestroyElement(*slot);
			*slot = -1;
		}
next:
		slot += 1;
		list += 4;
		if (list >= 0x14d0c20) {
			break;
		}
	}
	if (g_14cf7c8) {
		d2_ScrollWindow(0, -4, d2_CurrentWindowId);
		return;
	}
	if (g_14cf7d0) {
		d2_ScrollWindow(0, 4, d2_CurrentWindowId);
		return;
	}
	if (g_14cf7cb) {
		d2_ScrollWindow(-4, 0, d2_CurrentWindowId);
		return;
	}
	if (g_14cf7cd) {
		d2_ScrollWindow(4, 0, d2_CurrentWindowId);
	}
}

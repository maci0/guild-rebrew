/*
 * Move the selected goods from the warehouse for every stock slot that covers
 * the requested amount, refresh the slot display and report the remainder.
 */

#include <stdlib.h>

extern char* g_entity_type_table;    /* 0x00868050 */
extern unsigned short g_774970;      /* 0x00774970 */
#include "GOLDTL.ob_TransportFromLager_gconf.h"
extern float flt_1;                  /* 0x006628a0 */
extern float g_6628a8;               /* 0x006628a8 */
extern double dbl_1_0;               /* 0x006629c8 */

unsigned short* __cdecl fcn_00502cd0(int, int, ...);
void __cdecl fcn_0041d9e0(const char*);
void __cdecl fcn_004c44a0(void);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_00535960(void);
int __cdecl fcn_00471f80(int);
int __cdecl gm_CheckInventoryCapacity(char*, int, int);
int __cdecl fcn_0050e170(int, int, int);
float __cdecl fcn_0050bb50(int, char);
int __cdecl fcn_00526010(void*, int, int);
int __cdecl fcn_0050b750(int, int);
int __cdecl fcn_0057eba0(int, int, int, int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_004c51f0(int, int, int, int, int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl fcn_0051af00(char*, int, int);
void __cdecl fcn_00533a40(char*);
void __cdecl fcn_004234e0(int, char*, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x005ba0e0 */
int __cdecl ob_TransportFromLager(int a0, char* a1, char* a2, int a3, int a4,
                                  float a5, int a6, int a7)
{
	int* p;

	int query;
	char* type;
	int n;
	char buf[0x100];

	query = 0;
	type = 0;
	if (a2) {
		type = g_entity_type_table + (unsigned char)*a2 * 0x24d;
	}
	if (!a4) {
		query = (int)fcn_00502cd0(0, 2, 7, 1, a0);
		if (!query) {
			fcn_0041d9e0((const char*)0x6ac37c);
			return 0;
		}
	}
	fcn_004c44a0();
	{
		int count;
		float v11;
		float countf;
		float prod;
		float scale;
	p = (int*)0x7796e0;
	do {
		if (p[4] != -1 && fcn_00471f80(p[4])) {
			count = fcn_00471f80(p[4]);
			if (!a4) {
				if (query) {
					count = fcn_0050e170(query, *p, count);
				}
			} else {
				count = gm_CheckInventoryCapacity((char*)a4, *p, count);
			}
			if (count > 0) {
				if (a3) {
					if (*type == '\n') {
						v11 = fcn_0050bb50(*p, a6) * *(double*)0x664ef8;
					} else {
						v11 = fcn_0050bb50(*p, a6) * *(float*)(a2 + 0x49);
					}
					if (a7 == 2 || a7 == 4) {
						v11 = fcn_0050bb50(*p, *(char*)(a2 + 0x65));
					}
				} else {
					v11 = 0.0f;
				}
				countf = (float)count;
				prod = countf * v11;
				scale = flt_1 / a5;
				if (fcn_00526010(g_slot_table + g_774970 * 0x21c,
				                 (int)(scale * prod), a6) && p[0xc] >= 0) {
					n = fcn_0050b750(1, a6);
					if (abs((int)(scale * countf * v11 - prod)) < n) {
						a5 = 1.0f;
					}
					if (a7 & 8) {
						if (a4) {
							if (!fcn_0057eba0(0x29, (int)a2, 0, *p)) {
								goto next;
							}
							fcn_0057e880(0x29, (int)a2, 0, *p);
						} else {
							if (!fcn_0057eba0(0x27, (int)a2, 0, *p)) {
								goto next;
							}
							fcn_0057e880(0x27, (int)a2, 0, *p);
						}
					} else if (a7 & 1) {
						if (a4) {
							if (!fcn_0057eba0(0x2a, (int)a2, 0, *p)) {
								goto next;
							}
							fcn_0057e880(0x2a, (int)a2, 0, *p);
						} else {
							if (!fcn_0057eba0(0x25, (int)a2, 0, *p)) {
								goto next;
							}
							fcn_0057e880(0x25, (int)a2, 0, *p);
						}
					}
					fcn_004c51f0(a0, *(int*)(a1 + 2), *p, count, a6,
					             (int)(v11 / a5));
					if (v11 != g_6628a8 && a5 != dbl_1_0) {
						fcn_0051af00(buf, 0xec, (int)(prod * a5 - prod));
						fcn_00533a40(buf);
						fcn_004234e0(0, (char*)0x68aed0, 1, 0x3f, 0x7f, 0, 0);
					}
					d2_SetElementValue(p[4], 0, p[0xc],
					                   fcn_00471f80(p[4]) - count, 0);
				}
			}
		}
next:
		p += 0xe;
	} while ((int)p < 0x7798a0);
	p = (int*)0x778da0;
	do {
		if (p[4] != -1 && fcn_00471f80(p[4])) {
			count = fcn_00471f80(p[4]);
			if (!a4) {
				count = fcn_0050e170(query, *p, count);
			} else {
				count = gm_CheckInventoryCapacity((char*)a4, *p, count);
			}
			if (count > 0) {
				if (a3) {
					v11 = fcn_0050bb50(*p, a6) * *(float*)(a2 + 0x49);
				} else {
					v11 = 0.0f;
				}
				countf = (float)count;
				prod = countf * v11;
				scale = flt_1 / a5;
				if (fcn_00526010(g_slot_table + g_774970 * 0x21c,
				                 (int)(scale * prod), a6) && p[0xc] >= 0) {
					n = fcn_0050b750(1, a6);
					if (abs((int)(scale * countf * v11 - prod)) < n) {
						a5 = 1.0f;
					}
					if (a7 & 8) {
						if (a4) {
							if (!fcn_0057eba0(0x29, (int)a2, 0, *p)) {
								goto next2;
							}
							fcn_0057e880(0x29, (int)a2, 0, *p);
						} else {
							if (!fcn_0057eba0(0x27, (int)a2, 0, *p)) {
								goto next2;
							}
							fcn_0057e880(0x27, (int)a2, 0, *p);
						}
					} else if (a7 & 1) {
						if (a4) {
							if (!fcn_0057eba0(0x2a, (int)a2, 0, *p)) {
								goto next2;
							}
							fcn_0057e880(0x2a, (int)a2, 0, *p);
						} else {
							if (!fcn_0057eba0(0x25, (int)a2, 0, *p)) {
								goto next2;
							}
							fcn_0057e880(0x25, (int)a2, 0, *p);
						}
					}
					fcn_004c51f0(a0, *(int*)(a1 + 2), *p, count, a6,
					             (int)(v11 / a5));
					if (v11 != g_6628a8 && a5 != dbl_1_0) {
						fcn_0051af00(buf, 0xec, (int)(prod * a5 - prod));
						fcn_00533a40(buf);
						fcn_004234e0(0, (char*)0x68aed0, 1, 0x3f, 0x7f, 0, 0);
					}
					d2_SetElementValue(p[4], 0, p[0xc],
					                   fcn_00471f80(p[4]) - count, 0);
				}
			}
		}
next2:
		p += 0xe;
	} while ((int)p < 0x779120);
	}
	fcn_004c44b0();
	while (!fcn_004c44c0()) {
		fcn_00535960();
	}
	return 1;
}

#include "client_data.h"
extern int g_100f888, g_6a99e8, g_14ce8e8, g_6772c4, g_100f1e8, g_100f1ec, g_67d370, g_7725c8;
void __cdecl fcn_00471e30(int); void __cdecl fcn_004125c0(int, int);
int __cdecl fcn_00591190(int);
int __cdecl fcn_00590b80(int);
int __cdecl fcn_005909d0(int);
int __cdecl fcn_005913e0(int);
int __cdecl fcn_00591490(int*);
void __cdecl fcn_004707d0(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x00590670 */
void __cdecl fcn_00590670(void)
{
	unsigned short* p;
	unsigned short* q;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	unsigned char b;

	v4 = 0;
	v6 = 0;
	p = 0;
	v3 = g_100f888;
	v5 = g_6a99e8;
	if ((v3 == -1 && *(int*) 0x6a99ec != -1)
		|| (*(int*) 0x774a24 != 0 && g_14ce8e8 == 0 && v5 != -1)) {
		fcn_00471e30(g_6a99e8);
		g_6a99e8 = -1;
		*(int*) 0x6a99f0 = -1;
		*(int*) 0x6a99ec = -1;
		*(int*) 0x774a24 = 0;
		g_6772c4 = 1;
		fcn_004125c0(g_100f1e8, g_100f1ec);
		v3 = g_100f888;
		v5 = g_6a99e8;
	}
	v7 = 0;
	if (*(int*) &g_7746a4 != 0 && *(int*) 0x774a24 != *(int*) &g_7746a4
		&& g_14ce8e8 != 0) {
		v4 = 0;
		if (*(int*) &g_7746ac == 0) {
			v7 = *(int*) &g_7746a4;
		}
		else {
			v4 = *(unsigned short*) g_7746ac;
			if (v4 == 0) {
				v7 = *(int*) &g_7746a4;
			}
		}
		*(int*) 0x774a24 = *(int*) &g_7746a4;
		*(int*) 0x6a99ec = -1;
	}
	if (v3 != -1 && v3 != *(int*) 0x6a99ec) {
		q = *(unsigned short**) (*(int*) &g_1015ea0 + 0x2f0
			+ g_67d370 * 0x2f4);
		if (q != 0) {
			if ((unsigned int) q >= 0x7f4ca0 && (unsigned int) q <= 0x85a09f) {
				p = q;
				if (*q == 0xffff) {
					p = 0;
				}
			}
			else if ((unsigned int) q >= (unsigned int) *(int*) &lpGebaeudeINST && (unsigned int) q < (unsigned int) (*(int*) &lpGebaeudeINST + 0xa900)) {
				v6 = *(unsigned char*) q;
				if (v6 >= 0x58) {
					v6 = 0;
				}
			}
			else if ((unsigned int) q >= (unsigned int) *(int*) &lpGebaeudePROT && (unsigned int) q < (unsigned int) (*(int*) &lpGebaeudePROT + 0xca78)) {
				v6 = ((int) q - *(int*) &lpGebaeudePROT) / 0x24d;
			}
			else if ((unsigned int) q >= (unsigned int) *(int*) &lpObjekteINST && (unsigned int) q < (unsigned int) (*(int*) &lpObjekteINST + 0x14f218)) {
				v4 = *q;
				if (v4 >= 0x2dc) {
					v4 = 0;
				}
			}
			else if ((unsigned int) q >= (unsigned int) *(int*) &lpObjektePROT && (unsigned int) q < (unsigned int) (*(int*) &lpObjektePROT + 0xb9dc)) {
				v4 = ((int) q - *(int*) &lpObjektePROT) / 0x41;
			}
		}
		else if (0xdf <= v3) {
			if (0x427 <= v3) {
				if (v3 <= 0x47e) {
					v6 = v3 - 0x427;
				}
			}
			else {
				v4 = v3 - 0xdf;
			}
		}
		else if (0x427 <= v3) {
			if (v3 <= 0x47e) {
				v6 = v3 - 0x427;
			}
		}
		*(int*) 0x774a24 = 0;
	}
	if (v4 != 0 || v6 != 0 || v7 != 0 || p != 0) {
		if (v5 != -1) {
			fcn_00471e30(v5);
			v5 = -1;
			g_6a99e8 = -1;
			*(int*) 0x6a99f0 = -1;
			v3 = g_100f888;
		}
		if (v4 != 0) {
			b = *(unsigned char*) (*(int*) &lpObjektePROT + v4 * 0x41);
			if (b != 0x20 && b != 0x17 && b != 0x25 && b != 0x27) {
				v5 = fcn_00591190(v4);
			}
			else {
				v5 = fcn_00590b80(v4);
			}
			v3 = g_100f888;
			g_6a99e8 = v5;
		}
		else if (v6 != 0) {
			v5 = fcn_005909d0(v6);
			v3 = g_100f888;
			g_6a99e8 = v5;
		}
		else if (v7 != 0) {
			v5 = fcn_005913e0(v7);
			v3 = g_100f888;
			g_6a99e8 = v5;
		}
		else if (p != 0) {
			v5 = fcn_00591490((int*) p);
			v3 = g_100f888;
			g_6a99e8 = v5;
		}
		if (v5 == -1) {
			*(int*) 0x6a99ec = -1;
			*(int*) 0x774a24 = 0;
		}
		else {
			*(int*) 0x6a99ec = v3;
			*(int*) 0x6a99f0 = *(int*) (v5 * 700 + (unsigned long)&g_1038144);
			if (g_14ce8e8 != 0) {
				g_6772c4 = 0;
			}
		}
	}
	if (v5 != -1) {
		g_7725c8 = 1;
		*(int*) 0x774a28 = 1;
		fcn_004707d0(v5);
		return;
	}
	if (*(int*) 0x774a28 == 0) {
		return;
	}
	g_7725c8 = 0;
	*(int*) 0x774a28 = 0;
}

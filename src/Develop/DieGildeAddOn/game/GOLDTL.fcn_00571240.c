/*
 * Kugel flight state machine, one step per frame.
 *
 * The handle at self+0xb8 resolves to a map slot; self+0x27 of that object
 * gives the slot index and 0x7f4ca0 + index * 0x21c is the map entry, unless
 * it is the current-entry pointer at 0x773da8.
 *
 * State word at self+0x70: negative unlinks the instance, 0 arms state 1,
 * 1 lets the ball start and sets the flight counters, 2 waits until both
 * counters have drained and then restarts. The two counters at self+0x14 and
 * self+0x18 weight the travel time; the ball position at self+0xb0 is summed
 * until it turns positive, and a negative socket test repeats the loop.
 */

#include "client_types.h"

void __cdecl gm_ResolveEntityById(void*, void*, int, int);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_0050c710(char*, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
double __cdecl fcn_0050fdb0(int, int, char*);
int __cdecl fcn_0050c830(char*, char*, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
int __cdecl fcn_00500cb0(char*, char*);
void __cdecl fcn_00500bb0(char*, int, int, int);
void __cdecl fcn_004c51f0(int, int, int, int, int, int);

extern char g_7f4ca0[];
extern char g_7f4c00[];
extern char* g_773da8;
extern unsigned char g_773d75;
extern char* lpObjektePROT;
extern double g_6640e8;
extern double g_6629c8;
extern double g_662908;
extern double g_662ad8;

/* ADDRESS: GOLDTL 0x00571240 */
void __cdecl fcn_00571240(char* self)
{
	char* node;
	float total;
	float prev;
	char* o1;
	char* o2;
	char buf[0x100];
	char* map;
	char* entry;
	char* row;
	char* q;
	int i;
	int n;

	map = 0;
	gm_ResolveEntityById(&node, 0, 0, *(int*) (self + 0xb8));
	if (node == 0) {
		for (i = 0; i < 768; i++) {
			if (*(char**) (g_7f4ca0 + i * 0x21c + 0x17c) == self)
				fcn_00529160(0, 0, *(unsigned short*) (g_7f4ca0 + i * 0x21c), 0);
		}
		fcn_00546190(self);
		return;
	}
	if (*(unsigned short*) (node + 0x27) != 0xffff) {
		row = g_7f4ca0 + *(unsigned short*) (node + 0x27) * 0x21c;
		if (row != g_773da8)
			map = row;
	}
	switch (*(int*) (self + 0x70)) {
	case -2:
	case -1:
		for (i = 0; i < 768; i++) {
			if (*(char**) (g_7f4ca0 + i * 0x21c + 0x17c) == self)
				fcn_00529160(0, 0, *(unsigned short*) (g_7f4ca0 + i * 0x21c), 0);
		}
		fcn_00546190(self);
		return;
	case 0:
		*(int*) (self + 0x70) += 1;
		return;
	case 1:
		if (*(int*) (self + 0x14) == 0 && *(int*) (self + 0x18) == 0) {
			*(int*) (self + 0x70) = 2;
			return;
		}
		gm_ResolveEntityById(&node, 0, 0, *(int*) (self + 0xb8));
		total = fcn_0050c710(node, 1, 1) * g_6640e8 + g_6629c8;
		if (*(unsigned char*) (self + 0xc8) >= 0x3c) {
			if (map != 0) {
				for (i = 0; i < 8; i++) {
					if (((int*) (self + 0x8c))[i] != -1 && *(int*) (node + 0x41) != 2)
						fcn_004c54c0(*(int*) (map + 4), ((int*) (self + 0x8c))[i],
							2 - *(int*) (node + 0x41), 0);
				}
				*(float*) (self + 0xc4) = (float) ((fcn_0050fdb0(*(unsigned short*) map, 8, self + 0x8c)
					- g_662908) * g_662ad8);
			}
			*(unsigned char*) (self + 0xc8) = 0;
		}
		n = fcn_0050c830(self + 0x60, g_7f4c00, 0);
		if (n > 0)
			*(unsigned char*) (self + 0xc8) += n;
		total = total + *(float*) (self + 0xc4);
		if (fcn_00500cb0(self + 0x52, g_7f4c00) >= 0)
			return;
		do {
			entry = lpObjektePROT + *(unsigned short*) (self + 0xac) * 0x41;
			prev = (float) *(int*) (self + 0xb0);
			n = fcn_0050c830(self + 0x60, self + 0x52, 0)
				* (*(int*) (self + 0x18) + *(int*) (self + 0x14) * 2);
			*(int*) (self + 0xb0) = (int) (prev - n * total);
			while (*(int*) (self + 0xb0) <= 0) {
				gm_ResolveEntityById(0, &o1, 0, *(int*) (self + 0xbc));
				q = fcn_00502cd0(*(int*) (o1 + 0x14), 1, 0, *(unsigned short*) (self + 0xac));
				gm_ResolveEntityById(0, &o2, 0, *(int*) (self + 0xc0));
				if (q == 0) {
					io_FormatTextBuffer(buf, 0x1bb7, *(unsigned short*) (self + 0xac) * 2 + 0x9a8, node);
					he_MessageBoxQuickjump(*(int*) (g_7f4ca0 + *(unsigned short*) (self + 8) * 0x21c + 4),
						-1, buf, 0, 0x5f1, *(int*) (node + 1), -1, 0, "_NACHRICHTEN_HS_07");
					for (i = 0; i < 768; i++) {
						if (*(char**) (g_7f4ca0 + i * 0x21c + 0x17c) == self)
							fcn_00529160(node, 0, *(unsigned short*) (g_7f4ca0 + i * 0x21c), 0);
					}
					fcn_00546190(self);
					return;
				}
				n = *(unsigned short*) (entry + 0x36);
				if (n >= *(int*) (q + 0xe))
					n = *(int*) (q + 0xe);
				fcn_004c51f0(*(int*) (self + 0xc0), *(int*) (self + 0xbc), *(unsigned short*) (self + 0xac),
					n, g_773d75, 0);
				*(int*) (self + 0xb0) += *(int*) (entry + 0x22);
				*(float*) (self + 0xb4) = (float) *(int*) (self + 0xb0);
			}
			*(pos14_7f4c00*) (self + 0x60) = *(pos14_7f4c00*) (self + 0x52);
			fcn_00500bb0(self + 0x52, 0, 0, 5);
		} while (fcn_00500cb0(self + 0x52, g_7f4c00) < 0);
		return;
	case 2:
		if (*(int*) (self + 0x14) > 0 || *(int*) (self + 0x18) > 0) {
			*(int*) (self + 0x70) = 1;
			return;
		}
		gm_ResolveEntityById(&node, 0, 0, *(int*) (self + 0xb8));
		if (node == 0) {
			*(int*) (self + 0x70) = -1;
			return;
		}
		for (i = 0; i < 768; i++) {
			if (*(char**) (g_7f4ca0 + i * 0x21c + 0x17c) == self)
				fcn_00529160(node, 0, *(unsigned short*) (g_7f4ca0 + i * 0x21c), 0);
		}
		fcn_00546190(self);
		return;
	}
}

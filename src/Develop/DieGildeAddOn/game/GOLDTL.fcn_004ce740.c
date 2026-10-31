#include "client_packet_builder.h"
/* Owned (both targets) by src/GOLDTL.fcn_004cef70.c. */
extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004ce6e0(void*);

void __cdecl fcn_004c4670(int, int, int, char*);
void __cdecl fcn_004c5360(void);
void* __cdecl fcn_004ce610(void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);


/* ADDRESS: GOLDTL 0x004ce740 */
char __cdecl fcn_004ce740(char* a1)
{
	char buf[0x800];
	char c;
	signed char c0;
	unsigned short idx;
	void* e;
	void* q;
	char* p;
	int r;

	c = 1;
	if (a1 == 0) {
		return 0;
	}
	if ((*(int*) (a1 + 0x1c8) & 0x20000000) == 0) {
		return 0;
	}
	c0 = *(signed char*) (a1 + 0x1c5);
	if (gm_RandomMod(10) < (unsigned short) (unsigned char) c0) {
		c = -c0;
		fcn_004ce6e0(a1);
		fcn_004c4510(a1, *(int*) (a1 + 4));
		fcn_004c4670(1, 1, a1 - g_aed32c + 0x1c5, &c);
		fcn_004c5360();
		e = *(void**) (a1 + 0x16c);
		if (e != 0) {
			idx = *(unsigned short*) ((char*) e + 0x27);
			if (idx != 0xffff) {
				p = g_7f4ca0 + idx * 540;
				if (*(char*) (p + 2) == 6 || *(char*) (p + 2) == 7) {
					q = fcn_004ce610(a1);
					r = *(int*) q;
					if (r != 0) {
						io_FormatTextBuffer(buf, 0x1bca, r * 2 + 0x9a8,
						    *(unsigned short*) a1, *(int*) (a1 + 0x16c));
						fcn_00545d40(*(int*) (p + 4), -1, buf, 0, 0x5f2, 0);
					}
				}
			}
		}
		return 1;
	}
	fcn_004c4510(a1, *(int*) (a1 + 4));
	fcn_004c4670(1, 1, a1 - g_aed32c + 0x1c5, &c);
	fcn_004c5360();
	fcn_004c5420(*(int*) (a1 + 4), 0x1c8, 4, 0, 0x20000000);
	return 0;
}

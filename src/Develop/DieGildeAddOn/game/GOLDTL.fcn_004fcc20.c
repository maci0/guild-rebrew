#include <stdlib.h>

extern int g_773d48;
extern unsigned char g_773d75;
extern unsigned char* lpGebaeudePROT;

char* __cdecl fcn_00507ab0(int a);
int __cdecl fcn_004f4830(int idx, void* dst);
int __cdecl fcn_0050b750(int a, unsigned char b);
void __cdecl fcn_00535960(void);
int __cdecl gm_AccumulateTyped2(char* rec);
void __cdecl fcn_004c54c0(int a1, int a2, int a3, int a4);
float __cdecl fcn_004ff210(int a, int b);
void __cdecl fcn_004c51a0(int a1, int a2, char a3, int a4);

/* ADDRESS: GOLDTL 0x004fcc20 */
void __cdecl fcn_004fcc20(void)
{
	int handle;
	char buf[0x24];
	int i;
	int n;
	int r;
	char* rec;
	char* e;

	handle = (int) fcn_00507ab0(1);
	fcn_004f4830(5, buf);
	n = fcn_0050b750(0xe - *(int*) (buf + 0x18), g_773d75);
	i = 0;
	g_773d48 = 0;
	rec = (char*) 0x7f4ca0;
	do {
		if (g_773d48 > 0x40) {
			fcn_00535960();
			g_773d48 = 0;
		}
		if (*(unsigned short*) rec != 0xffff && *(unsigned char*) (rec + 8) != 0 && *(unsigned char*) (rec + 2) == 0 && *(int*) (rec + 0x170) != 0) {
			e = (char*) (lpGebaeudePROT + *(unsigned char*) *(int*) (rec + 0x170) * 0x24d);
			r = gm_AccumulateTyped2(rec);
			if (r < 0) {
				int obj;

				obj = *(int*) (rec + 0x16c);
				if (*(int*) (rec + 0x16c) == 0 && *(int*) (rec + 0x5c) == -1) {
					r = abs(r);
					if (r > n * 2) {
						fcn_004ff210(i, 0xffffec78);
						goto inc;
					}
				}
				if (obj != 0) {
					fcn_004c54c0(*(int*) (*(unsigned short*) (obj + 0x27) * 0x21c + 0x7f4ca4),
					    *(int*) (rec + 4), -0xa, 1);
					g_773d48++;
				}
			}
			if (*e == 1) {
				fcn_004c51a0(*(int*) (handle + 2), *(int*) (rec + 4), 0, n);
			inc:
				g_773d48++;
			}
		}
		rec += 0x21c;
		i++;
	} while ((int) rec < 0x85a0a0);
	g_773d48 = 0;
}

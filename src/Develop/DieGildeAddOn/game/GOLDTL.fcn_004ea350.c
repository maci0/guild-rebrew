#include "client_types.h"

extern Rec18_68da68 g_9a9220[42];
extern char g_7f4ca0[];

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004e81a0(unsigned char);
int __cdecl fcn_004e8240(unsigned char, char*, char*, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00535960(void);

/* ADDRESS: GOLDTL 0x004ea350 */
void __cdecl fcn_004ea350(void)
{
	unsigned char* r;
	char* p;
	char* e;
	int res;
	int v;
	int n;

	for (r = &g_9a9220[0].x10; (int) r < (int) &g_9a9220[30].x10; r += 0x18) {
		e = fcn_00508e40(*(int*) (r - 0xc));
		res = -1;
		if (e != 0 && *(unsigned char*) (e + 8) != 0) {
			if (*r != 1) {
				res = fcn_004e8240(*(unsigned char*) (r - 0x10), e, 0, 1, 0xff);
			}
		} else {
			if (*r != 3) {
				res = fcn_004e81a0(*(unsigned char*) (r - 0x10));
			}
			if (e != 0 && *(unsigned char*) (e + 0x166) != 0) {
				n = *(int*) (e + 4);
				v = 0;
				fcn_004c4510(e, n);
				fcn_004c4570(1, 1, 0x166, &v);
				fcn_004c5360();
			}
		}
		if (res != -1) {
			while (1) {
				if (fcn_004c4450(res) != 0) {
					break;
				}
				fcn_00535960();
			}
		}
	}
	for (p = g_7f4ca0 + 0x168; (int) p < (int) (g_7f4ca0 + 0x168 + 0x65400); p += 0x21c) {
		if (*(unsigned char*) p != 0) {
			v = 0;
			fcn_004c4510(p - 0x168, *(int*) (p - 0x164));
			fcn_004c4570(1, 1, 0x168, &v);
			fcn_004c5360();
		}
	}
}

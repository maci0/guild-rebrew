extern char* g_868050;
extern unsigned char g_773d75;
extern float g_664174;

char* __cdecl fcn_004be320(char*, int);
char* __cdecl fcn_00504e70(int);
int __cdecl fcn_0050cce0(char*, unsigned short*, int);
char* __cdecl fcn_0050d490(char*);
int __cdecl fcn_0050de80(char*, void*);
char* __cdecl fcn_00503d10(int);
void* __cdecl fcn_00502cd0(int, int, int, int, ...);
int __cdecl fcn_0050df70(char*, char*);
int __cdecl fcn_0050e000(char*, int, int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0064d228(void);
int __cdecl fcn_0050d320(char*, char);
int __cdecl fcn_004c51f0(int, int, short, int, char, int);

/* ADDRESS: GOLDTL 0x004c0240 */
void __cdecl fcn_004c0240(char* a0, int a1)
{
	char* rec;
	char* pkt;
	char* q;
	char* v4;
	char* v5;
	char* v6;
	int n;
	int cnt;
	int v7;
	int c;
	char buf[180];
	char stats[180];

	if (*(int*) (a0 + 0x29) == 0) {
		return;
	}
	rec = fcn_004be320(*(char**) (a0 + 0x29), *(int*) (a0 + 0x2d));
	pkt = fcn_00504e70(*(int*) (rec + 4));
	if (pkt == 0) {
		return;
	}
	q = g_868050 + (*(unsigned char*) pkt) * 0x24d;
	if ((*q != 0xa && *q != 0x1c) && fcn_0050cce0(pkt, (unsigned short*) buf, 0) == 0) {
		return;
	}
	v4 = fcn_0050d490(a0);
	if (fcn_0050de80(a0, stats) == 0) {
		return;
	}
	rec += 0x20;
	cnt = 3;
	do {
		if (*(int*) rec != 0) {
			if (*q == 0xa) {
				v5 = fcn_00503d10(*(int*) rec);
			} else if (*q == 0x1c) {
				v5 = fcn_00502cd0(*(int*) (pkt + 0x5d), 2, 0, 0x1db, 6);
			} else {
				/* Native reads an unwritten local slot on this path. */
				v5 = 0;
			}
			v6 = fcn_00502cd0(*(int*) (buf + 0x10), 1, 0, *(int*) rec);
			if (v6 != 0) {
				n = *(int*) (rec + 4);
				if (!(n < fcn_0050df70(buf, v6))) {
					n = fcn_0050df70(buf, v6);
				}
				c = fcn_0050e000(v5, *(int*) rec, n);
				if (c > 0) {
					v7 = 0;
					if (*(unsigned short*) (pkt + 0x27) != *(unsigned short*) v4) {
						if (*q == 0xa) {
							fcn_0050bb50(*(unsigned short*) v6, g_773d75);
						} else {
							fcn_0050bb50(*(unsigned short*) v6, g_773d75);
						}
						v7 = fcn_0064d228();
					}
					if (v7 * c <= fcn_0050d320((char*) v4, (char) a1)) {
						fcn_004c51f0(*(int*) (v5 + 2), *(int*) (buf + 2),
							*(int*) rec, c, (char) a1, v7);
					}
				}
			}
		}
		rec += 8;
		cnt--;
	} while (cnt != 0);
}

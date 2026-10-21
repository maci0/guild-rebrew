typedef struct Slots {
	int v[0x2d];
	char* obj;
} Slots;
// SIZE 0xb8

extern unsigned char* g_868050;
extern unsigned char g_773d75;
extern float g_664174;

int* __cdecl fcn_004be320(int, int);
char* __cdecl fcn_00504e70(int);
int __cdecl fcn_0050cce0(char*, Slots*, int);
char* __cdecl fcn_0050d490(char*);
int __cdecl fcn_0050de80(char*, Slots*);
char* __cdecl fcn_00503d10(int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_0050df70(char*, char*);
int __cdecl fcn_0050e000(char*, int, int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0050d320(char*, int);
int __cdecl fcn_004c51f0(int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x004c0240 */
void __cdecl fcn_004c0240(char* a0, int a1)
{
	char* rec;
	char* t;
	char* v4;
	char* pkt;
	char* src;
	char* v6;
	int n;
	int c;
	int cnt;
	int val;
	Slots buf;
	Slots stats;

	if (*(int*) (a0 + 0x29) == 0) {
		return;
	}
	rec = (char*) fcn_004be320(*(int*) (a0 + 0x29), *(int*) (a0 + 0x2d));
	pkt = fcn_00504e70(*(int*) (rec + 4));
	if (pkt == 0) {
		return;
	}
	t = (char*) g_868050 + (*(unsigned char*) pkt) * 0x24d;
	if ((*t != 0xa && *t != 0x1c) && fcn_0050cce0(pkt, &buf, 0) == 0) {
		return;
	}
	v4 = fcn_0050d490(a0);
	if (fcn_0050de80(a0, &stats) == 0) {
		return;
	}
	rec += 0x20;
	for (cnt = 3; cnt != 0; cnt--) {
		if (*(int*) rec != 0) {
			if (*t == 0xa) {
				src = fcn_00503d10(*(int*) rec);
			} else if (*t == 0x1c) {
				src = fcn_00502cd0(*(int*) (pkt + 0x5d), 2, 0, 0x1db, 6);
			} else {
				src = buf.obj;
			}
			v6 = fcn_00502cd0(*(int*) (stats.obj + 0x14), 1, 0, *(int*) rec);
			if (v6 != 0) {
				n = *(int*) (rec + 4);
				if (!(n < fcn_0050df70(stats.obj, v6))) {
					n = fcn_0050df70(stats.obj, v6);
				}
				c = fcn_0050e000(src, *(int*) rec, n);
				if (c > 0) {
					val = 0;
					if (*(unsigned short*) (pkt + 0x27) != *(unsigned short*) v4) {
						if (*t == 0xa) {
							val = (int) (fcn_0050bb50(*(unsigned short*) v6, g_773d75) *
								     g_664174);
						} else {
							val = (int) (fcn_0050bb50(*(unsigned short*) v6, g_773d75) *
								     *(float*) (pkt + 0x49));
						}
					}
					if (fcn_0050d320(v4, a1) >= val * c) {
						fcn_004c51f0(*(int*) (src + 2), *(int*) (stats.obj + 2),
							     *(int*) rec, c, a1, val);
					}
				}
			}
		}
		rec += 8;
	}
}

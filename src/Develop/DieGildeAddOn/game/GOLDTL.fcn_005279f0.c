#include <string.h>

typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect47bf;

typedef struct {
	char pad0[0x18];
	int* items;
} fcn_0047cba0_set;

extern int g_6b8010;
extern int g_6a2be4;
extern int g_1040494;
extern char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern unsigned char g_773d75;
extern char g_868060[];
extern char* g_7746cc;
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_774718;
extern char* g_77471c;
extern int g_774714;
extern char* g_774684;
extern char* g_774680;
extern unsigned short g_774970;
extern unsigned char g_7f4e51[];
extern int g_14ce8d8;
extern int g_77250c;
extern int g_772568;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_7ea380[15];
extern char g_6a24ec[45];
extern char* g_14a79c0[];

void __cdecl fcn_0046b2b0(int id);
void __cdecl fcn_00527540(void);
int __cdecl fcn_00465950(const char* name);
void* __cdecl fcn_00466190(int idx);
int __cdecl fcn_0047cba0(int x, int y, int a3, fcn_0047cba0_set* s,
	int idx);
void* __cdecl fcn_0047bf80(int x, int y, int w, int h, int tex,
	Rect47bf* src);
int __cdecl fcn_00475fd0(void* s);
void __cdecl fcn_00476a50(int x, int y, void* s, unsigned char* dst);
int __cdecl fcn_00475780(char* a1, char* a2);
int __cdecl fcn_00476060(void* o);
unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0057eba0(int a, int b, int c, int d);
int __cdecl fcn_00506380(int a, int b, void* c, int d);
void __cdecl fcn_005a7320(int n, int v);
void __cdecl fcn_00475220(char* a);
void __cdecl fcn_00526920(int a, int b, int c);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strupr(char*);

/* ADDRESS: GOLDTL 0x005279f0 */
void __cdecl fcn_005279f0(unsigned int a0)
{
	int v9;
	int v6;
	int v7;
	int x;
	int y;
	int id;
	char key[4];
	Rect47bf r;
	char name[128];
	char path[128];
	unsigned short* v8;
	short* e;
	char* p;
	char* q;
	char* s;
	char* d;
	char c;

	if (g_6b8010 != g_6a2be4 || g_7746cc != g_77471c
		|| g_7746c4 != g_774718 || g_774714 != 0) {
		g_774718 = g_7746c4;
		g_77471c = g_7746cc;
		p = (char*) 0x7ea380;
		do {
			if (*(int*) p != -1) {
				fcn_0046b2b0(*(int*) p);
				*(int*) p = -1;
			}
			p += 4;
		} while ((int) p < (int) 0x7ea3bc);
		if (g_7746c4 || g_7746c8)
			fcn_00527540();
		g_6a2be4 = g_6b8010;
	}
	if (!g_7746c4 && !g_7746c8) {
		s = g_868060 + (unsigned int) g_773d75 * 0x2f4;
		d = name;
		do {
			c = *s;
			*d = c;
			s++;
			d++;
		} while (c);
		strupr(name);
		sprintf(path, "_STADTWAPPEN_%s", name);
		v6 = fcn_00465950(path);
		if (v6 == -1)
			v6 = fcn_00465950("_STADTWAPPEN_BERLIN");
		fcn_0047cba0(g_1040494 - 0x6e, 0x5b, g_77250c,
			(fcn_0047cba0_set*) fcn_00466190(v6), g_772568 + 1);
		goto done;
	}
	if (g_774684) {
		r.left = 0;
		r.top = 0;
		r.right = *(int*) (g_774684 + 0x54);
		r.bottom = *(int*) (g_774684 + 0x58);
		fcn_0047bf80(g_1040494 - 0x6e, 0x5b, 0x68, 0x6e,
			*(int*) (g_774684 + 0x20), &r);
	}
	if (!(a0 & 0x2000))
		goto done;
	x = (*(short*) &g_14ce8c0 - g_1040494) + 0x72;
	y = *(short*) &g_14ce8c2 - 0x59;
	if (!g_774680)
		goto done;
	if (x < 0)
		goto done;
	if (*(int*) (g_774680 + 4) <= x)
		goto done;
	if (y < 0)
		goto done;
	if (*(int*) (g_774680 + 8) <= y)
		goto done;
	fcn_00475fd0(g_774680);
	fcn_00476a50(x, y, g_774680, (unsigned char*) key);
	v6 = 0;
	q = (char*) 0x6a24ec;
	do {
		if (!fcn_00475780(key, q))
			break;
		q += 3;
		v6++;
	} while ((int) q < (int) 0x6a2519);
	fcn_00476060(g_774680);
	if (v6 >= 0xf)
		goto done;
	if (g_7746c4) {
		v9 = 0;
		if (*(char*) (lpGebaeudePROT
			+ (unsigned char) *g_7746c4 * 0x24d) == 2) {
			v8 = fcn_00502cd0(*(int*) (g_7746c4 + 0x5d),
				1, 4, 2);
			while (v8) {
				if (*v8 != 0xfd) {
					if (v9 == v6)
						break;
					v9++;
				}
				v8 = (unsigned short*) gm_NextEntityQueryMatch();
			}
		} else {
			v7 = 0;
			e = (short*) (lpGebaeudePROT
				+ (unsigned char) *g_7746c4 * 0x24d + 0x23);
			do {
				if (*e != (short) 0xffff) {
					id = *e & 0x7fff;
					c = *(char*) (lpObjektePROT + id * 0x41);
					if ((c == 2 || c == 6)
						&& id != 0xfd) {
						if (v9 == v6) {
							v8 = fcn_00502cd0(
								*(int*) (g_7746c4 + 0x5d),
								1, 0, id);
							break;
						}
						v9++;
					}
				}
				v7++;
				e++;
			} while (v7 < 0x40);
		}
		if (g_14ce8d8) {
			if (!v8)
				goto label_527db2;
			if (*v8 != *(short*) g_7746cc
				&& fcn_0057eba0(0x19, (int) g_7746c4, 0,
					(int) *v8) == 1
				&& g_7f4e51[g_774970 * 0x21c] == 0) {
				if (fcn_00506380(g_774970,
					(int) g_7746c4, v8, 0) & 0x4000)
					fcn_005a7320(-1, (int) *v8);
				goto label_527db2;
			}
		}
		if (v8)
			fcn_00475220(g_14a79c0[(unsigned short) *v8 * 2]);
	}
label_527db2:
	if (!g_7746c8)
		goto done;
	v7 = 0;
	v8 = 0;
	v9 = 0;
	e = (short*) (lpGebaeudePROT + (unsigned char) *g_7746c8 * 0x24d + 0x23);
	do {
		if (*e != (short) 0xffff) {
			id = *e & 0x7fff;
			c = *(char*) (lpObjektePROT + id * 0x41);
			if ((c == 2 || c == 6) && id != 0xfd) {
				if (v9 == v6) {
					v8 = fcn_00502cd0(
						*(int*) (g_7746c8 + 0x5d),
						1, 0, id);
					break;
				}
				v9++;
			}
		}
		v7++;
		e++;
	} while (v7 < 0x40);
	if (g_14ce8d8) {
		if (!v8)
			goto done;
		if ((!g_7746cc || *v8 != *(short*) g_7746cc)
			&& fcn_0057eba0(0x19, (int) g_7746c8, 0,
				(int) *v8) == 1
			&& g_7f4e51[g_774970 * 0x21c] == 0) {
			if (!(fcn_00506380(g_774970,
				(int) g_7746c8, v8, 0) & 0x4000))
				goto done;
			fcn_00526920((int) g_7746c8,
				*(int*) ((char*) v8 + 2), 0x6b5c60);
			goto done;
		}
	}
	if (v8)
		fcn_00475220(g_14a79c0[(unsigned short) *v8 * 2]);
done:
	g_774714 = 0;
}
unsigned char _dpad_773de8[2200];
unsigned char _dpad_7f4cc0[401] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
unsigned char _dpad_14a579c[8740];
unsigned char _dpad_14a79c0[17000];

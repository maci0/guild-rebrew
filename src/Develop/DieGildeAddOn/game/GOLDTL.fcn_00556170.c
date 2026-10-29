#include <math.h>

extern float g_6628a8;
extern int lpGebaeudeINST;
extern int lpGebaeudePROT;
extern unsigned char g_773d75;
extern char g_7f4c00[];

void __cdecl fcn_00546190(char*);
int __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
float __cdecl fcn_004fc460(char*);
float __cdecl fcn_0042e450(void);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_004c4fc0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
void __cdecl fcn_004c6000(int, int);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004fac80(int, int*);
float __cdecl fcn_004ff210(unsigned short, int);

typedef struct {
	int a;
	int b;
	int c;
	short d;
} UIPos;

#define COPY_UI(q) \
	*(UIPos*) ((q) + 0x52) = *(UIPos*) ((char*) g_7f4c00)

/* ADDRESS: GOLDTL 0x00556170 */
void __cdecl fcn_00556170(char* p)
{
	float ts[0xa];
	char* ent;
	char* obj;
	int found;
	int n;
	int i;
	int key;
	int type;
	int state;
	int v38;
	int v34;
	unsigned short v;
	float f;

	state = *(int*) (p + 0x70);
	if (state == -1 || state == -2) {
		fcn_00546190(p);
		return;
	}
	if (*(unsigned char*) (p + 0x78) & 4) {
		return;
	}
	switch (state) {
	case 0:
		*(int*) (p + 0xb4) = 0;
		*(int*) (p + 0xac) = 0;
		*(float*) (p + 0xb0) = *(float*) (p + 0xb0) * g_6628a8;
		fcn_00500bb0(p + 0x52, 0, 0, 5);
		*(int*) (p + 0x84) = fcn_004c5620(1, p);
		return;
	case 1:
		fcn_004fc460((char*) ts);
		f = (float) (((int*) ts)[8] - ((int*) ts)[4]) / (float) ((int*) ts)[8];
		*(float*) (p + 0xb0) = 1.0f - f;
		*(float*) (p + 0xb4) = f / (float) (*(int*) (p + 0xac) + 2);
		fcn_00500bb0(p + 0x52, 1, 0, 0);
		if (ts[3] < 0.1) {
			*(float*) (p + 0xb0) = (2.0f - ts[9]) * *(float*) (p + 0xb0);
			*(int*) (p + 0x84) = fcn_004c5620(2, p);
			return;
		}
		if (0.3 < ts[3]) {
			*(float*) (p + 0xb0) = (float) fabs((ts[9] + 1.0f) * *(float*) (p + 0xb0));
			*(float*) (p + 0xb4) = (float) fabs(*(float*) (p + 0xb4));
			*(int*) (p + 0x84) = fcn_004c5620(6, p);
			return;
		}
		COPY_UI(p);
		*(short*) (p + 0x56) = 0xf;
		goto anim7;
	case 2:
		if (*(unsigned short*) ((char*) g_7f4c00 + 4) < 0x14) {
			f = fcn_0042e450();
			if (f <= *(float*) (p + 0xb0)) {
				*(float*) (p + 0xb0) -= *(float*) (p + 0xb4);
				COPY_UI(p);
				fcn_00500bb0(p + 0x52, 1, 0, 0);
				*(int*) (p + 0x84) = fcn_004c5620(2, p);
				return;
			}
			*(int*) (p + 0xb8) = -1;
			i = fcn_0042e410(0xc);
			*(int*) (p + 0xb8) = fcn_004c4fc0(0xff, -1, -1, i + 0xf, -1, 0, 0, 2);
			COPY_UI(p);
			fcn_00500bb0(p + 0x52, 0, 0, 1);
			*(int*) (p + 0x84) = fcn_004c5620(3, p);
			return;
		}
		COPY_UI(p);
		break;
	case 3:
		if (fcn_004c4450(*(int*) (p + 0xb8)) == 0) {
			COPY_UI(p);
			fcn_00500bb0(p + 0x52, 0, 0, 1);
			*(int*) (p + 0x84) = fcn_004c5620(3, p);
			return;
		}
		if (fcn_004c4450(*(int*) (p + 0xb8)) == 2) {
			fcn_00500bb0(p + 0x52, 1, 0, 0);
			*(int*) (p + 0xb8) = -1;
			*(int*) (p + 0x84) = fcn_004c5620(6, p);
			return;
		}
		obj = fcn_004c4480(*(int*) (p + 0xb8));
		v34 = fcn_0042e410(2) & 0xffff;
		v38 = 0;
		if (obj == 0) {
			fcn_00500bb0(p + 0x52, 1, 0, 0);
			*(int*) (p + 0xb8) = -1;
			*(int*) (p + 0x84) = fcn_004c5620(6, p);
			return;
		}
		found = 0;
		n = 0x100;
		v = (unsigned short) fcn_0042e410(0x100);
		do {
			ent = (char*) (lpGebaeudeINST + v * 0xa9);
			type = *(unsigned char*) ent;
			if (*(char*) (lpGebaeudePROT + type * 0x24d) == 1 &&
			    fcn_004fac80(type, &i) != 0 &&
			    *(unsigned char*) (ent + 0x65) < (unsigned short) i) {
				found = 1;
			}
			n--;
			v = (unsigned short) ((v + 1) & 0xff);
		} while (found == 0 && n != 0);
		fcn_004c6000(*(int*) (obj + 4), *(int*) (ent + 1));
		i = fcn_0042e410(0x32);
		key = *(int*) (obj + 4);
		fcn_004c51a0(key, -1, g_773d75, ((i & 0xffff) + 0x33) * 0x20);
		fcn_004c4510(obj, key);
		fcn_004c4570(1, 1, 2, &v38);
		fcn_004c4570(1, 1, 0xc, &v34);
		fcn_004c5360();
		COPY_UI(p);
		fcn_00500bb0(p + 0x52, 1, 0, 0);
		*(int*) (p + 0xac) += 1;
		*(int*) (p + 0x84) = fcn_004c5620(1, p);
		return;
	case 6:
		if (*(unsigned short*) ((char*) g_7f4c00 + 4) < 0x14) {
			f = fcn_0042e450();
			if (f <= *(float*) (p + 0xb0)) {
				*(float*) (p + 0xb0) -= *(float*) (p + 0xb4);
				COPY_UI(p);
				fcn_00500bb0(p + 0x52, 1, 0, 0);
				*(int*) (p + 0x84) = fcn_004c5620(6, p);
				return;
			}
			v = (unsigned short) fcn_0042e410(0x300);
			n = 0x300;
			do {
				key = v * 0x21c;
				if (*(short*) (key + 0x7f4ca0) != -1 &&
				    *(char*) (key + 0x7f4ca8) != 0 &&
				    *(char*) (key + 0x7f4ca2) == 0 &&
				    *(int*) (key + 0x7f4e0c) == 0) {
					fcn_004ff210(v, -2000);
					*(int*) (p + 0xac) += 1;
					break;
				}
				n--;
				v = (unsigned short) ((v + 1) % 0x300);
			} while (n != 0);
			*(int*) (p + 0xb8) = -1;
			COPY_UI(p);
			fcn_00500bb0(p + 0x52, 0, 0x1e, 0);
			*(int*) (p + 0x84) = fcn_004c5620(1, p);
			return;
		}
		COPY_UI(p);
		break;
	case 7:
		v = (unsigned short) fcn_0042e410(0x300);
		n = 0x300;
		for (;;) {
			key = v * 0x21c;
			if (*(short*) (key + 0x7f4ca0) != -1 &&
			    *(char*) (key + 0x7f4ca8) != 0 &&
			    ((*(char*) (key + 0x7f4ca2) == 0 &&
			      *(int*) (key + 0x7f4e10) == 0) ||
			     (*(char*) (key + 0x7f4ca2) == 1 &&
			      *(int*) (key + 0x7f4e10) == 0))) {
				found = 0;
				i = 0x100;
				v34 = fcn_0042e410(0x100) & 0xff;
				for (;;) {
					ent = (char*) (lpGebaeudeINST + v34 * 0xa9);
					type = *(unsigned char*) ent;
					if (*(char*) (lpGebaeudePROT + type * 0x24d) == 1 &&
					    fcn_004fac80(type, &v38) != 0 &&
					    *(unsigned char*) (ent + 0x65) < (unsigned short) v38) {
						found = 1;
					}
					i--;
					v34 = (v34 + 1) & 0xff;
					if (found != 0) {
						break;
					}
					if (i == 0) {
						break;
					}
				}
				if (found != 0) {
					fcn_004c6000(*(int*) (key + 0x7f4ca4), *(int*) (ent + 1));
				}
				break;
			}
			n--;
			if (n == 0) {
				break;
			}
			v = (unsigned short) ((v + 1) % 0x300);
		}
		fcn_00500bb0(p + 0x52, 0, 10, 0);
		if (*(unsigned short*) (p + 0x56) > 0x15) {
			COPY_UI(p);
			*(int*) (p + 0x58) = 0;
			*(int*) (p + 0x52) += 1;
			*(short*) (p + 0x56) = 6;
			goto anim7;
		}
		if (*(unsigned short*) (p + 0x56) < 0xf) {
			COPY_UI(p);
			*(int*) (p + 0x58) += 1;
			goto anim7;
		}
		break;
	default:
		return;
	}
	*(int*) (p + 0x58) += 1;
anim7:
	*(int*) (p + 0x84) = fcn_004c5620(7, p);
}

static int filler_556170(char *e)
{
	return *(int *)(e + 4);
}

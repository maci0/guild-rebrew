#include <string.h>

extern unsigned int* g_1015ea0;
extern int g_772514;

typedef struct Req_59ecc0 {
	int f00;                    /* 0x00 */
	unsigned char kind;         /* 0x04 */
	unsigned char pad05[3];
	int f08;                    /* 0x08 */
	int f0c;                    /* 0x0c */
	unsigned int list[6];       /* 0x10 */
	int f28;                    /* 0x28 */
	int f2c;                    /* 0x2c */
	int f30;                    /* 0x30 */
	unsigned short f34;         /* 0x34 */
	unsigned char f36;          /* 0x36 */
	unsigned char pad37[0x21];
	unsigned char f58;          /* 0x58 */
	unsigned char pad59;
	unsigned short f5a;         /* 0x5a */
	unsigned char pad5c[4];
	int f60;                    /* 0x60 */
	unsigned char pad64[0x94];
} Req_59ecc0;

int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_00525fb0(int);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00533dc0(int, int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_00594340(void);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00595e20(int, int);
void __cdecl fcn_005963f0(int, int, int, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_0052ae70(void);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x0059ecc0 */
void __cdecl fcn_0059ecc0(int a0, int a1)
{
	int i;
	int h;
	int x;
	int sel;
	int cnt;
	char* p;
	unsigned int ids[7];
	int y;
	int total;
	int handles[3];
	Req_59ecc0 req;
	char text[256];

	ids[0] = 0x1c1;
	ids[1] = 0x1c2;
	ids[2] = 0x1c3;
	ids[6] = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, 0x2a);
	if (fcn_00525fb0(a0))
		return;
	ids[3] = 0;
	ids[4] = 0;
	ids[5] = 0;
	h = fcn_005463a0(2, 0, 0x15, 3, *(int*) (a0 + 1));
	while (h) {
		i = 0;
		do {
			if (*(unsigned short*) (h + 0xae) == ids[i]) {
				ids[i + 3] += *(unsigned char*) (h + 0xac);
				break;
			}
			i++;
		} while (i < 3);
		h = he_fn_Handlung();
	}
	total = fcn_00470820(0, 0, (char*) 0x6a9750);
	fcn_00471b60(total);
	d2_SetForm(total, 0);
	fcn_00533dc0(*(int*) 0x772514, 0x70f, 0x741);
	d2_SetForm(total, 3);
	fcn_00519190(0x1806);
	fcn_0052a0c0(a0, 0);
	fcn_00594340();
	fcn_00471b60(total);
	d2_SetForm(total, 2);
	y = *(int*) (0x1015f4c + *(int*) 0x772514 * 0x3cc) / 2 - 0x80;
	cnt = 0;
	for (x = 0x19; x < 0x109; x += 0x50) {
		h = fcn_0046f740(y, x, (int) ids[cnt] + 0xdf, *(int*) 0x772514);
		g_1015ea0[h * 0xbd + 0x17] = 1;
		g_1015ea0[h * 0xbd + 0x74] = 3;
		g_1015ea0[h * 0xbd + 0x77] = 100;
		g_1015ea0[h * 0xbd + 0x78] = 0x10;
		g_1015ea0[h * 0xbd + 0x21] = 0x54;
		fcn_0046f9b0(h, *(int*) (0x14a79c0 + (int) ids[cnt] * 8));
		handles[cnt] = h;
		fcn_00472640(h, 1);
		cnt++;
	}
	fcn_00473a90(0, 0);
	fcn_00595e20(a0, ids[6]);
	fcn_005963f0(total, 1, 0, a0);
	sel = fcn_005373e0(0x59ecc0, 0x677c7);
	while (sel) {
		fcn_00595e20(a0, ids[6]);
		fcn_005963f0(total, 1, 0, a0);
		ids[3] = 0;
		ids[4] = 0;
		ids[5] = 0;
		h = fcn_005463a0(2, 0, 0x15, 3, *(int*) (a0 + 1));
		while (h) {
			i = 0;
			do {
				if (*(unsigned short*) (h + 0xae) == ids[i]) {
					ids[i + 3] += *(unsigned char*) (h + 0xac);
					break;
				}
				i++;
			} while (i < 3);
			h = he_fn_Handlung();
		}
		d2_SetForm(total, 2);
		for (i = 0; i < 3; i++) {
			fcn_00472640(handles[i], 1);
			if (ids[i + 3] == 1) {
				fcn_0051af00(text, 0x1807, 1);
			}
			else if (ids[i + 3] > 1) {
				fcn_0051af00(text, 0x1808, ids[i + 3]);
			}
			else {
				fcn_0051af00(text, 0x679060,
					(int) ids[i] * 2 + 0x9a8);
			}
			fcn_0046f9b0(handles[i], text);
		}
		if (*(int*) 0x100f1dc != -1) {
			for (sel = 0; sel < 3; sel++) {
				if (handles[sel] == *(int*) 0x67d370)
					break;
			}
			if (sel != -1) {
				memset(&req, 0, 0xf8);
				req.kind = 0x15;
				req.f36 = 1;
				req.f08 = *(int*) (*(unsigned short*) (a0 + 0x27) * 0x21c
					+ 0x7f4ca4);
				req.f0c = *(int*) (a0 + 1);
				req.f28 = *(int*) 0x7f4c00;
				req.f2c = *(int*) 0x7f4c04;
				req.f30 = *(int*) 0x7f4c08;
				req.f34 = *(unsigned short*) 0x7f4c0c;
				req.f5a = (unsigned short) ids[sel];
				req.f60 = *(int*) (a1 + 2);
				cnt = 0;
				p = (char*) 0x7f4ca4;
				do {
					if (cnt >= 6)
						break;
					if (p[0x184] != 0) {
						req.list[cnt] = *(unsigned int*) p;
						cnt++;
					}
					p += 0x21c;
				} while ((int) p < 0x85a0a4);
				memset(&req.list[cnt], -1, (6 - cnt) * 4);
				req.f58 = (unsigned char) cnt;
				if (cnt == 0) {
					fcn_00526120(*(int*) 0x14ab324, 4);
				}
				else {
					fcn_004c35f0();
					fcn_0052ae70();
					sel = fcn_004c5530(&req);
					while (!fcn_004c4450(sel)) {
						fcn_005373e0(0, 0x20007);
					}
					fcn_004c4480(sel);
				}
				continue;
			}
		}
		if (*(int*) 0x14ce8e0 != 0)
			*(int*) 0x774654 = 1;
		sel = fcn_005373e0(0x59ecc0, 0x677c7);
	}
	fcn_0052ae70();
	fcn_0052a2d0();
	fcn_00471e30(total);
	return fcn_00532ef0();
}

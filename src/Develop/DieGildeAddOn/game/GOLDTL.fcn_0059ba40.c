#include <string.h>

extern int g_772514;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_100f884;
extern int g_67d370;
extern int g_7746cc;
extern int g_774654;
extern int g_14ce8e0;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;

int __cdecl fcn_00525fb0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int);
void __cdecl fcn_00594340(void);
void __cdecl fcn_00533dc0(int, int, int);
int __cdecl fcn_00472830(int, int, int, int*, int*, int*);
void __cdecl fcn_00533f40(int, int, int, int);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl fcn_004c35f0(void);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_00532ef0(void);
int __cdecl gm_GetMsgField(int, int);
void __cdecl fcn_0046f940(int, char*);
void __cdecl fcn_00595330(int, int, int, int, int);
void __cdecl fcn_00595e20(char*, int);
void __cdecl fcn_005963f0(int, int, int, char*);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
char* __cdecl itoa(int, char*, int);

typedef struct {
	int kind;
	char flag4;
	char pad5[3];
	int f8;
	int f12;
	int f16;
	int f20;
	char pad24[0x10];
	int c28;
	int c2c;
	int c30;
	unsigned short c34;
	char flag36;
	char pad37[0x21];
	unsigned short id;
	char pad5a[0xa];
	int f68;
	int f6c;
	int f70;
	char pad74[0x88];
} Req_59ba40;

/* ADDRESS: GOLDTL 0x0059ba40 */
int __cdecl fcn_0059ba40(char* a0)
{
	Req_59ba40 req;
	char buf[4];
	int v15;
	int v16;
	int item;
	int count;
	int any;
	int r;
	int h;
	int q;
	int t;
	int found;
	int i;
	int k;
	int m;
	int* p;
	int* acc;
	char* row;

	if (fcn_00525fb0((int) a0))
		return 0;
	h = fcn_00470820(0, 0, "Handel\\Handel_PRODUKTION");
	fcn_00471b60(h);
	fcn_0052a0c0(a0, 0);
	d2_SetForm(h, 3);
	io_AppendText(0xca);
	fcn_00594340();
	count = 0;
	d2_SetForm(h, 0);
	p = (int*) (0x10162e8 + g_772514 * 0x3cc);
	p[0] = 0xe;
	p[1] = 0xe;
	p[2] = 0xe;
	p[3] = 0xe;
	fcn_00533dc0(g_772514, 0x70b, 0x742);
	fcn_00533f40(0x270, 0x15e, g_772514, fcn_00472830(h, 2, 0x78, &v16, &v15, &item));
	*(unsigned int*) (g_1015ea0 + 0x84 + item * 0x2f4) = 0x54;
	do {
		d2_SetForm(h, 2);
		t = fcn_00502cd0(*(unsigned int*) (a0 + 0x5d), 2, 6, 0, 0xff);
		if (!t)
			return 0;
		q = fcn_00502cd0(*(unsigned int*) (a0 + 0x5d), 1, 0, 0xfe);
		if (!q)
			return 0;
		r = fcn_00502cd0(*(unsigned int*) (a0 + 0x5d), 2, 6, 0, 0x2a);
		if (!r)
			return 0;
		if ((g_100f1dc != -1) && (g_100f884 == h)) {
			any = 0;
			p = (int*) 0x7e30e0;
			do {
				if ((int) p >= 0x7e35e0)
					break;
				if (p[-4] == 0xffff)
					break;
				if (*p)
					any = 1;
				p += 10;
			} while (!any);
			if (count > 0) {
				for (k = 0; k < count; k++) {
					if (g_67d370 == *(int*) (0x779194 + k * 0x58)) {
						if (!any) {
							p = (int*) 0x7e30d0;
							do {
								if (*p == 0xffff)
									break;
								row = *(char**) (*p * 0x21c + 0x7f4e1c);
								if (row && (*row == 3) && (*(int*) (row + 0x10) == *(int*) (a0 + 1)) && (*(unsigned short*) (row + 0xac) == *(unsigned int*) (0x779160 + k * 0x58)))
									*(char*) (*p * 0x21c + 0x7f4e28) = 1;
								p += 10;
							} while ((int) p < 0x7e35d0);
						} else {
							fcn_004c35f0();
							found = fcn_005463a0(2, 0, 3, 3, *(unsigned int*) (a0 + 1));
							while (found) {
								if (*(unsigned short*) (found + 0xac) == *(unsigned int*) (0x779160 + k * 0x58))
									goto located;
								found = he_fn_Handlung();
							}
							memset(&req, 0, sizeof(req));
							req.flag4 = 3;
							req.f16 = 0;
							req.f20 = 0;
							req.flag36 = 1;
							req.f8 = *(unsigned int*) (*(unsigned short*) (a0 + 0x27) * 0x21c + 0x7f4ca4);
							req.f12 = *(unsigned int*) (a0 + 1);
							req.c28 = g_7f4c00;
							req.c2c = g_7f4c04;
							req.c30 = g_7f4c08;
							req.c34 = g_7f4c0c;
							req.id = *(unsigned short*) (0x779160 + k * 0x58);
							req.f68 = *(unsigned int*) (a0 + 1);
							req.f6c = *(unsigned int*) (q + 2);
							req.f70 = *(unsigned int*) (r + 2);
							m = fcn_004c5530(&req);
							while (!fcn_004c4450(m))
								fcn_005373e0(0, 0x20007);
							found = fcn_004c4480(m);
located:
							p = (int*) 0x7e30d0;
							do {
								if (*p == 0xffff)
									break;
								if (p[4]) {
									fcn_00529160(a0, g_7746cc, *p, found);
									*(char*) (*p * 0x21c + 0x7f4e28) = 0;
								}
								p += 10;
							} while ((int) p < 0x7e35d0);
							if (!*(int*) (found + 0x70))
								*(int*) (found + 0x70) = 1;
						}
					}
				}
			}
		}
		if (g_14ce8e0) {
			any = 0;
			p = (int*) 0x7e30e0;
			do {
				if ((int) p >= 0x7e35e0)
					break;
				if (p[-4] == 0xffff)
					break;
				if (*p)
					any = 1;
				p += 10;
			} while (!any);
			if (any) {
				p = (int*) 0x7e30d0;
				do {
					if (*p == 0xffff)
						break;
					*(char*) (*p * 0x21c + 0x7f4e28) = 0;
					p += 10;
				} while ((int) p < 0x7e35d0);
			} else {
				g_774654 = 1;
				fcn_00532ef0();
			}
		}
		m = fcn_00502cd0(*(unsigned int*) (t + 0x14), 1, 4, 0x17);
		if (m) {
			acc = (int*) (0x779160 + count * 0x58);
			do {
				if (*(int*) (m + 0xe) > 1) {
					found = 1;
					for (i = 0; (i < count) && found; i++) {
						if (*(unsigned int*) (0x779160 + i * 0x58) == *(unsigned short*) m)
							found = 0;
					}
					if (found) {
						if ((int) acc < 0x7796e0) {
							count++;
							*acc = *(unsigned short*) m;
							acc += 0x16;
						}
					}
				}
				m = (int) gm_NextEntityQueryMatch();
			} while (m);
		}
		if (count > 0) {
			acc = (int*) 0x779160;
			for (i = count; i > 0; i--) {
				m = fcn_00502cd0(*(unsigned int*) (r + 0x14), 1, 0, *acc);
				if (m)
					acc[0x14] = *(int*) (m + 0xe);
				else
					acc[0x14] = 0;
				m = fcn_00502cd0(*(unsigned int*) (q + 0x14), 1, 0, *acc);
				if (m)
					acc[0x15] = gm_GetMsgField(q, m);
				else
					acc[0x15] = 0;
				acc[1] = 0;
				acc[2] = 0;
				acc[3] = 0;
				acc[4] = 0;
				acc += 0x16;
			}
		}
		itoa(count, buf, 10);
		fcn_0046f940(item, buf);
		fcn_00595330(h, 2, count, r, 1);
		fcn_00595e20(a0, r);
		fcn_005963f0(h, 1, 0, a0);
	} while (fcn_005373e0(0x59ba40, 0x677c7));
	fcn_00471e30(h);
	fcn_0052a2d0();
	return 0;
}

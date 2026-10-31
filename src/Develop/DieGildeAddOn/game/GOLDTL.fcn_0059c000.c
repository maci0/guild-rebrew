#include <string.h>

extern int g_772514;
extern char* lpObjektePROT;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_100f884;
extern int g_67d370;
extern int g_7746cc;
extern int g_774654;
extern int g_14ce8e0;
extern int g_7798a0;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern unsigned short g_774970;
extern unsigned short g_7f3ee4;

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
void __cdecl fcn_004c35f0(void);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_005039e0(char*);
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
	char pad24[0x14];
	int c28;
	int c2c;
	int c30;
	unsigned short c34;
	char flag36;
	char pad37[0x21];
	unsigned short id;
	char pad5a[2];
	int neg5c;
	char pad60[8];
	int f68;
	int f6c;
	char pad70[0x88];
} Req_59c000;

/* ADDRESS: GOLDTL 0x0059c000 */
int __cdecl fcn_0059c000(char* a0)
{
	Req_59c000 req;
	char buf[8];
	int v15;
	int v16;
	int item;
	int h;
	int q;
	int t;
	int found;
	int i;
	int k;
	int j;
	int m;
	int count;
	int any;
	int sel;
	int* p;
	int* rows;
	int* ep;
	int* acc;
	char* row;

	if (fcn_00525fb0((int) a0))
		return 0;
	h = fcn_00470820(0, 0, "Handel\\Handel_PRODUKTION");
	fcn_00471b60(h);
	fcn_0052a0c0(a0, 0);
	d2_SetForm(h, 3);
	io_AppendText(0xcb);
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
		q = fcn_00502cd0(*(unsigned int*) (a0 + 0x5d), 2, 6, 0, 0x2a);
		if (!q)
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
				rows = (int*) 0x7798c0;
				for (k = 0; k < count; k++) {
					if (g_67d370 == *(int*) (0x779194 + k * 0x58)) {
						if (any) {
							found = fcn_005463a0(2, 0, 4, 3, *(unsigned int*) (a0 + 1));
							while (found) {
								if (*(unsigned short*) (found + 0xac) == *rows)
									goto located;
								found = he_fn_Handlung();
							}
							fcn_004c35f0();
							memset(&req, 0, sizeof(req));
							req.flag4 = 4;
							if (*(unsigned short*) (a0 + 0x27) != 0xffff)
								req.f8 = *(unsigned int*) (*(unsigned short*) (a0 + 0x27) * 0x21c + 0x7f4ca4);
							else
								req.f8 = *(unsigned int*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca4);
							req.c28 = g_7f4c00;
							req.c2c = g_7f4c04;
							req.c30 = g_7f4c08;
							req.c34 = g_7f4c0c;
							req.id = *(unsigned short*) (0x779160 + k * 0x58);
							req.f12 = *(unsigned int*) (a0 + 1);
							req.f16 = 0;
							req.f20 = 0;
							req.flag36 = 1;
							req.neg5c = -1;
							req.f68 = *(unsigned int*) (a0 + 1);
							req.f6c = *(unsigned int*) (q + 2);
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
									j = g_7746cc;
									if (!j)
										j = fcn_00502cd0(*(unsigned int*) (a0 + 0x5d), 1, 0, 0xfd);
									fcn_00529160(a0, j, *p, found);
									*(char*) (*p * 0x21c + 0x7f4e28) = 0;
								}
								p += 10;
							} while ((int) p < 0x7e35d0);
							if (!*(int*) (found + 0x70))
								*(int*) (found + 0x70) = 1;
						} else {
							p = (int*) 0x7e30d0;
							do {
								if (*p == 0xffff)
									break;
								row = *(char**) (*p * 0x21c + 0x7f4e1c);
								if (row && (*row == 4) && (*(int*) (row + 0x10) == *(int*) (a0 + 1)) && (*(unsigned short*) (row + 0xac) == *(unsigned int*) (0x779160 + k * 0x58)))
									*(char*) (*p * 0x21c + 0x7f4e28) = 1;
								p += 10;
							} while ((int) p < 0x7e35d0);
						}
					}
					ep = (int*) (0x779164 + k * 0x58);
					for (j = 0; j < 4; j++) {
						if (g_67d370 == ep[0xe]) {
							if (*(int*) (0x77918c + k * 0x58) != j)
								g_7798a0 = *ep;
							else
								g_7798a0 = 0;
						}
						ep++;
					}
					rows += 0xe;
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
		fcn_005039e0(a0);
		if (count < 0x10) {
			p = (int*) 0x90d520;
			acc = (int*) (0x779160 + count * 0x58);
			for (i = 0; i < (int) (unsigned short) g_7f3ee4; i++) {
				row = (char*) (lpObjektePROT + *p * 0x41);
				if (*row == 0x17)
					goto nextcand;
				found = 1;
				for (j = 0; j < 4 && found; j++) {
					if (*(unsigned short*) (row + 0x2e + j * 2)) {
						m = fcn_00502cd0(*(unsigned int*) (t + 0x14), 1, 0, *(unsigned short*) (row + 0x2e + j * 2));
						if (!m || (*(int*) (m + 0xe) != 2 && *a0 != 0x1e))
							found = 0;
					}
				}
				if (found) {
					for (m = 0; m < count; m++) {
						if (*(int*) (0x779160 + m * 0x58) == *p)
							break;
					}
					if (m == count) {
						if ((int) acc < 0x7796e0) {
							*acc = *p;
							count++;
							acc += 0x16;
						}
					}
				}
nextcand:
				p++;
			}
		}
		if (count > 0) {
			acc = (int*) 0x7791b0;
			for (k = 0; k < count; k++) {
				*acc = 0x7fffffff;
				for (j = 0; j < 4; j++) {
					row = (char*) (lpObjektePROT + *(int*) (0x779160 + k * 0x58) * 0x41);
					*(int*) (0x779164 + k * 0x58 + j * 4) = *(unsigned short*) (row + 0x2e + j * 2);
					*(int*) (0x779174 + k * 0x58 + j * 4) = *(unsigned short*) (row + 0x26 + j * 2);
					if (!*(int*) (0x779164 + k * 0x58 + j * 4))
						continue;
					m = fcn_00502cd0(*(unsigned int*) (q + 0x14), 1, 0, *(int*) (0x779164 + k * 0x58 + j * 4));
					if (m) {
						if (*acc >= gm_GetMsgField(q, m) / *(int*) (0x779174 + k * 0x58 + j * 4))
							*acc = gm_GetMsgField(q, m) / *(int*) (0x779174 + k * 0x58 + j * 4);
					} else {
						*acc = 0;
					}
				}
				*acc = *(unsigned short*) (lpObjektePROT + *(int*) (0x779160 + k * 0x58) * 0x41 + 0x36) * *acc;
				m = fcn_00502cd0(*(unsigned int*) (q + 0x14), 1, 0, *(int*) (0x779160 + k * 0x58));
				if (m)
					acc[1] = gm_GetMsgField(q, m);
				else
					acc[1] = 0;
				acc += 0x16;
			}
		}
		itoa(count, buf, 10);
		fcn_0046f940(item, buf);
		fcn_00595330(h, 2, count, q, 2);
		fcn_00595e20(a0, q);
		fcn_005963f0(h, 1, 0, a0);
	} while (fcn_005373e0(0x59c000, 0x677c7));
	fcn_00471e30(h);
	fcn_0052a2d0();
	return 0;
}

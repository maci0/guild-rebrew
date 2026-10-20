extern char* g_1015ea0;
extern char* g_item_def_table;
extern int g_772514;
extern int g_100f1dc;
extern int g_100f884;
extern int g_67d370;
extern int g_774654;
extern int g_14ce8e0;
extern int g_774970;
extern char* g_7746cc;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca4[];

void* __cdecl memset(void*, int, unsigned int);
char* __cdecl itoa(int, char*, int);
int __cdecl fcn_00525fb0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00472830(int, int);
int __cdecl fcn_0046f940(int, char*);
int __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00533dc0(int, int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void __cdecl fcn_00594340(void);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_0050df70(char*, char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00529160(char*, char*, int, char*);
void __cdecl fcn_005944d0(int);
void __cdecl fcn_00594de0(int, int, int, char*);
int __cdecl fcn_00595e20(int, int);
void __cdecl fcn_005963f0(int, int, int, int);
void __cdecl fcn_004c35f0(void);
char* __cdecl fcn_005463a0(int, ...);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_004c5530(char*);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
char* __cdecl gm_NextEntityQueryMatch(void);

typedef struct Msg59b {
	char pad0[4];
	unsigned char type;
	char pad5[3];
	int f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	char pad1c[0xc];
	int f28;
	int f2c;
	int f30;
	unsigned short f34;
	unsigned char f36;
	char pad37[1];
	unsigned short f38;
	char pad3a[0x1e];
	int f58;
	int f5c;
	int f60;
	int f64;
	char pad68[0x90];
} Msg59b;

/* ADDRESS: GOLDTL 0x0059b260 */
int __cdecl fcn_0059b260(int a0)
{
	char buf[4];
	Msg59b msg;
	int id1;
	int id2;
	int id3;
	int count;
	int hasAny;
	int n;
	int i;
	int k;
	int h;
	char* p1;
	char* p2;
	char* p3;
	char* p;
	char* q;
	char* e;
	int v;
	int prev;
	int div;

	if (fcn_00525fb0(a0) != 0) {
		return 0;
	}
	h = fcn_00470820(0, 0, (char*) 0x6aa148);
	fcn_00471b60(h);
	fcn_0052a0c0(a0, 0);
	fcn_004727a0(h, 3);
	fcn_00519190(0xc7);
	fcn_00594340();
	*(int*) 0x779160 = 0;
	count = 1;
	fcn_004727a0(h, 0);
	k = g_772514 * 0x3cc;
	*(int*) (k + 0x10162e8) = 0xe;
	*(int*) (k + 0x10162ec) = 0xe;
	*(int*) (k + 0x10162f0) = 0xe;
	*(int*) (k + 0x10162f4) = 0xe;
	fcn_00533dc0(g_772514, 0x70b, 0x742);
	fcn_00533f40(0x270, 0x15e, g_772514, fcn_00472830(h, 2), 0x78, &id2, &id1, &id3);
	*(int*) (g_1015ea0 + id3 * 0x2f4 + 0x84) = 0x54;
	fcn_00473a90(0, 0);
	do {
		fcn_004727a0(h, 2);
		p1 = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, 0xff);
		if (p1 == 0) {
			return 0;
		}
		p2 = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, 0x2a);
		if (p2 == 0) {
			return 0;
		}
		p3 = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, 0xfe);
		if (p3 == 0) {
			return 0;
		}
		if (g_100f1dc != -1 && g_100f884 == h) {
			hasAny = 0;
			q = (char*) 0x7e30e0;
			do {
				if (q >= (char*) 0x7e35e0) {
					break;
				}
				if (*(int*) (q - 0x10) == 0xffff) {
					break;
				}
				if (*(int*) q != 0) {
					hasAny = 1;
				}
				q += 0x28;
			} while (hasAny == 0);
			i = 0;
			if (count > 0) {
				do {
					e = (char*) (0x779160 + i * 0x58);
					if (g_67d370 == *(int*) (e + 0x34)) {
						if (hasAny != 0) {
							if (i == 0) {
								fcn_004c35f0();
								p = fcn_005463a0(2, 0, 9, 3, *(int*) (a0 + 4));
								if (p == 0) {
									memset(&msg, 0, 0xf8);
									msg.f28 = g_7f4c00;
									msg.f30 = g_7f4c08;
									msg.type = 9;
									msg.f08 = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
									msg.f0c = *(int*) (a0 + 4);
									msg.f10 = 0;
									msg.f14 = 0;
									msg.f36 = 1;
									msg.f2c = g_7f4c04;
									msg.f34 = (unsigned short) g_7f4c0c;
									msg.f58 = *(int*) (a0 + 4);
									msg.f5c = *(int*) (p1 + 2);
									msg.f60 = *(int*) (p3 + 2);
									k = fcn_004c5530((char*) &msg);
									e = (char*) fcn_004c4450(k);
									while (e == 0) {
										fcn_005373e0(0, 0x20007);
										e = (char*) fcn_004c4450(k);
									}
									p = fcn_004c4480(k);
								}
							}
							else {
								fcn_004c35f0();
								p = fcn_005463a0(2, 0, 8, 3, *(int*) (a0 + 4));
								while (p != 0) {
									if (*(unsigned short*) (p + 0xac) == *(int*) e) {
										break;
									}
									p = fcn_005462a0();
								}
								if (p == 0) {
									memset(&msg, 0, 0xf8);
									msg.f28 = g_7f4c00;
									msg.type = 8;
									msg.f30 = g_7f4c08;
									msg.f36 = 1;
									*(unsigned short*) &msg.f58 = (unsigned short) *(int*) e;
									msg.f0c = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
									msg.f14 = 0;
									msg.f18 = 0;
									msg.f10 = *(int*) (a0 + 4);
									msg.f30 = g_7f4c04;
									msg.f38 = (unsigned short) g_7f4c0c;
									msg.f60 = *(int*) (a0 + 4);
									msg.f64 = *(int*) (p2 + 2);
									k = fcn_004c5530((char*) &msg);
									e = (char*) fcn_004c4450(k);
									while (e == 0) {
										fcn_005373e0(0, 0x20007);
										e = (char*) fcn_004c4450(k);
									}
									p = fcn_004c4480(k);
								}
							}
							if (p != 0) {
								q = (char*) 0x7e30d0;
								do {
									n = *(int*) q;
									if (n == 0xffff) {
										break;
									}
									if (*(int*) (q + 0x10) != 0) {
										fcn_00529160((char*) a0, g_7746cc, n, p);
										*(unsigned char*) (0x7f4e28 + n * 0x21c) = 0;
									}
									q += 0x28;
								} while (q < (char*) 0x7e35d0);
								if (*(int*) (p + 0x70) == 0) {
									*(int*) (p + 0x70) = 1;
								}
							}
						}
						else {
							q = (char*) 0x7e30d0;
							do {
								n = *(int*) q;
								if (n == 0xffff) {
									break;
								}
								p = *(char**) (0x7f4e1c + n * 0x21c);
								if (i == 0) {
									if (p != 0 && *(char*) p == 9 && *(int*) (p + 0x10) == *(int*) (a0 + 4)) {
										*(unsigned char*) (0x7f4e28 + n * 0x21c) = 0;
									}
								}
								else {
									if (p != 0 && *(char*) p == 8 && *(int*) (p + 0x10) == *(int*) (a0 + 4)
										&& *(unsigned short*) (p + 0xac) == *(int*) e) {
										*(unsigned char*) (0x7f4e28 + n * 0x21c) = 1;
									}
								}
								q += 0x28;
							} while (q < (char*) 0x7e35d0);
						}
					}
					i++;
				} while (i < count);
			}
		}
		if (g_14ce8e0 != 0) {
			hasAny = 0;
			q = (char*) 0x7e30e0;
			do {
				if (q >= (char*) 0x7e35e0) {
					break;
				}
				if (*(int*) (q - 0x10) == 0xffff) {
					break;
				}
				if (*(int*) q != 0) {
					hasAny = 1;
				}
				q += 0x28;
			} while (hasAny == 0);
			if (hasAny != 0) {
				q = (char*) 0x7e30d0;
				do {
					n = *(int*) q;
					if (n == 0xffff) {
						break;
					}
					*(unsigned char*) (0x7f4e28 + n * 0x21c) = 0;
					q += 0x28;
				} while (q < (char*) 0x7e35d0);
			}
			else {
				g_774654 = 1;
				fcn_00532ef0();
			}
		}
		e = fcn_00502cd0(*(int*) (p1 + 0x14), 1, 4, 0x17);
		if (e != 0) {
			k = count;
			p = (char*) (0x779160 + count * 0x58);
			do {
				if (*(int*) (e + 0xe) > 1) {
					v = 0;
					for (n = 1; n < k; n++) {
						if (*(int*) (0x779160 + n * 0x58) == *(unsigned short*) e) {
							v = 1;
							break;
						}
					}
					if (v == 0 && p < (char*) 0x7796e0) {
						*(int*) p = *(unsigned short*) e;
						p += 0x58;
						k++;
					}
				}
				e = gm_NextEntityQueryMatch();
			} while (e != 0);
			count = k;
		}
		if (count > 1) {
			n = count - 1;
			p = (char*) 0x779208;
			do {
				q = p - 0x4c;
				*(int*) p = 0x7fffffff;
				k = 0x26;
				do {
					i = *(int*) (p - 0x50);
					v = *(unsigned short*) (g_item_def_table + i * 0x41 + k + 8);
					prev = *(unsigned short*) (g_item_def_table + i * 0x41 + k);
					*(int*) q = v;
					*(int*) (q + 0x10) = prev;
					if (v != 0) {
						e = fcn_00502cd0(*(int*) (p2 + 0x14), 1, 0, v);
						if (e == 0) {
							*(int*) p = 0;
						}
						else {
							div = *(unsigned short*) (g_item_def_table + i * 0x41 + k);
							v = fcn_0050df70(p2, e);
							prev = *(int*) p;
							v = v / div;
							if (prev >= v) {
								v = fcn_0050df70(p2, e) / div;
							}
							else {
								v = prev;
							}
							*(int*) p = v;
						}
					}
					k += 2;
					q += 4;
				} while (k < 0x2e);
				i = *(int*) (p - 0x50);
				v = *(unsigned short*) (g_item_def_table + i * 0x41 + 0x36);
				*(int*) p *= v;
				e = fcn_00502cd0(*(int*) (p2 + 0x14), 1, 0, i);
				if (e != 0) {
					*(int*) (p + 4) = fcn_0050df70(p2, e);
				}
				else {
					*(int*) (p + 4) = 0;
				}
				p += 0x58;
			} while (--n);
		}
		itoa(count - 1, buf, 10);
		fcn_0046f940(id3, buf);
		fcn_00594de0(h, 2, count, p3);
		fcn_00595e20(a0, (int) p2);
		fcn_005963f0(h, 1, 0, a0);
	} while (fcn_005373e0(fcn_005944d0, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_0052a2d0();
	return 0;
}

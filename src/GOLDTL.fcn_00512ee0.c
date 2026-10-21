#include <string.h>

#include "client_types.h"

#pragma pack(push, 1)

/* SIZE 0x29 */
typedef struct {
	unsigned char office;
	int id;
	char pad5[0x22];
	unsigned short slot;
} Player;

/* SIZE 0x21c */
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x15c];
	unsigned char kind;
	char pad165[0xb7];
} Entity;

/* SIZE 0x24d */
typedef struct {
	unsigned char kind;
	char pad1[0x222];
	unsigned char slots[6];
	char pad229[6];
	unsigned char f22f;
	unsigned char f230;
	char pad231[0x1c];
} Office;

/* SIZE 0xf8 */
typedef struct {
	int f0;
	unsigned char b4;
	char pad5[3];
	int f8;
	int fc;
	int f10;
	int f14;
	char pad18[0x10];
	pos14_7f4c00 pos;
	unsigned char b36;
	char pad37[0x21];
	int f58;
	int f5c;
	char pad60[0x98];
} Msg;

#pragma pack(pop)

extern unsigned char *g_868050;
extern unsigned char *g_90e094;
extern unsigned char *g_773da8;
extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;
extern int g_6a3424;
extern unsigned char g_6a3440;

int __cdecl gm_RandomMod(int);
void __cdecl fcn_00455350(char *, char *, char *);
void __cdecl fcn_004c3ff0(void);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_004c44a0(void);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_004c4510(char *, int);
int __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char *);
void __cdecl fcn_004c4940(void);
void __cdecl fcn_004c4b00(void);
void __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c51f0(int, int, short, int, char, int);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c5530(Msg *);
int __cdecl fcn_004c5f60(int, int, int);
void __cdecl fcn_004c6000(int, int);
int __cdecl fcn_004c6090(unsigned char *, int, int, int);
int __cdecl fcn_004c65a0(int, int, char *, float *);
void __cdecl fcn_004fb390(void);
int __cdecl fcn_00503e80(void);
int __cdecl fcn_00503fe0(int, ...);
int __cdecl fcn_00504db0(unsigned char *, int);
int __cdecl fcn_00505370(unsigned char *);
int __cdecl fcn_005072c0(int);
int __cdecl fcn_0050b750(int, char);
int __cdecl fcn_0050cf50(unsigned char *, int);
int __cdecl fcn_0050d170(int);
void __cdecl fcn_00511c60(int);
void __cdecl fcn_00512b40(unsigned char *);
void __cdecl fcn_00512d20(unsigned char *);
void __cdecl fcn_00535960(void);
void __cdecl fcn_0053f630(int, int);
void __cdecl fcn_00547010(void);
void __cdecl fcn_005470a0(void);
void __cdecl fcn_00547130(void);
void __cdecl fcn_005471c0(void);
int __cdecl fcn_00597ff0(int, char *);
int __cdecl fcn_00598150(int, char **);
void __cdecl fcn_00598740(float *, int);

/* ADDRESS: GOLDTL 0x00512ee0 */
void __cdecl fcn_00512ee0(void)
{
	char kinds[34] = {0, 0, 3, 0, 1, 1, 0, 1, 1, 1, 0, 2, 2, 2, 1, 0,
			2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 3, 3, 1, 0, 1, 1, 0};
	char *e;
	char *f;
	Player *p;
	Office *o;
	int i;
	int j;
	int n;
	int h;
	int q;
	int res;
	int done;
	int outer;
	int total;
	int inner;
	int count;
	unsigned int kind;
	unsigned short slot;
	{
	int counts[34] = {0};
	int found[8] = {0};
	int handles[16] = {0};
	char path[16];
	char name[96];
	int list[128];
	float pos3[3];

	n = 0;
	for (e = g_7f4ca0 + 2; e < g_7f4ca0 + 0x65402; e += 0x21c) {
		if (n >= 8)
			break;
		if (*(short *)(e - 2) != -1 && (*e == 6 || *e == 7 || *e == 5)) {
			found[n] = (int)(e - 2);
			n++;
		}
	}
	total = n;

	for (i = 0; i < total; i++) {
		e = (char *)found[i];
		if (e == 0)
			continue;
		if (!(*(unsigned char *)(e + 2) == 6 || *(unsigned char *)(e + 2) == 7
				|| *(unsigned char *)(e + 2) == 5))
			continue;
		done = 0;
		inner = 0;
		do {
			p = (Player *)(g_90e094 + inner);
			if (p->office != 0 && p->slot == 0xffff) {
				o = (Office *)(g_868050 + p->office * 0x24d);
				for (j = 0; j < 6; j++) {
					if (o->slots[j] != 0
							&& o->slots[j] == *(unsigned char *)(e + 0x164)) {
						h = fcn_004c5f60(p->id, *(int *)(e + 4),
								*(int *)(e + 4));
						while (fcn_004c4450(h) == 0) {
							fcn_00535960();
						}
						fcn_00512d20((unsigned char *)p);
						done = 1;
						counts[o->kind]++;
						break;
					}
				}
			}
			if (done)
				break;
			inner += 0xa9;
		} while (inner < 0xa900);
		if (!done) {
			kind = fcn_005072c0(*(unsigned char *)(e + 0x164));
			if (fcn_00597ff0(kind, name)
					&& (res = fcn_00598150(kind, (char **)list)) != 0) {
				j = 0;
				if (res >= 1) {
					do {
						if (list[j])
							break;
						j++;
					} while (j < res);
				}
				fcn_00455350((char *)list[j], (char *)(list[j] + 0x4c), path);
				fcn_00598740(pos3, list[j]);
				h = fcn_004c65a0(*(int *)(e + 4), kind, path, pos3);
				if (h != -1) {
					while (fcn_004c4450(h) == 0) {
						fcn_00535960();
					}
				}
				h = fcn_004c4480(h);
				if (h)
					fcn_00512d20((unsigned char *)h);
			}
		}
	}

	fcn_0053f630(0, 0x55);
	for (i = 0; i < total; i++) {
		e = (char *)found[i];
		if (e == 0)
			continue;
		h = fcn_00503fe0(1, 4, *(unsigned short *)e);
		if (h && fcn_00505370((unsigned char *)h))
			h = 0;
		if (*(unsigned char *)(e + 2) != 5 && *(unsigned char *)(e + 2) != 4) {
			if (h) {
				q = fcn_00504db0((unsigned char *)h, 4);
				if (!q) {
					q = fcn_00504db0((unsigned char *)h, 5);
					if (!q)
						break;
				}
			} else {
				q = fcn_00503fe0(2, 0, 4, 4, 0xffff);
				if (!q) {
					q = fcn_00503fe0(2, 0, 5, 4, 0xffff);
					if (!q)
						break;
				}
			}
		} else if (h) {
			q = fcn_00504db0((unsigned char *)h, 5);
			if (!q) {
				q = fcn_00504db0((unsigned char *)h, 4);
				if (!q)
					break;
			}
		} else {
			q = fcn_00503fe0(2, 0, 5, 4, 0xffff);
			if (!q) {
				q = fcn_00503fe0(2, 0, 4, 4, 0xffff);
				if (!q)
					break;
			}
		}
		fcn_004c6000(*(int *)(e + 4), *(int *)(q + 1));
		h = fcn_004c5f60(*(int *)(q + 1), *(int *)(e + 4), *(int *)(e + 4));
		while (fcn_004c4450(h) == 0) {
			fcn_00535960();
		}
	}

	fcn_0053f630(0, 0x5a);
	for (n = 0xb; n <= 0xd; n++) {
		e = (char *)fcn_00503fe0(2, 4, 0xffff, 5, n);
		if (e == 0)
			continue;
		count = fcn_0050cf50((unsigned char *)e, 100);
		fcn_004c4510(e, *(int *)(e + 1));
		fcn_004c4570(4, 1, 0x65, (char *)&count);
		count = count * 2;
		fcn_004c4570(4, 1, 0x69, (char *)&count);
		fcn_004c5360();
		o = (Office *)(g_868050 + *(unsigned char *)e * 0x24d);
		fcn_004c5f60(*(int *)(e + 1), *(int *)(g_773da8 + 4),
				*(int *)(g_773da8 + 4));
		fcn_004c6090((unsigned char *)e, 1, o->f230, o->slots[0]);
		fcn_004c6090((unsigned char *)e, 0, o->f22f, 0);
		fcn_004c6090((unsigned char *)e, 0, o->f22f, 0);
		fcn_004c51f0(*(int *)(e + 1), -1, 0x135, 1, g_773d75, 0);
		counts[n]++;
	}

	fcn_0053f630(0, 0x5f);
	e = (char *)fcn_00503fe0(2, 4, 0xffff, 5, 0x10);
	if (e) {
		o = (Office *)(g_868050 + *(unsigned char *)e * 0x24d);
		h = fcn_004c6090((unsigned char *)e, 2, o->f230, 0x2d);
		while (fcn_004c4450(h) == 0) {
			fcn_00535960();
		}
		h = *(int *)(fcn_004c4480(h) + 4);
		fcn_004c5f60(*(int *)(e + 1), h, h);
		fcn_004c6090((unsigned char *)e, 0, o->f22f, 0);
		fcn_004c6090((unsigned char *)e, 0, o->f230, 0);
		fcn_004c51f0(*(int *)(e + 1), -1, 0x135, 1, g_773d75, 0);
		counts[0x10]++;
	}

	if (g_6a3424) {
		outer = 0;
		for (inner = 0; inner < 0xa900; inner += 0xa9) {
			p = (Player *)(g_90e094 + inner);
			if (p->office == 0 || p->slot != 0xffff)
				continue;
			o = (Office *)(g_868050 + p->office * 0x24d);
			kind = o->kind;
			if (kinds[kind] != 1 || counts[kind] >= 2)
				continue;
			slot = 0;
			fcn_004c44a0();
			for (j = 5; j >= 0; j--) {
				if (o->slots[j]) {
					slot = o->slots[j];
					break;
				}
			}
			h = fcn_004c6090((unsigned char *)p, 2, o->f230, slot);
			while (fcn_004c4450(h) == 0) {
				fcn_00535960();
			}
			q = fcn_004c4480(h);
			count = fcn_0050b750(3000, g_773d75);
			fcn_004c5150(*(int *)(q + 4), -1, g_773d75, count);
			if (outer <= 0xf) {
				handles[outer] = q;
				outer++;
			}
			kind = o->kind;
			if (kind != 9 && kind != 5) {
				if (kind != 4 && kind != 0x10 && kind != 0x13) {
					fcn_004c6090((unsigned char *)p, 0, o->f22f, 0);
				} else {
					fcn_004c6090((unsigned char *)p, 0, o->f22f, 0);
					fcn_004c6090((unsigned char *)p, 0, o->f230, 0);
				}
			}
			fcn_004c51f0(p->id, -1, 0x135, 1, g_773d75, 0);
			if (o->kind == 5) {
				count = fcn_0050b750(6000, g_773d75);
				fcn_004c5150(*(int *)(q + 4), -1, g_773d75, count);
			}
			fcn_00512b40((unsigned char *)p);
			fcn_004c44b0();
			counts[o->kind]++;
		}
		while (fcn_004c44c0() == 0) {
			fcn_004c3ff0();
			fcn_004c4940();
			fcn_004c4b00();
		}
		for (i = 0; i < outer; i++) {
			e = (char *)handles[i];
			if (e == 0)
				continue;
			h = fcn_00503fe0(1, 4, *(unsigned short *)e);
			if (h == 0 || fcn_00505370((unsigned char *)h) != 0) {
				q = fcn_00503fe0(2, 0, 5, 4, 0xffff);
				if (!q) {
					q = fcn_00503fe0(2, 0, 4, 4, 0xffff);
					if (!q)
						goto release_handles;
				}
			} else {
				q = fcn_00504db0((unsigned char *)h, 5);
				if (!q) {
					q = fcn_00504db0((unsigned char *)h, 4);
					if (!q)
						goto release_handles;
				}
			}
			fcn_004c6000(*(int *)(q + 1), *(int *)(e + 4));
			h = fcn_004c5f60(*(int *)(q + 1), *(int *)(e + 4),
					*(int *)(e + 4));
			while (fcn_004c4450(h) == 0) {
				fcn_00535960();
			}
		}
		goto handles_done;
release_handles:
		for (; i < outer; i++) {
			e = (char *)handles[i];
			if (e) {
				count = fcn_0050d170(4);
				fcn_004c5150(*(int *)(e + 4), -1, g_773d75, count);
			}
		}
handles_done:
		;
	}
	}
	{
	Msg msg;

	fcn_004c44a0();
	for (inner = 0; inner < 0xa900; inner += 0xa9) {
		p = (Player *)(g_90e094 + inner);
		o = (Office *)(g_868050 + p->office * 0x24d);
		slot = p->slot;
		kind = o->kind;
		if (slot != 0xffff) {
			if (kinds[kind] == 2 || kinds[kind] == 1) {
				e = g_7f4ca0 + slot * 0x21c;
				if (*(unsigned char *)(e + 2) == 5
						|| *(unsigned char *)(e + 2) == 4) {
					if (g_6a3424) {
						if (kind != 9 && kind != 5) {
							if (kind != 4 && kind != 0x10 && kind != 0x13) {
								fcn_004c6090((unsigned char *)p, 0, o->f22f, 0);
							} else {
								fcn_004c6090((unsigned char *)p, 0, o->f22f, 0);
								fcn_004c6090((unsigned char *)p, 0, o->f230, 0);
							}
						}
						fcn_004c6090((unsigned char *)p, 1, o->f230, o->slots[0]);
						fcn_004c51f0(p->id, -1, 0x135, 1, g_773d75, 0);
						fcn_00512b40((unsigned char *)p);
					}
					continue;
				}
			}
		}
		if (kinds[o->kind] == 0 && slot == 0xffff)
			fcn_004c5f60(p->id, *(int *)(g_773da8 + 4),
					*(int *)(g_773da8 + 4));
	}
	fcn_004c44b0();
	while (fcn_004c44c0() == 0) {
		fcn_004c3ff0();
		fcn_004c4940();
		fcn_004c4b00();
	}
	fcn_00511c60(0);
	fcn_004fb390();
	e = (char *)fcn_00503fe0(1, 6);
	while (e) {
		if (*(short *)(e + 0x25) == -1 && *e != 'E' && *e != 'D' && *e != 'F') {
			msg.b4 = 0x1b;
			msg.f8 = *(int *)(g_773da8 + 4);
			msg.fc = -1;
			msg.b36 = 2;
			msg.f58 = *(int *)(e + 1);
			msg.f5c = fcn_0050cf50((unsigned char *)e, (char)e[0x5c]);
			fcn_004c5f60(*(int *)(e + 1), *(int *)(g_773da8 + 4),
					*(int *)(g_773da8 + 4));
			fcn_004c5530(&msg);
		}
		e = (char *)fcn_00503e80();
	}
	if (g_6a3440 == 5) {
		n = 0;
		for (e = g_7f4ca0 + 2; e < g_7f4ca0 + 0x65402; e += 0x21c) {
			if (*e == 6)
				break;
			n++;
		}
		memset(&msg, 0, sizeof(msg));
		msg.b4 = 0x4c;
		msg.f8 = *(int *)(g_7f4ca0 + n * 0x21c + 4);
		msg.fc = msg.f8;
		msg.f10 = 0;
		msg.f14 = 0;
		msg.pos = g_7f4c00;
		msg.b36 = 1;
		fcn_004c5530(&msg);
	}
	fcn_00547010();
	fcn_005470a0();
	fcn_00547130();
	fcn_005471c0();
	outer = 0;
	for (e = g_7f4ca0 + 2; e < g_7f4ca0 + 0x651e6; e += 0x21c) {
		if (*e == 6 || *e == 7 || *e == 5 || *e == 3 || *e == 4 || *e == 2) {
			total = 0;
			if (outer + 1 < 0x300) {
				for (f = e + 0x21c; f < g_7f4ca0 + 0x65402; f += 0x21c) {
					if (!(*f == 6 || *f == 7 || *f == 5 || *f == 3 || *f == 4
								|| *f == 2))
						continue;
					fcn_004c54c0(*(int *)(e + 2), *(int *)(f + 2),
							(int)(gm_RandomMod(0x40) & 0xffff) - 0x20, 0);
					res = fcn_004c54c0(*(int *)(f + 2), *(int *)(e + 2),
							(int)(gm_RandomMod(0x40) & 0xffff) - 0x20, 0);
					total += 2;
					if (res != -1 && total % 10 == 0) {
						while (fcn_004c4450(res) == 0) {
							fcn_00535960();
						}
					}
				}
			}
		}
		outer++;
	}
	}
}

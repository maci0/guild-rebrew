#include <string.h>

/* Out-parameter block of the entity search helper at 0x55be70. */
typedef struct {
	void* obj;      /* +0x00 */
	float radius;   /* +0x04 */
	void* owner;    /* +0x08 */
	void* found;    /* +0x0c */
} SEARCH;

int __cdecl fcn_0051af00(void*, int, ...);
void __cdecl he_MessageBoxQuickjump(unsigned int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c51f0(int, int, int, int, int);
void __cdecl fcn_004c5a60(int, int, int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c58b0(int, int);
char* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c4510(char*, int);
void* __cdecl fcn_00503fe0(int, int, int);
unsigned char* __cdecl fcn_00508e40(int);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl fcn_00529160(char*, int, int, int);
int __cdecl fcn_00529670(char*, char*);
int __cdecl fcn_0055be70(int*);
int __cdecl fcn_004f4f60(int, int, int, int, int);
int __cdecl fcn_005463a0(int, int, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl fcn_00502cd0(int, int, ...);
void* __cdecl fcn_00502850(void);
int __cdecl fcn_00507e30(char*, int);
char* __cdecl fcn_00509570(char*);
int __cdecl fcn_0050c5d0(char*, int*);
int __cdecl fcn_0050c710(char*, int, int);
int __cdecl fcn_0050b750(int);
int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
int __cdecl _ftol(void);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_0055c050(char*);
float __cdecl fcn_004ff210(short, int);
float __cdecl fcn_0050bb50(int, int);
int __cdecl fcn_0050df70(char*, char*);

/* The 14-byte message block published by the server at 0x7f4c00. */
#define MSG_COPY(dst) \
	do { \
		*(int*) (dst) = *(int*) 0x7f4c00; \
		*(int*) ((dst) + 4) = *(int*) 0x7f4c04; \
		*(int*) ((dst) + 8) = *(int*) 0x7f4c08; \
		*(unsigned short*) ((dst) + 12) = *(unsigned short*) 0x7f4c0c; \
	} while (0)

/* Advances the active message of the player object through its states. */
/* ADDRESS: GOLDTL 0x00569ff0 */
void __cdecl fcn_00569ff0(char* e)
{
	volatile float fv;
	volatile int flag;
	volatile int count;
	volatile char* px;
	volatile int num;
	volatile char* pa;
	volatile char* pb;
	volatile char* pc;
	volatile int hits;
	volatile int val;
	SEARCH s;
	char b200[0x200];
	char b100[0x100];
	char b400[0x400];
	int* p;
	char* o;
	char* q;

	val = 0;
	pc = 0;
	hits = 0;
	px = 0;

	switch (*(int*) (e + 0x70)) {
	case 0:
		pa = (char*) fcn_00503fe0(*(int*) (e + 0xac), 1, 1);
		if (pa == 0) {
			*(int*) (e + 0x70) = -1;
			return;
		}
		p = (int*) (e + 0x8c);
		count = 8;
		do {
			if (*p != -1) {
				o = (char*) fcn_00508e40(*p);
				if (o != 0) {
					fcn_00529160(pa, 0, *(unsigned short*) o, e);
					fcn_004c5c80(*p);
					fcn_004c5da0(*p, *(int*) (pa + 1), -1, 0, 1, "Einbruch");
				}
			}
			p++;
		} while (--count);
		MSG_COPY(e + 0x52);
		fcn_00500bb0(e + 0x52, 0, 4, 0);
		*(int*) (e + 0x70) = 1;
		return;
	case 1:
		pa = (char*) fcn_00503fe0(*(int*) (e + 0xac), 1, 1);
		if (pa == 0) {
			*(int*) (e + 0x70) = -1;
			return;
		}
		p = (int*) (e + 0x8c);
		for (count = 0; count < 8; count++, p++) {
			if (*p != -1) {
				o = (char*) fcn_00508e40(*p);
				if (o != 0 && *(int*) (o + 0x184) != 0) {
					if (fcn_00529670(o, pa) == 0) {
						MSG_COPY(e + 0x52);
						fcn_00500bb0(e + 0x52, 0, 4, 0);
						return;
					}
				}
			}
		}
		MSG_COPY(e + 0x52);
		fcn_00500bb0(e + 0x52, 0, 0, 1);
		*(int*) (e + 0x70) = 2;
		return;
	case 2:
		pa = (char*) fcn_00503fe0(*(int*) (e + 0xac), 1, 1);
		if (pa != 0) {
			s.obj = pa;
			s.radius = 5000.0f;
			s.owner = e;
			s.found = 0;
			pc = (char*) (0x7f4ca0 + *(unsigned short*) (pa + 0x27) * 0x21c);
			if (fcn_0055be70((int*) &s) != 0) {
				*(int*) (e + 0xb4) = fcn_004f4f60(0x17, 1,
				        *(int*) (0x7f4ca4 + *(unsigned short*) (e + 8) * 0x21c),
				        *(int*) ((char*) s.found + 4), *(int*) (pa + 1));
				*(int*) (e + 0xb8) = *(int*) ((char*) s.found + 4);
				*(int*) (e + 0xbc) = *(int*) ((char*) s.found + 0xb0);
				*(int*) (e + 0x70) = 3;
				MSG_COPY(e + 0x52);
				return;
			}
		}
		*(int*) (e + 0x70) = 5;
		MSG_COPY(e + 0x52);
		fcn_00500bb0(e + 0x52, 0, 0xf, 0);
		return;
	case 3:
		if (*(int*) (e + 0xb4) != -1 && fcn_004c4450(*(int*) (e + 0xb4)) == 0) {
			return;
		}
		pa = (char*) fcn_00503fe0(*(int*) (e + 0xac), 1, 1);
		pb = (char*) fcn_005463a0(*(int*) (e + 0xb8), 1, 1);
		if (pa == 0 || pb == 0) {
			goto fail;
		}
		if (*(int*) (pb + 0xd4) != *(int*) (e + 4)) {
			goto fail;
		}
		if (*(int*) (e + 0xb4) == -1) {
			goto fail;
		}
		px = (char*) (0x7f4ca0 + *(unsigned short*) (pb + 8) * 0x21c);
		o = (char*) fcn_004c4480(*(int*) (e + 0xb4));
		if (px != 0 && o != 0) {
			fcn_004c58b0(*(int*) o, *(int*) (px + 4));
		}
		*(int*) (e + 0x70) = 4;
		fcn_00500bb0(e + 0x52, 0, 0xa, 0);
		return;
	case 4:
		pb = (char*) fcn_005463a0(*(int*) (e + 0xb8), 1, 1);
		if (pb == 0) {
			goto fail;
		}
		if (*(int*) (pb + 0xd4) == *(int*) (e + 4)) {
			fcn_00500bb0(e + 0x52, 0, 6, 0);
			return;
		}
		pa = (char*) fcn_00503fe0(*(int*) (e + 0xac), 1, 1);
		if (pa == 0) {
			goto again;
		}
		q = (char*) fcn_00503fe0(*(int*) (e + 0xb0), 1, 1);
		if (q != 0) {
			pc = (char*) fcn_00508e40(*(int*) (0x7f4ca4 + *(unsigned short*) (q + 0x27) * 0x21c));
		}
		px = (char*) (0x7f4ca0 + *(unsigned short*) (pb + 8) * 0x21c);
		if (px != 0 && pc != 0) {
			val = fcn_0050b750((gm_RandomMod(0xc8) & 0xffff) + 0x226);
			fcn_0051af00(b200, 0x19ea, pa, val, *(unsigned short*) px);
			fcn_00545d40(*(int*) (pc + 4), *(int*) (pc + 4), b200, 1, 0x5f0,
			        "_NACHRICHTEN_HS_76");
			fcn_0051af00(b200, 0x19eb, pa, val);
			fcn_00545d40(*(int*) (px + 4), *(int*) (px + 4), b200, 1, 0x5f0,
			        "_NACHRICHTEN_HS_77");
			fcn_004c51a0(*(int*) (pc + 4), *(int*) (px + 4), *(char*) 0x773d75, val);
		}
	again:
		o = (char*) fcn_00503fe0(*(int*) (e + 0xbc), 1, 1);
		if (o != 0) {
			fcn_004c4510(o, *(int*) (o + 1));
			fcn_004c4670(4, 1, 0x65, &val);
			fcn_004c5360();
		}
		p = (int*) (e + 0x8c);
		count = 8;
		do {
			if (*p != -1) {
				o = (char*) fcn_00508e40(*p);
				if (o != 0) {
					fcn_004ff210(*(short*) o, -100 - (gm_RandomMod(0x64) & 0xffff));
				}
			}
			p++;
		} while (--count);
		pb = (char*) fcn_00503fe0(*(int*) (e + 0xb0), 1, 1);
		if (pb != 0) {
			pa = (char*) gm_SetupEntityQuery(pb);
			p = (int*) (e + 0x8c);
			count = 8;
			do {
				if (*p != -1) {
					fcn_004c5c80(*p);
					fcn_004c5da0(*p, *(int*) (pb + 1), *(int*) (pa + 2), 0, 0,
					        "Entdeckt");
				}
				p++;
			} while (--count);
		}
		goto fail;
	case 5:
		pa = (char*) fcn_00503fe0(*(int*) (e + 0xac), 1, 1);
		pb = (char*) fcn_00503fe0(*(int*) (e + 0xb0), 1, 1);
		if (pb != 0) {
			pc = (char*) fcn_00508e40(*(int*) (0x7f4ca4 + *(unsigned short*) (pb + 0x27) * 0x21c));
		}
		if (pa == 0 || pc == 0) {
			goto fail;
		}
		count = (int) (0x7f4ca0 + *(unsigned short*) (pa + 0x27) * 0x21c);
		if ((char*) count == 0) {
			*(int*) (e + 0x70) = -1;
			return;
		}
		if (pb != 0) {
			px = (char*) gm_SetupEntityQuery(pb);
			val = fcn_00502cd0(*(int*) (pb + 0x5d), 2, 6, 0, 0x116);
			p = (int*) (e + 0x8c);
			num = 8;
			do {
				if (*p != -1) {
					o = (char*) fcn_00508e40(*p);
					if (o != 0) {
						fcn_004c5c80(*p);
						fcn_004c5da0(*p, *(int*) (pb + 1), *(int*) (px + 2), 0, 0,
						        "Einbruch");
						hits++;
						fcn_00507e30(o, 2);
						fcn_00529160(pb, 0, *(unsigned short*) o, 0);
					}
				}
				p++;
			} while (--num);
			count = (int) fcn_00502cd0(*(int*) (pb + 0x5d), 1, 0, 0xca);
			if ((char*) count != 0) {
				while (*(int*) ((char*) count + 0x2a) != *(int*) (px + 1)) {
					count = (int) fcn_00502850();
					if ((char*) count == 0) {
						break;
					}
				}
			}
			if ((char*) count == 0) {
				fv = 0.001f;
			} else {
				num = *(unsigned char*) ((char*) count + 0x37);
				fv = (float) (num * *(double*) 0x6640e8);
				if (fv < *(float*) 0x662a2c) {
					fv = 0.001f;
				}
			}
			num = fcn_0050c710(pa, 7, 1);
			*(float*) &num = (float) num * *(float*) 0x662910;
			fv = fv - *(float*) &num * *(double*) 0x665ed0;
			if (fv > gm_RandomFloat01()) {
				flag = 1;
			} else {
				flag = 0;
			}
		} else {
			flag = 0;
		}
		if (fcn_0055c050(pa) == 0) {
			flag = 0;
		}
		fcn_004f4f60(0x17, 1,
		        *(int*) (0x7f4ca4 + *(unsigned short*) (pb + 0x27) * 0x21c),
		        *(int*) ((char*) count + 4), *(int*) (pa + 1));
		if (pc != 0) {
			q = (char*) fcn_00509570(pc);
			if (q != 0) {
				*(int*) (q + 0x14) += flag;
			}
		}
		fcn_0051af00(b200, 0x19e6, *(unsigned short*) ((char*) count), flag);
		fcn_0051af00(b100, 0x19e8, *(int*) (e + 0x24), flag);
		strcpy(b400, b200);
		strcpy(b400, b100);
		fcn_00546190(e);
		return;
	default:
		pb = (char*) fcn_00503fe0(*(int*) (e + 0xb0), 1, 1);
		if (pb != 0) {
			px = (char*) gm_SetupEntityQuery(pb);
		}
		p = (int*) (e + 0x8c);
		count = 8;
		do {
			if (*p != -1) {
				o = (char*) fcn_00508e40(*p);
				if (o != 0) {
					fcn_004c5c80(*p);
					if (pb != 0 && px != 0) {
						fcn_004c5da0(*p, *(int*) (pb + 1), *(int*) (px + 2), 0, 0,
						        "Einbruch");
					} else {
						fcn_004c5da0(*p, -1, -1, 0, 0, "Einbruch");
					}
					fcn_00529160(0, 0, *(unsigned short*) o, 0);
				}
			}
			p++;
		} while (--count);
		fcn_00546190(e);
		return;
	}
after:
	if (pc != 0) {
		o = (char*) fcn_00503fe0(*(int*) (e + 0xb0), 1, 1);
		if (o != 0) {
			fcn_004c5a60(*(int*) (o + 1), -1, *(int*) (pc + 2));
		}
	}
	fcn_00546190(e);
	return;
fail:
	*(int*) (e + 0x70) = -1;
	return;
}

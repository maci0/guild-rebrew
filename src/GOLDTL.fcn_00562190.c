// FUNCTION: GOLDTL 0x00562190
// SIZE: 780

#include <string.h>

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

typedef struct House {
	char pad0[0x21c];
} House;
// SIZE 0x21c

typedef struct Query {
	int kind;
	char pad4[0x220 - 4];
} Query;
// SIZE 0x220

extern struct pos14 g_7f4c00;
extern int g_6643d8[];
extern F8 g_666018;
extern House g_7f4ca0[];
extern char g_67ed14[];
extern char g_6a656c[];

unsigned char* __cdecl fcn_00508e40(int id);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_005015e0(char**, int, int, int);
int __cdecl fcn_004a5e60(House* h, int kind, F8 f, int c, float r, int* out);
int __cdecl fcn_004fa5b0(int k, House* h, Query* q);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);
int __cdecl fcn_004c5620(int, char*);

/* `close` is set in two if arms: one combined condition keeps it in a
 * register, three arms give it more slot weight than `o`. */
void __cdecl fcn_00562190(char* u)
{
	Query q;
	char* o;
	char* e;
	unsigned char* p;
	House* h;
	int close;
	int count;
	int r;

	close = 0;
	count = 0;
	if (u[0x78] & 4) {
		return;
	}
	*(int*) (u + 0xd8) = -1;
	p = fcn_00508e40(*(int*) (u + 0xc4));
	if (p == 0) {
		*(int*) (u + 0x84) = fcn_004c5620(-1, u);
		return;
	}
	*(int*) (u + 0xbc) = fcn_0042e410(0x100);
	*(int*) (u + 0xc0) = g_6643d8[fcn_0042e410(0x10)];
	*(int*) (u + 0xb8) = 0;
	*(int*) (u + 0xb4) = -1;
	*(struct pos14*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((struct pos14*) (u + 0x52), 0, 1, 0);
	for (e = fcn_005463a0(1, 0, 0x18); e != 0; e = fcn_005462a0()) {
		if (*(unsigned short*) (u + 8) == *(unsigned short*) (e + 8) && *(int*) (e + 4) != *(int*) (u + 4) && *(int*) (e + 0xc4) == *(int*) (u + 0xc4)) {
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
		if (*(int*) (e + 0xd8) != -1) {
			count++;
		}
	}
	fcn_005015e0(&o, 0, 0, *(int*) (u + 0xac));
	if (o == 0) {
		fcn_004a5e60(&g_7f4ca0[*(unsigned short*) (u + 8)], 6, g_666018, 0, 100.0f, (int*) (u + 0xac));
		fcn_005015e0(&o, 0, 0, *(int*) (u + 0xac));
		if (o == 0) {
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
	}
	memset(&q, 0, sizeof(q));
	q.kind = 1;
	h = &g_7f4ca0[*(unsigned short*) (u + 8)];
	*(struct pos14*) (u + 0x52) = g_7f4c00;
	*(struct pos14*) (u + 0xc8) = g_7f4c00;
	if (fcn_004fa5b0(0x26, h, &q) == 2) {
		fcn_00500bb0((struct pos14*) (u + 0xc8), (*(int*) (u + 0xe8) + 4) * 24, 0, 0);
	} else {
		fcn_00500bb0((struct pos14*) (u + 0xc8), (*(int*) (u + 0xe8) + 3) * 24, 0, 0);
	}
	if (((char*) h)[2] == 6) {
		close = 1;
	} else if (p[2] == 6 || p[2] == 7 || count < 8) {
		close = 1;
	}
	fcn_004c4eb0(g_67ed14);
	if (close != 0) {
		*(int*) (u + 0xd8) = fcn_004c64b0(0x11, *(int*) (o + 1), -1, 0, 0, 0, g_6a656c);
		r = fcn_004c5620(0, u);
	} else {
		*(struct pos14*) (u + 0x52) = *(struct pos14*) (u + 0xc8);
		r = fcn_004c5620(4, u);
	}
	*(int*) (u + 0x84) = r;
	fcn_004c4ef0(g_67ed14);
}

#include "client_types.h"

/* 0xf8-byte action packet sent through fcn_004c5530. */
typedef struct Msg553490 {
	int pad0;
	unsigned char type;
	char pad5[3];
	int seed;
	int id;
	char pad10[0x28 - 0x10];
	pos14_7f4c00 pos;
	unsigned char code;
	char pad37[0x58 - 0x37];
	int value;
	char pad5c[0xf8 - 0x5c];
} Msg553490;

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_004c5c80(int);
int __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
int __cdecl fcn_0050cf50(char*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x00553490 */
void __cdecl fcn_00553490(char* self)
{
	Msg553490 msg;
	char buf[0x200];
	char* p;
	char* ent;
	char* q;
	unsigned char kind;
	int state;
	int slotofs;
	int i;
	int step;

	p = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0xb0));
	ent = gm_LookupEntityRecordById(*(int*) (self + 0xac));
	state = *(int*) (self + 0x70);
	if (state == -1 || state == -2) {
		if (p != 0 && (*(unsigned char*) (self + 0x78) & 2)) {
			fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0, 0x100);
		}
		fcn_00546190(self);
		return;
	}
	step = 4;
	if (*(unsigned char*) (self + 0x78) & step) {
		return;
	}
	if (*(int*) (self + 0x84) != -1 && fcn_004c4450(*(int*) (self + 0x84)) == 0) {
		return;
	}
	*(int*) (self + 0x84) = -1;
	if (ent == 0 || p == 0 || *(unsigned short*) (p + 0x27) == 0xffff) {
		*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
		fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 0, 2, 0);
		*(int*) (self + 0x70) = -1;
		*(int*) (self + 0x84) = fcn_004c5620(-1, self);
		return;
	}
	switch (*(int*) (self + 0x70)) {
	case 1:
		fcn_00529160(p, 0, *(unsigned short*) ent, self);
		fcn_004c5c80(*(int*) (ent + 4));
		fcn_004c5da0(*(int*) (ent + 4), *(int*) (p + 1), -1, 0, 1, (char*) 0x6a5c24);
		*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
		fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 0, 10, 0);
		*(int*) (self + 0x70) = 2;
		*(int*) (self + 0x84) = fcn_004c5620(2, self);
		return;
	case 2:
		if (*(int*) (*(int*) (ent + 0x184) + 0x128) != 0) {
			*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
			fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 0, step, 0);
			*(int*) (self + 0x70) = 2;
			*(int*) (self + 0x84) = fcn_004c5620(2, self);
			return;
		}
		*(int*) (self + 0xb4) = (int) (fcn_0050cf50(p, 100) * *(float*) 0x665e98);
		slotofs = *(unsigned short*) (p + 0x27) * 0x21c;
		kind = *(unsigned char*) (slotofs + 0x7f4ca2);
		if (kind != 6 && kind != 7) {
			*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
			fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 0, (gm_RandomMod(0x10) & 0xffff) + 2, 0);
			*(int*) (self + 0x70) = 3;
			if (*(unsigned char*) (p + 0x5b) & 1) {
				*(int*) (self + 0xb8) = 2;
			} else {
				slotofs = *(unsigned short*) (p + 0x27) * 0x21c;
				if (*(unsigned char*) (slotofs + 0x7f4dd0) == 11 || *(float*) (slotofs + 0x7f4db4) * *(float*) 0x662a2c > gm_RandomFloat01()) {
					*(int*) (self + 0xb8) = 1;
				} else {
					*(int*) (self + 0xb8) = gm_RandomMod(2) & 0xffff;
				}
			}
			*(int*) (self + 0x84) = fcn_004c5620(3, self);
			return;
		}
		memset(&msg, 0, sizeof(msg));
		msg.id = *(int*) (p + 1);
		msg.seed = *(int*) (slotofs + 0x7f4ca4);
		msg.value = *(int*) (self + 4);
		msg.pos = (*(pos14_7f4c00*) &g_7f4c00);
		msg.type = 0x63;
		msg.code = 9;
		fcn_004c5530((char*) &msg);
		*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
		fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 3, 0, 0);
		*(int*) (self + 0x70) = 3;
		*(int*) (self + 0xb8) = 2;
		*(int*) (self + 0x84) = fcn_004c5620(3, self);
		return;
	case 3:
		if (*(int*) (self + 0xb8) == 1) {
			fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0x100, 0);
			fcn_004c51a0(*(int*) (*(unsigned short*) (self + 8) * 0x21c + 0x7f4ca4), *(int*) (*(unsigned short*) (p + 0x27) * 0x21c + 0x7f4ca4), 0, *(int*) (self + 0xb4));
			if (*(int*) (self + 0xbc) != -1) {
				q = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0xbc));
				*(int*) (q + 0x4d) = *(int*) (q + 0x4d) + *(int*) (self + 0xb4);
			}
			*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
			*(pos14_7f4c00*) (self + 0x44) = (*(pos14_7f4c00*) &g_7f4c00);
			fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 0x30, 0, 0);
			*(int*) (self + 0x70) = step;
			*(int*) (self + 0x84) = fcn_004c5620(step, self);
			io_FormatTextBuffer(buf, 0x1a8d, *(unsigned short*) (p + 0x27), p, *(int*) (self + 0xb4));
			i = *(int*) (*(unsigned short*) (self + 8) * 0x21c + 0x7f4ca4);
			fcn_00545d40(i, i, buf, 0, 0x5f3, (char*) 0x6a5c10);
			return;
		}
		if (*(int*) (self + 0xb8) != 0) {
			*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
			fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 0, 5, 0);
			*(int*) (self + 0x70) = step;
			*(int*) (self + 0x84) = fcn_004c5620(step, self);
			io_FormatTextBuffer(buf, 0x1a8f, *(unsigned short*) (p + 0x27), p);
			i = *(int*) (*(unsigned short*) (self + 8) * 0x21c + 0x7f4ca4);
			fcn_00545d40(i, i, buf, 0, 0x5f3, (char*) 0x6a5bfc);
			return;
		} else {
			*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
			fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 0, 5, 0);
			*(int*) (self + 0x70) = step;
			*(int*) (self + 0x84) = fcn_004c5620(step, self);
			io_FormatTextBuffer(buf, 0x1a8e, *(unsigned short*) (p + 0x27), p);
			i = *(int*) (*(unsigned short*) (self + 8) * 0x21c + 0x7f4ca4);
			fcn_00545d40(i, i, buf, 0, 0x5f3, (char*) 0x6a5bfc);
			return;
		}
	case 4:
		if (*(int*) (self + 0xb8) == 1) {
			io_FormatTextBuffer(buf, 0x1a90, p);
			i = *(int*) (*(unsigned short*) (self + 8) * 0x21c + 0x7f4ca4);
			fcn_00545d40(i, i, buf, 0, 0x5f3, 0);
			i = *(int*) (*(unsigned short*) (p + 0x27) * 0x21c + 0x7f4ca4);
			fcn_00545d40(i, i, buf, 0, 0x5f3, 0);
		}
		fcn_00529160(p, 0, *(unsigned short*) ent, 0);
		fcn_004c5c80(*(int*) (ent + 4));
		fcn_004c5da0(*(int*) (ent + 4), *(int*) (self + 0xbc), *(int*) (self + 0xc0), 0, 0, (char*) 0x6a5c24);
		*(pos14_7f4c00*) (self + 0x52) = (*(pos14_7f4c00*) &g_7f4c00);
		fcn_00500bb0((pos14_7f4c00*) (self + 0x52), 0, 2, 0);
		*(int*) (self + 0x70) = -1;
		*(int*) (self + 0x84) = fcn_004c5620(-1, self);
		return;
	}
}

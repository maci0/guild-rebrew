/* Native extent 0x005aacd0..0x005ac260 (5520 bytes; code ends with the tail
 * jmp at 0x005ac252 plus 9 filler bytes). chkstk frame 0x1a4c, no frame
 * pointer. Frame offsets below are from the bottom of the chkstk allocation:
 * [esp+N] with the four saved registers pushed is frame offset N-0x10. */

#include <string.h>

int __cdecl fcn_0052f390(int, int, int, int, int, int, int);
void __cdecl fcn_005350d0(int);
void __cdecl fcn_00576300(int, int, int, int);
int __cdecl fcn_00514400(int, int, int, void*);
int __cdecl fcn_0050dc90(void*);
void __cdecl fcn_00475f60(int, int);
int __cdecl fcn_00475b70(int, int, int);
void __cdecl fcn_00475ca0(int, int, int, int);
void __cdecl fcn_0046bc90(int, int, int, int, int, int, int);
int __cdecl fcn_00515990(int, ...);

typedef struct {
	int id;
	char type;
	char pad05[3];
	int f08;
	int f0c;
	int f10;
	char pad14[0x28 - 0x14];
	int f28;
	int f2c;
	int f30;
	short w34;
	char b36;
	short w38;
	char b3a;
	char pad3b[0x58 - 0x3b];
	int f58;
	int f5c[12];
	int f8c;
	char pad90[0xf8 - 0x90];
} MSG;

typedef struct {
	int type;
	int a04;
	int a08;
	int a0c;
	short a10;
	short a12;
	int a14;
	int a18;
	short a1c;
	short a1e;
	char a20;
	char pad21[3];
	int a24;
	char pad28[0x3c - 0x28];
	int a3c;
	char pad40[0x58 - 0x40];
	int a58;
} SEL;

typedef struct {
	int v00;
	int book;
	int v08;
	int v0c;
	int v10;
	char* row;
	int v18;
	int v1c;
	int v20;
	int v24;
	int v28;
	int v2c;
	int v30;
	int v34;
	int v38;
	int v3c;
	int v40;
	int v44;
	int v48;
	MSG msg;
	SEL sel;
	char rec2[0x54];
	char txt204[0x60];
	SEL rows[12];
	char gap6a4[0xbc];
	char txt760[0x50];
	char txt7b0[0x50];
	char txt800[0x1fc];
	char txt9fc[0x400];
	SEL rows2[12];
	char txt124c[0x400];
	char txt164c[0x400];
} FRAME;

/* ADDRESS: GOLD 0x005aacd0 */
int __cdecl fcn_005aacd0(unsigned char* a1, int a2, int a3)
{
	FRAME f;
	char* tbl;
	char* book;
	char* r;
	char* src;
	char* dst;
	char c;
	int t;

	t = *a1;
	f.sel.type = 0;
	memset(&f.sel.a04, 0, 0x58);
	f.v38 = 0;
	tbl = (char*) *(unsigned int*) 0x7e3f30 + t;
	f.v34 = -1;
	f.v48 = -1;
	f.v28 = -1;
	f.v1c = -1;
	f.v20 = -1;
	f.v44 = -1;
	f.v18 = -1;
	f.v40 = -1;
	f.v3c = -1;
	f.row = tbl + t * 0x24c;

	if (f.row[0] != 4 && f.row[0] != 0x13 && f.row[0] != 0x10) {
		book = (char*) fcn_0052f390(a2, 0x62537c, 4, 0x62cc04,
			0x62cc18, 0x62cc2c, 0x62cc40);
	} else {
		book = (char*) fcn_0052f390(a2, 0x62537c, 4, 0x62cbe4,
			0x62cc18, 0x62cc2c, 0x62cc40);
	}
	f.book = book;
	fcn_005350d0((int) book);
	fcn_00576300(0x21, (int) book, 0, 0);
	fcn_00514400(*(unsigned short*) (a1 + 0x27), 1, 2, f.txt7b0);
	fcn_00514400(*(unsigned short*) (a1 + 0x25), 1, 2, f.txt760);
	r = (char*) fcn_0050dc90(a1);
	if (r != 0) {
		fcn_00514400(*(unsigned short*) r, 1, 1, f.txt204);
	} else {
		src = *(char**) 0x1440ac8;
		dst = f.txt204;
		do {
			c = *src++;
			*dst++ = c;
		} while (c != 0);
	}
	fcn_00475f60(*(int*) (book + 0x228), 3);
	f.v40 = fcn_00475b70(*(int*) (book + 0x228), 3, 2);
	fcn_00475ca0(f.v40, 0x32, 0x96, *(int*) (a1 + 0x3d));
	if (f.row[0] != 4 && f.row[0] != 0x13 && f.row[0] != 0x10) {
		f.v44 = fcn_00475b70(*(int*) (book + 0x228), 3, 3);
		fcn_00475ca0(f.v44, 0, 4, *(int*) (a1 + 0x41));
		fcn_0046bc90(f.v44, 5, *(int*) 0x1440a78, *(int*) 0x1440a7c,
			*(int*) 0x1440a80, *(int*) 0x1440a84,
			*(int*) 0x1440a88);
	}
	fcn_00475f60(*(int*) (book + 0x228), 3);
	fcn_00515990(0x62cbe0);
	fcn_00515990(0x62cbe0);
	f.msg.f0c = fcn_00475b70(*(int*) (book + 0x228), 3, fcn_00515990(0x1a20));
	return 0;
}

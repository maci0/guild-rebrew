/* Pleite cutscene setup handler, 0x4e3020..0x4e32be (671 bytes).  Registered
 * with id 9 through fcn_004e7160 at 0x4e72b9; frame is a 0x22D0-byte local
 * block with two `add esp,0x22D0; ret` exits at 0x4e329c/0x4e32a2 and
 * 0x4e32b8/0x4e32be. */

typedef struct {
	char path[0x100];    /* 0x18 sprintf path buffer */
	char msg[0x200];     /* 0x118 message buffer */
	char big[0x1fb8];    /* 0x318 work buffer */
} Frame4e3020;

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_68bfb8;
extern int g_7725c8;
extern unsigned char g_7747b0;
extern int g_772f54;
extern int g_774954;
extern char g_5438c0[];
extern char g_67d444[];

int __cdecl gm_LookupEntityRecordById(void* p);
int __cdecl fcn_004c3100(char* s, int a);
void __cdecl fcn_004e4e90(char* s);
void __cdecl fcn_004e4730(char* s);
void __cdecl fcn_00445f50(int a, int b, float f, int c);
void __cdecl fcn_004463f0(int a, int b, float f);
void __cdecl fcn_004e4b60(char* s);
int __cdecl fcn_004e44b0(char* s, char* buf);
int __cdecl fcn_004e4d00(int a, int b, int c);
void __cdecl fcn_004e4b40(int a, int b, char* s, int c, int d);
void __cdecl fcn_004e4c40(int a);
int __cdecl io_FormatTextBuffer(char* buf, int a, int b);
int __cdecl fcn_004e6eb0(void* buf, int n);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4610(void* h);
void __cdecl fcn_004e44f0(void* h);
void __cdecl fcn_004e4c00(void);
void __cdecl fcn_004e4c60(void);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004c09b0(void);
void __cdecl fcn_004230e0(void* h);
void __cdecl fcn_004e4eb0(void);
void __cdecl fcn_005356b0(int p);
void __cdecl fcn_00509fc0(void* a, void* b, int c);
void __cdecl fcn_004e7160(void);

/* ADDRESS: GOLDTL 0x004e3020 */
void __cdecl fcn_004e3020(void* arg)
{
	int table[6];
	Frame4e3020 f;
	void* obj;
	int handle;
	int h2;
	int i;
	int state;
	int r;
	unsigned int mask;
	unsigned char flags;

	obj = (void*) gm_LookupEntityRecordById(*(void**) ((char*) arg + 0x34));
	mask = *(unsigned int*) 0x7f4c04;
	i = 0;
	table[0] = 8;
	table[1] = 0xa;
	table[2] = 0xc;
	table[3] = 0xf;
	table[4] = 0x12;
	table[5] = 0x14;
	state = 6;
	g_68bfb8 = 0x702c6;
	g_7725c8 = 1;	mask &= 0xffff;
	while (i < 6) {
		if ((int) mask < table[i]) {
			state = i;
			break;
		}
		i++;
	}
	handle = fcn_004c3100((char*) 0x68d324, 1);
	fcn_004e4e90((char*) 0x68bd2c);
	fcn_004e4730((char*) 0x68d318);
	fcn_00445f50(state, 0, 1.0f, 1);
	fcn_004463f0(0, 0, 0.0f);
	fcn_004e4b60((char*) 0x68d308);
	sprintf(f.path, g_67d444, state);
	h2 = fcn_004e44b0((char*) 0x68d2e4, f.path);
	r = fcn_004e4d00(0x1770, 0, 0);
	if (r == 0) {
		fcn_004e4b40(-8, handle, (char*) 0x68d2d8, 0, 0);
		fcn_004e4b40(-8, handle, (char*) 0x68d2d8, 1, 2500);
		fcn_004e4b40(-8, handle, (char*) 0x68d2d8, 2, 500);
		r = fcn_004e4d00(0x3e80, 0, 0);
		if (r == 0) {
			fcn_004e4c40(250);
			r = fcn_004e4d00(0x2af8, 0, 0);
			if (r == 0) {
				fcn_004e4b40(-8, handle, (char*) 0x68d2d8, 3, 0x251c);
				fcn_004e4b40(-8, handle, (char*) 0x68d2d8, 4, 0x1194);
				fcn_004e4b40(-8, handle, (char*) 0x68d2d8, 5, 500);
				fcn_004e4d00(0x5dc0, 0, 0);
			}
		}
	}
	flags = g_7747b0;
	g_7725c8 = 0;
	if ((flags & 4) != 0) {
		io_FormatTextBuffer(f.msg, 0x3fda, *(unsigned short*) obj);
	} else {
		io_FormatTextBuffer(f.msg, 0x1ab1, *(unsigned short*) obj);
	}
	fcn_004e6eb0(f.msg, 0);
	fcn_004e48b0();
	fcn_004e4610((void*) h2);
	fcn_004e44f0((void*) h2);
	fcn_004e4c00();
	fcn_004e4c60();
	fcn_004e4910();
	fcn_004c09b0();
	fcn_004230e0((void*) handle);
	fcn_004e4eb0();
	flags = g_7747b0;
	g_772f54 = 0;
	if ((flags & 8) != 0) {
		*(char*) ((char*) obj + 8) = 0;
		g_774954 = 1;
		fcn_005356b0(g_5438c0);
	} else {
		fcn_00509fc0(obj, f.big, 0);
	}
}

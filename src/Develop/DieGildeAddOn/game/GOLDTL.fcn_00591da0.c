


typedef struct
{
	int x0;
	int x4;
	int x8;
} Tip;
// SIZE 0xc

extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7746cc;
extern char* g_7e2aa0;
extern char* g_773d78;
#include "client_types.h"
extern Slot_779d00 g_779d00[];
extern char s_6a9b3c[];
extern char s_6a9b30[];

char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00533a40(char*);

void __cdecl fcn_00591da0(int a1)
{
	char buf[0x100];
	char* e;
	char* t;

	t = 0;
	e = g_7746c4;
	if (e != 0) {
		if (g_7746cc != 0) {
			t = g_7746cc;
		}
	} else {
		e = ((char*)g_7746c8);
		if (e != 0) {
			t = g_7746cc;
			if (t == 0) {
				t = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0xfd);
			}
		} else {
			e = g_7e2aa0;
			if (e == 0) {
				e = g_773d78;
			}
		}
	}
	if (t != 0) {
		((Tip*)g_779d00)[a1].x4 = *(int*) (e + 1);
		((Tip*)g_779d00)[a1].x8 = *(int*) (t + 2);
	} else {
		((Tip*)g_779d00)[a1].x4 = *(int*) (e + 1);
		((Tip*)g_779d00)[a1].x8 = -1;
	}
	if (t != 0 && *(unsigned short*) t != 0xfd) {
		io_FormatTextBuffer(buf, (int) s_6a9b30, a1 + 0x205e, e, *(unsigned short*) t * 2 + 0x9a8);
	} else {
		io_FormatTextBuffer(buf, (int) s_6a9b3c, a1 + 0x205e, e);
	}
	fcn_00533a40(buf);
}



extern char* g_773db4[];
extern unsigned char g_773d75;
#include "client_packet_builder.h"

int __cdecl fcn_004d0cd0(int* a);
void __cdecl fcn_004ce6e0(char* u);
int __cdecl fcn_004c51f0(int a, int b, int c, int d, char e, int f);
float __cdecl fcn_004ff210(unsigned short id, int delta);

int __cdecl fcn_004c4570(unsigned char size, unsigned char count, unsigned short off, unsigned char* src);
void __cdecl fcn_004c5360(void);

/* v is a separate local: c2 homes it in the dead slot of mode, and mode
 * stays a register load (an &mode argument would force byte reloads). */
void __cdecl fcn_004d1d40(char* obj, unsigned char mode)
{
	int i;
	unsigned char v;

	if (mode != 0) {
		*(int*) (obj + 0x110) = mode;
	}
	if (mode == 1) {
		i = fcn_004d0cd0((int*) (obj + 0x80));
		*(int*) (obj + 0x80 + i * 4) = *(int*) (g_773db4[i] + 4);
		fcn_004ce6e0(g_773db4[i]);
		fcn_004c51f0(*(int*) (g_773db4[i] + 4), -1, 0x156, 1, (*(char*)&g_773d75), 0);
		fcn_004ff210(*(unsigned short*) g_773db4[i], -*(int*) (g_773db4[i] + 0x24));
		v = 0xa8;
		fcn_004c4510(g_773db4[i], *(int*) (g_773db4[i] + 4));
		fcn_004c4570(1, 1, (unsigned short) (g_773db4[i] - g_aed32c + 0x83), &v);
		fcn_004c5360();
		i = fcn_004d0cd0((int*) (obj + 0x80));
		*(int*) (obj + 0x80 + i * 4) = *(int*) (g_773db4[i] + 4);
		fcn_004ce6e0(g_773db4[i]);
		fcn_004c51f0(*(int*) (g_773db4[i] + 4), -1, 0x156, 1, (*(char*)&g_773d75), 0);
		fcn_004ff210(*(unsigned short*) g_773db4[i], -*(int*) (g_773db4[i] + 0x24));
		v = 0xa8;
		fcn_004c4510(g_773db4[i], *(int*) (g_773db4[i] + 4));
		fcn_004c4570(1, 1, (unsigned short) (g_773db4[i] - g_aed32c + 0x83), &v);
		fcn_004c5360();
	}
	else if (mode == 2 || mode == 3) {
		i = fcn_004d0cd0((int*) (obj + 0x80));
		*(int*) (obj + 0x80 + i * 4) = *(int*) (g_773db4[i] + 4);
		fcn_004ce6e0(g_773db4[i]);
		fcn_004c51f0(*(int*) (g_773db4[i] + 4), -1, 0x158, 1, (*(char*)&g_773d75), 0);
		fcn_004ff210(*(unsigned short*) g_773db4[i], -*(int*) (g_773db4[i] + 0x24));
		v = 0xd2;
		fcn_004c4510(g_773db4[i], *(int*) (g_773db4[i] + 4));
		fcn_004c4570(1, 1, (unsigned short) (g_773db4[i] - g_aed32c + 0x83), &v);
		fcn_004c5360();
		i = fcn_004d0cd0((int*) (obj + 0x80));
		*(int*) (obj + 0x80 + i * 4) = *(int*) (g_773db4[i] + 4);
		fcn_004ce6e0(g_773db4[i]);
		fcn_004c51f0(*(int*) (g_773db4[i] + 4), -1, 0x160, 1, (*(char*)&g_773d75), 0);
		fcn_004ff210(*(unsigned short*) g_773db4[i], -*(int*) (g_773db4[i] + 0x24));
		v = 0xd2;
		fcn_004c4510(g_773db4[i], *(int*) (g_773db4[i] + 4));
		fcn_004c4570(1, 1, (unsigned short) (g_773db4[i] - g_aed32c + 0x83), &v);
		fcn_004c5360();
	}
}

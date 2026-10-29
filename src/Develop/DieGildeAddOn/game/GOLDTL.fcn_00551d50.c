#include <float.h>
#include <string.h>

extern float g_66413c;
extern float g_664168;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char s_6a5b74[];

int __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_00546190(void* u);
void __cdecl fcn_004c6ba0(int a1, int a2, int a3);
void __cdecl fcn_0051af00(char* out, int a2, int a3, int a4);
void __cdecl fcn_00545d40(int id, int arg, char* text1, unsigned char flags, int value, char* text2);
void __cdecl fcn_004c5530(void* packet);
void __cdecl fcn_004c6330(int id);
int __cdecl sprintf(char*, const char*, ...);

#pragma optimize("y", off)

/* Sends one behaviour event to the server when its delay has elapsed. */
/* ADDRESS: GOLDTL 0x00551d50 */
void __cdecl fcn_00551d50(char* a0)
{
	char buf[0x800];
	char packet[0xf8];
	char msg[0x30];
	char* table;
	char* row;
	int index;
	int delay;
	int byte;
	int id;

	if (*(int*) (a0 + 0x70) == -2) {
		fcn_00546190(a0);
		return;
	}
	if (*(int*) (a0 + 0x70) != 0) {
		return;
	}
	index = *(unsigned short*) (a0 + 8);
	byte = *(unsigned char*) (a0 + 0xae);
	delay = *(unsigned char*) (a0 + 0xac) - (gm_RandomMod(*(unsigned char*) (a0 + 0xad)) & 0xffff);
	row = (char*) (0x7f4ca0 + index * 0x21c);
	id = *(unsigned char*) (row + 0x80 + byte);
	if ((float) (id + delay) > g_66413c) {
		delay = (int) (g_66413c - (float) id);
	}
	fcn_004c6ba0(*(int*) (row + 4), byte, delay);
	if (*(unsigned char*) (row + 2) == 6) {
		byte = *(unsigned char*) (a0 + 0xae);
		id = *(unsigned char*) (row + 0x80 + byte);
		if ((int) ((float) (id + delay) * g_664168) <= (int) ((float) byte * g_664168)) {
			sprintf(msg, s_6a5b74, byte);
			fcn_0051af00(buf, 0x67728c, 0x16f2, byte + 0x16f3);
			fcn_00545d40(*(int*) (row + 4), *(int*) (row + 4), buf, 0, 0x5fd, msg);
		} else {
			memset(packet, 0, 0xf8);
			*(int*) (packet + 8) = *(int*) (row + 4);
			*(int*) (packet + 0xc) = -1;
			*(int*) (packet + 0x28) = g_7f4c00;
			*(int*) (packet + 0x2c) = g_7f4c04;
			*(int*) (packet + 0x30) = g_7f4c08;
			*(short*) (packet + 0x34) = g_7f4c0c;
			*(char*) (packet + 4) = 0x6a;
			*(char*) (packet + 0x36) = 9;
			*(char*) (packet + 0x58) = *(unsigned char*) (a0 + 0xae);
			*(int*) (packet + 0x5c) = (int) ((float) (id + delay) * g_664168);
			fcn_004c5530(packet);
		}
	}
	fcn_004c6330(*(int*) (row + 4));
	fcn_00546190(a0);
}

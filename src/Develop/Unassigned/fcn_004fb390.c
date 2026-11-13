#include "client_data.h"
extern float g_773d4c, g_773d50, g_99ec14, g_99f590[];
extern char g_99f5e0[];
void __cdecl fcn_004faed0(void*);
void __cdecl fcn_004c62c0(void*);
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x004fb390 */
void __cdecl fcn_004fb390(void)
{
	int buf[0x19];
	float sample;
	float slope;

	fcn_004faed0(buf);
	memcpy((void*) (g_99f5e0 + 0x0), buf, 0x28);
	if (g_773d4c == 0.0f) {
		sample = *(float*) &buf[5];
		g_773d50 = (float) sample;
		g_773d4c = *(float*) &buf[5] * 0.95;
	} else {
		sample = g_773d50 + (*(float*) &buf[5] - g_773d50) * 0.5f;
		g_773d50 = (float) sample;
	}
	*(float*) (g_99f5e0 + 0x14) = (float) sample;
	*(int*) (g_99f5e0 + 0x18) = *(int*) &g_773d4c;
	slope = (sample - g_773d4c) * 0.0007336182331406322;
	g_99ec14 = (float) slope;
	*(int*) g_99f590 = g_7f4c00.a;
	*(int*) ((char*) g_99f590 + 4) = g_7f4c00.b;
	*(int*) ((char*) g_99f590 + 8) = g_7f4c00.c;
	*(short*) ((char*) g_99f590 + 12) = g_7f4c00.d;
	*(int*) ((char*) buf + 0x28) = *(int*) (g_99f5e0 + 0x0);
	*(int*) ((char*) buf + 0x2c) = *(int*) (g_99f5e0 + 0x4);
	*(int*) ((char*) buf + 0x30) = *(int*) (g_99f5e0 + 0x8);
	*(int*) ((char*) buf + 0x34) = *(int*) (g_99f5e0 + 0xc);
	*(int*) ((char*) buf + 0x38) = *(int*) (g_99f5e0 + 0x10);
	*(float*) ((char*) buf + 0x3c) = (float) sample;

	*(int*) ((char*) buf + 0x40) = *(int*) &g_773d4c;
	*(int*) ((char*) buf + 0x44) = *(int*) (g_99f5e0 + 0x1c);
	*(int*) ((char*) buf + 0x48) = *(int*) (g_99f5e0 + 0x20);
	*(int*) ((char*) buf + 0x4c) = *(int*) (g_99f5e0 + 0x24);
	*(float*) ((char*) buf + 0x50) = (float) slope;
	*(int*) ((char*) buf + 0x54) = g_7f4c00.a;
	*(int*) ((char*) buf + 0x58) = g_7f4c00.b;
	*(int*) ((char*) buf + 0x5c) = g_7f4c00.c;
	*(short*) ((char*) buf + 0x60) = g_7f4c00.d;
	fcn_004c62c0((char*) buf + 0x28);
}

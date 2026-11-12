#include "client_data.h"
extern float g_773d4c, g_773d50, g_99ec14;
extern char g_99f5e0[];
void __cdecl fcn_004faed0(void*);
void __cdecl fcn_004c62c0(void*);
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x004fb390 */
void __cdecl fcn_004fb390(void)
{
	int buf[0x19];

	fcn_004faed0(buf);
	memcpy((void*) (g_99f5e0 + 0x0), buf, 0x28);
	if (g_773d4c == 0.0f) {
		g_773d50 = *(float*) &buf[5];
		g_773d4c = *(float*) &buf[5]
		    * 0.95;
		*(float*) (g_99f5e0 + 0x14) = *(float*) &buf[5];
	} else {
		g_773d50 = g_773d50
		    + (*(float*) &buf[5] - g_773d50)
		    * 0.5f;
		*(float*) (g_99f5e0 + 0x14) = g_773d50;
	}

	*(int*) (g_99f5e0 + 0x18) = *(int*) &g_773d4c;
	g_99ec14 = (*(float*) (g_99f5e0 + 0x14)
	    - g_773d4c) * 0.0007336182331406322;
	*(int*) 0x99f590 = g_7f4c00.a;
	*(int*) 0x99f594 = g_7f4c00.b;
	*(int*) 0x99f598 = g_7f4c00.c;
	*(short*) 0x99f59c = g_7f4c00.d;
	*(int*) ((char*) buf + 0x28) = *(int*) (g_99f5e0 + 0x0);
	*(int*) ((char*) buf + 0x2c) = *(int*) (g_99f5e0 + 0x4);
	*(int*) ((char*) buf + 0x30) = *(int*) (g_99f5e0 + 0x8);
	*(int*) ((char*) buf + 0x34) = *(int*) (g_99f5e0 + 0xc);
	*(int*) ((char*) buf + 0x38) = *(int*) (g_99f5e0 + 0x10);
	*(float*) ((char*) buf + 0x3c) = *(float*) (g_99f5e0 + 0x14);

	*(int*) ((char*) buf + 0x40) = *(int*) &g_773d4c;
	*(int*) ((char*) buf + 0x44) = *(int*) (g_99f5e0 + 0x1c);
	*(int*) ((char*) buf + 0x48) = *(int*) (g_99f5e0 + 0x20);
	*(int*) ((char*) buf + 0x4c) = *(int*) (g_99f5e0 + 0x24);
	*(float*) ((char*) buf + 0x50) = (*(float*) (g_99f5e0 + 0x14)
	    - g_773d4c) * 0.0007336182331406322;
	*(int*) ((char*) buf + 0x54) = g_7f4c00.a;
	*(int*) ((char*) buf + 0x58) = g_7f4c00.b;
	*(int*) ((char*) buf + 0x5c) = g_7f4c00.c;
	*(short*) ((char*) buf + 0x60) = g_7f4c00.d;
	fcn_004c62c0((char*) buf + 0x28);
}

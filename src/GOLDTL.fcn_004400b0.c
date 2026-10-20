#include <string.h>

extern char g_6b5c60[];

void* __cdecl m_alloc(int size, char* tag);
void __cdecl fcn_0043f7e0(int* obj, char* name, int flag);
void __cdecl fcn_0043f6b0(int* obj);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004400b0 */
int* __cdecl fcn_004400b0(int a0, char* a1, char* a2, char** a3, float a4, float a5)
{
	int* obj;
	char* p;
	int i;

	obj = (int*) m_alloc(0x8038, (char*) 0x67a950);
	obj[0] = a0;
	obj[3] = a0 - 1;
	obj[2] = (a0 * a0 - 1) | (a0 - 1);
	p = (char*) m_alloc(a0 * a0, (char*) 0x67a940);
	obj[4] = (int) p;
	memset(p, 0x20, a0 * a0);
	obj[5] = (int) m_alloc(a0 * a0, (char*) 0x67a87c);
	obj[0x21] = (int) a5;
	obj[1] = a0 / 8;
	*(float*) (obj + 0x14) = (float) (-a0) * a4 * *(float*) 0x6628cc;
	obj[0x18] = (int) a4;
	obj[0x19] = 0;
	obj[0x1a] = 0;
	*(float*) (obj + 0x15) = a5 * *(float*) 0x662cac;
	obj[0x1c] = 0;
	obj[0x1d] = 0;
	obj[0x20] = 0;
	obj[0x22] = 0;
	obj[0x2009] = 0x41a00000;
	obj[0x200a] = 0x42200000;
	((unsigned char*) obj)[0x8036] &= 0xe1;
	*(float*) (obj + 0x16) = (float) a0 * a4 * *(float*) 0x6628cc;
	*(float*) (obj + 0x1e) = -a4;
	p = (char*) obj + 0x7e24;
	for (i = 0; i < 8; i++) {
		*p = g_6b5c60[0];
		if (a3[i] != 0 && a3[i][0] != 0) {
			fcn_0043f7e0(obj, a3[i], -1);
		}
		p += 0x40;
	}
	strncpy((char*) obj + 0x7da4, a1, 0x40);
	strncpy((char*) obj + 0x7de4, a2, 0x40);
	fcn_0043f6b0(obj);
	return obj;
}

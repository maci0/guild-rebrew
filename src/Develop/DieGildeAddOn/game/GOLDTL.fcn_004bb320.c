#include <string.h>

unsigned char* __cdecl fcn_00508e40(int);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_004c6ba0(int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

#define MIN(a, b) ((a) < (b) ? (a) : (b))


/* ADDRESS: GOLDTL 0x004bb320 */
int __cdecl fcn_004bb320(int* a1)
{
	char buf[0x100];
	unsigned char* e;
	int k;
	int room;

	k = gm_RandomMod(5);
	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	room = 0xfc - e[k + 0x80];
	if (room <= 0)
		return 0x400;
	fcn_004c6ba0(*(int*) (e + 4), k, (char) MIN(room, gm_RandomMod(0x11) + 8));
	fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, k + 0x16b7);
	fcn_00545d40(*(int*) (e + 4), *(int*) (e + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}

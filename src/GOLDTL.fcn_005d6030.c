#include <string.h>

extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern int g_666018;
extern int g_66601c;

int __cdecl fcn_00508e40(unsigned int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_004c6ae0(int, int);
void __cdecl fcn_0051af00(char*, int);
int __cdecl fcn_005cd440(void*, char*, int, char*);

/* ADDRESS: GOLDTL 0x005d6030 */
/* Two dialog outcomes: the shop path builds a 0xf8-byte request record from
 * the owner id and four random-range globals; the quest path fills a
 * five-dword descriptor and looks up the record for id 0x1d66. */
int __cdecl fcn_005d6030(char* a0, char* a1)
{
	unsigned char rec[0xf8];
	unsigned int init[5];
	char name[64];
	int owner;
	int found;
	int id;

	if (*(unsigned char*) (a0 + 2) != 6 && *(unsigned char*) (a0 + 2) != 7) {
		found = fcn_00508e40(*(unsigned int*) (a1 + 0x214));
		if (found == 0) {
			return 0x60;
		}
		id = gm_RandomMod(9) + 0x1d6d;
		owner = gm_RandomMod(9) + 0x1d76;
		memset(rec, 0, sizeof(rec));
		*(int*) (rec + 8) = *(int*) (a0 + 4);
		*(int*) (rec + 0xc) = *(int*) (a0 + 4);
		*(int*) (rec + 0x58) = *(int*) (a0 + 4);
		*(char*) (rec + 4) = 0x47;
		*(int*) (rec + 0x28) = g_7f4c00;
		*(int*) (rec + 0x2c) = g_7f4c04;
		*(int*) (rec + 0x30) = g_7f4c08;
		*(unsigned short*) (rec + 0x34) = g_7f4c0c;
		*(char*) (rec + 0x36) = 2;
		*(int*) (rec + 0x5c) = *(int*) (found + 4);
		*(unsigned short*) (rec + 0x60) = (unsigned short) id;
		*(unsigned short*) (rec + 0x62) = (unsigned short) owner;
		fcn_004c5530(rec);
		fcn_004c6ae0(*(int*) (a0 + 4), -2);
		return 0x10;
	}
	memset(init, 0, sizeof(init));
	init[1] = 0x400;
	init[2] = g_666018;
	init[3] = g_66601c;
	init[4] = 6;
	fcn_0051af00(name, 0x1d66);
	found = fcn_005cd440(init, name, 0, (char*) 0x5d5d70);
	if (found != 0 && (*(unsigned int*) (found + 0x1c8) & 0x400) != 0) {
		return 0x81;
	}
	return 2;
}

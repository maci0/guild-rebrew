#include <string.h>

extern char g_99f6a0[];
extern int g_99f6e0;
extern int g_99f724;
extern int g_99f768;
extern int g_99f7ac;
extern int g_99f7f0;
extern int g_773d48;
extern unsigned char* lpGebaeudePROT;
extern char* lpGebaeudeINST;

void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);
int __cdecl fcn_004fcb50(unsigned short id, int* out, int c);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004fd780(void);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);

/* ADDRESS: GOLDTL 0x004fd280 */
void __cdecl fcn_004fd280(int flag)
{
	char* p;
	char* ent;
	int vals[8];
	int i;
	int n;

	fcn_0064d740(g_99f6a0, g_99f6a0 + 4, 0x40);
	fcn_0064d740(g_99f6a0 + 0x44, g_99f6a0 + 0x48, 0x40);
	fcn_0064d740(g_99f6a0 + 0x88, g_99f6a0 + 0x8c, 0x40);
	fcn_0064d740(g_99f6a0 + 0xcc, g_99f6a0 + 0xd0, 0x40);
	fcn_0064d740(g_99f6a0 + 0x110, g_99f6a0 + 0x114, 0x40);
	g_99f6e0 = 0;
	g_99f724 = 0;
	g_99f768 = 0;
	g_99f7ac = 0;
	g_99f7f0 = 0;
	g_773d48 = 0;
	i = 0;
	p = (char*) 0x7f4e38;
	{
		int out[0xe];

		do {
			fcn_004fcb50((unsigned short) i, out, flag);
			if (g_773d48 > 0x40) {
				fcn_00535960();
				g_773d48 = 0;
			}
			*(int*) (p + 4) = 0;
			*(int*) p = 0;
			p += 0x21c;
			i++;
		} while ((int) p < 0x85a238);
	}
	if ((flag & 1) != 0) {
		fcn_004fd780();
	}
	if ((flag & 1) != 0) {
		char* ptrs[8];

		ent = (char*) gm_StartFilteredEntitySearch(1, 5, 7);
		if (ent != 0) {
			i = 0;
			for (n = 0; n < 8; n++) {
				if (*(unsigned short*) (ent + 0x27) != 0xffff) {
					ptrs[n] = ent;
					vals[n] = lpGebaeudePROT[*(unsigned char*) ent * 0x24d + 0x247];
				}
				ent = (char*) gm_FindNextFilteredEntity();
				if (ent == 0) {
					break;
				}
			}
		}
	}
	p = lpGebaeudeINST;
	i = 0;
	do {
		*(int*) (p + i + 0x4d) = 0;
		p = lpGebaeudeINST;
		if (*(unsigned char*) (p + i) >= 0xb && *(unsigned char*) (p + i) <= 0xd) {
			*(int*) (p + i + 0x69) = 0;
		}
		i += 0xa9;
	} while (i < 0xa900);
}

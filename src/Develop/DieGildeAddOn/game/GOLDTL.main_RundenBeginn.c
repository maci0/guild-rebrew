/* Round-begin HUD refresh: walks the entity slot table and attaches the role,
 * action, office and building icons of each visible entity. */

int __cdecl fcn_0047dca0(void* slot);
int __cdecl gm_GetEntityTableEntry(void* slot);
int __cdecl gm_CheckStatLevel(int id, int index);
int __cdecl gm_GetOppositeStatIndex(int kind);
int __cdecl he_RegisterApEvent(int id, char* text, int kind, int arg);
int __cdecl fcn_005c6270(void* slot, int key);
void __cdecl fcn_004c5420(int a1, int a2, int a3, int a4, int a5);
void __cdecl fcn_0050e380(int id, char* out);
int __cdecl fcn_0050c710(int a1, int a2, int a3);
void* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_00546fb0(int id);
void __cdecl fcn_004c6ae0(int a1, int a2);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl fcn_00420bf0(void);
void __cdecl fcn_00420b70(void);
int __cdecl fcn_0064d41a(char* out, char* fmt, ...);

/* ADDRESS: GOLDTL 0x0053fc80 */
void __cdecl main_RundenBeginn(void)
{
	char bufA[256];
	char bufB[256];
	char bufC[256];
	char bufD[256];
	char bufE[256];
	char bufF[512];
	char bufG[512];
	char bufH[512];
	char disp[512];
	char* p;
	char* slot;
	int n;
	int i;
	int v5;
	int v18;

	bufA[0] = *(char*) 0x6b5c60;
	for (i = 1; i < 0x100; i++)
		bufA[i] = 0;
	fcn_00420bf0();
	fcn_00420b70();
	fcn_0064d41a(bufA, (char*) 0x6a42d0, *(int*) 0x774950);
	slot = (char*) 0x7f4ca0;
	do {
		if (*(short*) slot == -1)
			goto next;
		if (*(unsigned char*) (slot + 2) < 1 || *(unsigned char*) (slot + 2) > 8)
			goto next;
		if (*(int*) 0x14cbca0 != -1) {
			if (fcn_0047dca0(slot) == 0)
				goto next;
			if (*(int*) 0x14cbca0 != -1 && *(unsigned char*) (slot + 2) == 7)
				goto next;
		}
		if (*(unsigned char*) (slot + 2) == 6 || *(unsigned char*) (slot + 2) == 5) {
			v5 = gm_GetEntityTableEntry(slot);
			n = 0;
			do {
				i = gm_CheckStatLevel(*(unsigned short*) slot, n);
				if (gm_GetOppositeStatIndex(i) == 6) {
					io_FormatTextBuffer(bufF, 0x15c5, *(unsigned char*) (n + 0x74 + v5) + 0x130);
					p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufF, 1, 0);
					if (p)
						*p -= 1;
				}
				n++;
			} while (n < 0x11);
		}
		if (fcn_005c6270(slot, 0x2c1) != 0) {
			io_FormatTextBuffer(bufE, 0x2052, 0xf2a);
			p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufE, 6, 0);
			if (p)
				*p -= 1;
		}
		if (fcn_005c6270(slot, 0x15b) != 0) {
			io_FormatTextBuffer(bufD, 0x2052, 0xc5e);
			p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufD, 1, 0);
			if (p)
				*p -= 1;
		}
		v5 = fcn_005c6270(slot, 0x2c4);
		if (*(int*) (slot + 0x1cc) & 0x100000) {
			if (v5 == 0) {
				io_FormatTextBuffer(bufC, 0x2054, 0xf18);
				p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufC, -3, 0);
				if (p)
					*p -= 1;
			}
			fcn_004c5420(*(int*) (slot + 4), 0x1cc, 4, 0, 0x100000);
		}
		if (*(int*) (slot + 0x1cc) & 0x200000) {
			if (v5 == 0) {
				io_FormatTextBuffer(bufB, 0x2054, 0xf2c);
				p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufB, -8, 0);
				if (p)
					*p -= 1;
			}
			fcn_004c5420(*(int*) (slot + 4), 0x1cc, 4, 0, 0x200000);
		}
		fcn_0050e380(*(unsigned short*) slot, disp);
		if (*(int*) (slot + 0x170) != 0) {
			v5 = fcn_0050c710(*(int*) (slot + 0x170), 3, 1);
			if (v5 != 0) {
				io_FormatTextBuffer(bufH, 0x2053, *(int*) (slot + 0x170));
				p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufH, v5, 0);
				if (p)
					*p -= 1;
			}
		}
		p = (char*) gm_StartFilteredEntitySearch(2, 4, *(unsigned short*) slot, 5, 5);
		while (p != 0) {
			v18 = fcn_0050c710((int) p, 3, 1);
			if (v18 != 0) {
				io_FormatTextBuffer(bufG, 0x3fd7, p);
				n = (int) he_RegisterApEvent(*(unsigned short*) slot, bufG, v18, 0);
				if (n != 0)
					*(char*) n -= 1;
			}
			p = (char*) gm_FindNextFilteredEntity();
		}
		fcn_004c6ae0(*(int*) (slot + 4),
			*(int*) (disp + 0x31) + 4 + fcn_00546fb0(*(unsigned short*) slot));
next:
		slot += 0x21c;
	} while ((int) slot <= (int) 0x85a0a1);
}

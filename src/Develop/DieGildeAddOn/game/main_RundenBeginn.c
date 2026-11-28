extern char g_85a0a2[];
extern char str_empty[];
extern char g_774950[];
extern char gm_SlotTableKindView[];
extern char nt_ClientSocket[];
/* Round-begin HUD refresh: walks the entity slot table and attaches the role,
 * action, office and building icons of each visible entity. */

int __cdecl gm_IsLocalSimEntity(void* slot);
int __cdecl gm_GetEntityTableEntry(void* slot);
int __cdecl gm_CheckStatLevel(int id, int index);
int __cdecl gm_GetOppositeStatIndex(int kind);
int __cdecl he_RegisterApEvent(int id, char* text, int kind, int arg);
int __cdecl gm_HasActiveSpecialObject(void* slot, int key);
void __cdecl cm_RequestChangeBits(int a1, int a2, int a3, int a4, int a5);
void __cdecl gm_BuildDealSummary(int id, char* out);
int __cdecl gm_GetBuildingTechEffect(int a1, int a2, int a3);
void* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl he_SumEventValuesForSubject(int id);
void __cdecl cm_RequestModifyHealth(int a1, int a2);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl nt_FormatPacketStats(void);
void __cdecl nt_ResetPacketStats(void);
int __cdecl fcn_0064d41a(char* out, char* fmt, ...);

/* ADDRESS: GOLDTL 0x0053fc80 */
/* ADDRESS: GOLDDE 0x00526790 */
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
	char disp[544];
	char* p;
	char* slot;
	char* slot2;
	int n;
	int i;
	int v5;
	int eventValue;
	int tmp;

	bufA[0] = *(char*) &str_empty;
	for (i = 1; i < 0x100; i++)
		bufA[i] = 0;
	nt_FormatPacketStats();
	nt_ResetPacketStats();
	fcn_0064d41a(bufA, "main_RundenBeginn(): init round no %i", *(int*) &g_774950);
	slot2 = (char*) &gm_SlotTableKindView;
	do {
		if (*(unsigned short*) (slot2 - 2) == 0xffff)
			goto next;
		slot = slot2 - 2;
		if (*(unsigned char*) slot2 < 1 || *(unsigned char*) slot2 > 8)
			goto next;
		if (*(int*) &nt_ClientSocket != -1) {
			if (gm_IsLocalSimEntity(slot) == 0)
				goto next;
			if (*(int*) &nt_ClientSocket != -1 && *(unsigned char*) slot2 == 7)
				goto next;
		}
		if (*(unsigned char*) slot2 == 6 || *(unsigned char*) slot2 == 5) {
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
		if (gm_HasActiveSpecialObject(slot, 0x2c1) != 0) {
			io_FormatTextBuffer(bufE, 0x2052, 0xf2a);
			p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufE, 6, 0);
			if (p)
				*p -= 1;
		}
		if (gm_HasActiveSpecialObject(slot, 0x15b) != 0) {
			io_FormatTextBuffer(bufD, 0x2052, 0xc5e);
			p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufD, 1, 0);
			if (p)
				*p -= 1;
		}
		v5 = gm_HasActiveSpecialObject(slot, 0x2c4) != 0;
		if (*(int*) (slot + 0x1cc) & 0x100000) {
			if (v5 == 0) {
				io_FormatTextBuffer(bufC, 0x2054, 0xf18);
				p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufC, -3, 0);
				if (p)
					*p -= 1;
			}
			cm_RequestChangeBits(*(int*) (slot + 4), 0x1cc, 4, 0, 0x100000);
		}
		if (*(int*) (slot + 0x1cc) & 0x200000) {
			if (v5 == 0) {
				io_FormatTextBuffer(bufB, 0x2054, 0xf2c);
				p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufB, -8, 0);
				if (p)
					*p -= 1;
			}
			cm_RequestChangeBits(*(int*) (slot + 4), 0x1cc, 4, 0, 0x200000);
		}
		gm_BuildDealSummary(*(unsigned short*) slot, disp);
		if (*(int*) (slot + 0x170) != 0) {
			v5 = gm_GetBuildingTechEffect(*(int*) (slot + 0x170), 3, 1);
			if (v5 != 0) {
				io_FormatTextBuffer(bufH, 0x2053, *(int*) (slot + 0x170));
				p = (char*) he_RegisterApEvent(*(unsigned short*) slot, bufH, v5, 0);
				if (p)
					*p -= 1;
			}
		}
		p = (char*) gm_StartFilteredEntitySearch(2, 4, *(unsigned short*) slot, 5, 5);
		while (p != 0) {
			eventValue = gm_GetBuildingTechEffect((int) p, 3, 1);
			if (eventValue != 0) {
				io_FormatTextBuffer(bufG, 0x3fd7, p);
				n = (int) he_RegisterApEvent(*(unsigned short*) slot, bufG, eventValue, 0);
				if (n != 0)
					*(char*) n -= 1;
			}
			p = (char*) gm_FindNextFilteredEntity();
		}
		tmp = *(int*) (disp + 0x31) + 4;
		tmp += he_SumEventValuesForSubject(*(unsigned short*) slot);
		cm_RequestModifyHealth(*(int*) (slot + 4), tmp);
next:
		slot2 += 0x21c;
	} while ((int) slot2 < (int) (int) &g_85a0a2);
}

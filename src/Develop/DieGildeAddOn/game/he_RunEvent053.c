#include "Develop/client_types.h"

extern unsigned char gm_ActiveTownIndex;
extern float flt_0_01;
extern char gm_CityDisplayNames[];






void __cdecl he_FreeAction(void*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl gm_RandomMod(int);
int __cdecl ai_FindEntityInFavorRange(unsigned short*, int, int, int, float, float, int*);
void __cdecl gm_ResolveEntityById(void**, void**, void**, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x005505b0 */
void __cdecl he_RunEvent053(int a)
{
	char buf[0x800];
	char msg[0x200];

	char* p;
	char* q;
	int id;
	int found;
	int n;



	if (*(int*) (a + 0x70) == -2) {
		he_FreeAction((void*) a);
		return;
	}
	io_FormatTextBuffer(buf, 0x10c2, gm_CityDisplayNames + (unsigned char) gm_ActiveTownIndex * 0x2f4, (gm_RandomMod(3) & 0xffff) + 0x10c4);
	id = 0;
	q = (char*) 0x7f4ca2;
	do {
		p = q - 2;
		if (*(short*) p != -1 && *(unsigned char*) (p + 8) >= 2
		    && (*(char*) (p + 2) == 6 || *(char*) (p + 2) == 7 || *(char*) (p + 2) == 5)) {
			if (ai_FindEntityInFavorRange((unsigned short*) p, 4, 0x400080, 0, 0.0f, 100.0f, &found)) {
				gm_ResolveEntityById((void**) &id, 0, 0, found);
			}
			if (*(char*) (p + 2) == 6 || *(char*) (p + 2) == 7) {
				he_PostEntityMessage(*(int*) (p + 4), -1, buf, 0x20, 0x601, 0);
			}
			if (id != 0) {
				n = (int) ((double) gm_WalkEntityChain(*(unsigned short*) p) * flt_0_01);
				n *= (gm_RandomMod(4) & 0xffff) + 2;
				cm_RequestTransferCurrencyNoKill(*(int*) (p + 4), -1, (unsigned char) gm_ActiveTownIndex, n);
				if (*(char*) (p + 2) == 6 || *(char*) (p + 2) == 7) {
					io_FormatTextBuffer(msg, 0x10c3, id, n);
					he_PostEntityMessage(*(int*) (p + 4), -1, msg, 0, 0x5ff, 0);
				}
			}
		}
		q += 0x21c;
		id = 0;
	} while ((int) q < 0x85a0a2);
	he_FreeAction((void*) a);
}

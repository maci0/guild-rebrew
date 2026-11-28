extern char gm_MarketStockTable[];
extern char g_662908[];
extern char g_6628f0[];
extern char* lpObjektePROT;
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
char* __cdecl gm_FindCityItemHolder(int id);
double __cdecl fcn_0042e450(char a, int b);
void __cdecl cm_SendSellObjekt(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x00515340 */
/* ADDRESS: GOLDDE 0x004ffdb0 */
void __cdecl gm_RestockTownMarket(int idx)
{
	char* rec;
	char* p;
	int i;
	int h;

	rec = (char*) &gm_MarketStockTable + idx * 0x2a90;
	i = 0x55;
	do {
		p = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) rec]);
		h = (int) gm_FindCityItemHolder(*(unsigned short*) rec);
		if (h != 0) {
			if (*(unsigned char*) p == 0x17 || *(unsigned char*) p == 0x25) {
				cm_SendSellObjekt(*(int*) (h + 2), -1, *(unsigned short*) rec,
				    (int) ((fcn_0042e450((char) gm_ActiveTownIndex, 0) + *(double*) &g_662908)
				    * *(float*) (rec + 0x20)));
			} else {
				cm_SendSellObjekt(*(int*) (h + 2), -1, *(unsigned short*) rec,
				    (int) ((fcn_0042e450((char) gm_ActiveTownIndex, 0) + *(double*) &g_6628f0)
				    * *(float*) (rec + 0x20)));
			}
		}
		rec += 0x80;
		i--;
	} while (i != 0);
}

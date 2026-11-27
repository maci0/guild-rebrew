#include "client_town.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern char* lpObjektePROT;
extern int __cdecl gm_CalcTownSlotTargetStock(int a, int b);
extern int __cdecl gm_CalcTownSlotProductionSupply(int a, int b);
extern float __cdecl eval_ObjektPreis2Credits(int a, int b);

/* ADDRESS: GOLDTL 0x005016f0 */
void __cdecl gm_InitTownGoodsTable(int which)
{
	char* def;
	char* dst;
	unsigned char kind;
	int i;

	i = 0;
	dst = (char*) 0x85abc0 + which * 0x2a90;
	do {
		def = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) (dst - 0x30)]); *(int*) (dst - 0x24) = *(int*) (0x696608 - 0x24 + i * 0x80);
		*(int*) dst = *(int*) (0x696608 + i * 0x80);
		kind = *def;
		if (kind != 0x17 && kind != 0x25) {
			*(float*) (dst - 0x10) = (float) gm_CalcTownSlotTargetStock(which, i);
		} else {
			*(int*) (dst + 4) = gm_CalcTownSlotProductionSupply(which, i);
		}
		*(float*) (dst + 8) = eval_ObjektPreis2Credits(*(unsigned short*) (dst - 0x30), 100);
		*(int*) (dst - 0xc) = *(int*) (dst - 0x10);
		i++;
		dst += 0x80;
	} while (i < 0x55);
}

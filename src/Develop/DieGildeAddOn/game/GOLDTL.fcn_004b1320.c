#include <string.h>
#include <stdlib.h>
#include "game_data.h"
#include "Develop/DieGildeAddOn/game/season_slots.h"
/* SIZE 0x80 */
typedef struct {
	unsigned short id;
	char pad2[2];
	int active;
	char pad8[0x20 - 8];
	float base;
	float price;
	char pad28[0x38 - 0x28];
	float value;
	char pad3c[0x80 - 0x3c];
} Ent80;

extern char g_85ab90[];
extern char* lpObjektePROT;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
int __cdecl fcn_0064eeec(char*);
char* __cdecl fcn_004ce590(int);
float __cdecl eval_ObjektPreis2Credits(int, int);
void __cdecl fcn_004c6190(char*, char);

/* ADDRESS: GOLDTL 0x004b1320 */
int __cdecl fcn_004b1320(int a1, int a2, char* argumentText)
{
	float f;
	float factor;

	if (*argumentText != '-')
		return 0;
	{
		int sign[2] = { -1, 1 };
		char names[2][6] = { "MINUS", "PLUS" };
		char cats[3][12] = { "WAFFEN", "BUECHER", "ENDPRODUKTE" };
		Ent80 copy;
		int amount;
		int i;
		int j;
		char* row;
		char* p;

		argumentText++;
		for (i = 0; i < 2; i++) {
			if (memcmp(argumentText, names[i], strlen(names[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		sign[0] = sign[i];
		argumentText += strlen(names[i]);
		if (*argumentText != '_')
			return 0;
		argumentText++;
		for (j = 0; j < 3; j++) {
			if (memcmp(argumentText, cats[j], strlen(cats[j])) == 0)
				break;
		}
		if (j >= 3)
			return 0;
		argumentText += strlen(cats[j]);
		if (*argumentText != '_')
			return 0;
		argumentText++;
		amount = atoi(argumentText) * sign[0];
		{
			factor = amount * 0.01;
			switch (j) {
			case 0: {
				for (i = 0; i < 0x2a80; i += 0x80) {
					row = g_85ab90 + g_773d75 * 0x2a90 + i;
					if (((MARKET_STOCK_SLOT*)row)->objekt_id == 0)
						continue;
					if (((MARKET_STOCK_SLOT*)row)->active == 0)
						continue;
					p = fcn_004ce590(((MARKET_STOCK_SLOT*)row)->objekt_id);
					if (p == 0 || *(int*) p == 0)
						continue;
					f = factor + 1.0f;
					copy = *(Ent80*)((MARKET_STOCK_SLOT*)(g_85ab90 + g_773d75 * 0x2a90 + i));
					copy.price = copy.base * (factor + 1.0f);
					copy.value = eval_ObjektPreis2Credits(((MARKET_STOCK_SLOT*)row)->objekt_id, 0x64) * f;
					fcn_004c6190((char*) &copy, g_773d75);
				}
				return 1;
			}
			case 1: {
				for (i = 0; i < 0x2a80; i += 0x80) {
					row = g_85ab90 + g_773d75 * 0x2a90 + i;
					if (((MARKET_STOCK_SLOT*)row)->objekt_id == 0)
						continue;
					if (((MARKET_STOCK_SLOT*)row)->active == 0)
						continue;
					if (*(char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[((MARKET_STOCK_SLOT*)row)->objekt_id].kind != 8)
						continue;
					f = factor + 1.0f;
					copy = *(Ent80*) row;
					copy.price = copy.base * (factor + 1.0f);
					copy.value = eval_ObjektPreis2Credits(((MARKET_STOCK_SLOT*)row)->objekt_id, 0x64) * f;
					fcn_004c6190((char*) &copy, g_773d75);
				}
				return 1;
			}
			case 2: {
				for (i = 0; i < 0x2a80; i += 0x80) {
					row = g_85ab90 + g_773d75 * 0x2a90 + i;
					if (((MARKET_STOCK_SLOT*)row)->objekt_id == 0)
						continue;
					if (((MARKET_STOCK_SLOT*)row)->active == 0)
						continue;
					if (*(char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[((MARKET_STOCK_SLOT*)row)->objekt_id].kind != 0x20)
						continue;
					f = factor + 1.0f;
					copy = *(Ent80*) row;
					copy.price = copy.base * (factor + 1.0f);
					copy.value = eval_ObjektPreis2Credits(((MARKET_STOCK_SLOT*)row)->objekt_id, 0x64) * f;
					fcn_004c6190((char*) &copy, g_773d75);
				}
			}
			}
		}
	}
	return 1;
}

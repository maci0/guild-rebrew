#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* g_entity_ptr;
extern char* gm_MarketEntity;
int __cdecl gm_QueryEntities(int, ...);
int __cdecl gm_FindCityItemHolder(int);
int __cdecl gm_GetStorageSlotCapacity(int, int);
int __cdecl gm_GetMsgField(int, int);
float __cdecl gm_GetSeasonPrice(int id, unsigned char a);

/* ADDRESS: GOLDTL 0x00503a70 */
/* ADDRESS: GOLDDE 0x004eedf0 */
int __cdecl gm_CollectItemSuppliers(int itemId)
{
	char* p;
	int count;
	int n;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int t;
	float f;
	int tmp[6];

	if (!lpGebaeudePROT) {
		return 1;
	}
	*(int*) 0x86805c = 0;
	n = 0x58;
	p = (char*) g_entity_ptr;
	do {
		v5 = itemId;
		if (*p) {
			v4 = 0;
			count = *(int*) 0x86805c * 0x18;
			*(int*) (count + 0x868c40) = 0;
			*(int*) (count + 0x868c48) = 0;
			*(int*) (count + 0x868c54) = 0;
			if (p == gm_MarketEntity) {
				v6 = gm_FindCityItemHolder(itemId);
				if (v6) {
					v7 = gm_QueryEntities(*(int*) (v6 + 0x14), 1, 0, v5);
					if (v7) {
						count = *(int*) 0x86805c * 0x18;
						*(char**) (count + 0x868c40) = p;
						*(int*) (count + 0x868c44) = v6;
						*(void**) (count + 0x868c48) = (void*) v7;
						v3 = *(unsigned short*) v7;
add:
						v8 = gm_GetStorageSlotCapacity(v6, v3);
						v9 = gm_GetMsgField(v6, v7);
						t = *(int*) (v7 + 0x1c);
						v9 = v9 - ((unsigned int) (v8 * t) >> 2);
						*(int*) (*(int*) 0x86805c * 0x18 + 0x868c4c) = v9;
						if ((int) v9 < 0) {
							v9 = 0;
						}
						*(int*) (*(int*) 0x86805c * 0x18 + 0x868c4c) = v9;
						*(int*) 0x86805c = *(int*) 0x86805c + 1;
					}
				}
			}
			else {
				v7 = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0xff);
				if (v7) {
					v7 = gm_QueryEntities(*(int*) (v7 + 0x14), 1, 0, itemId);
					if (v7) {
						v4 = 1;
						*(char**) (*(int*) 0x86805c * 0x18 + 0x868c40) = p;
						*(int*) (*(int*) 0x86805c * 0x18 + 0x868c54) = 1;
					}
				}
				v6 = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x2a);
				if (v6) {
					v7 = gm_QueryEntities(*(int*) (v6 + 0x14), 1, 0, itemId);
					if (v7) {
						count = *(int*) 0x86805c * 0x18;
						*(char**) (count + 0x868c40) = p;
						*(int*) (count + 0x868c44) = v6;
						*(void**) (count + 0x868c48) = (void*) v7;
						v3 = *(unsigned short*) v7;
						goto add;
					}
				}
				if (v4) {
					*(int*) 0x86805c = *(int*) 0x86805c + 1;
				}
			}
		}
		p += 0xa9;
		n--;
		if (!n) {
			break;
		}
	} while (1);
	v6 = 0;
	if (*(int*) 0x86805c > 0) {
		p = (char*) 0x868c50;
		do {
			f = gm_GetSeasonPrice(itemId, *(unsigned char*) 0x773d75);
			v6++;
			*(float*) p = f * *(float*) (*(int*) (p - 0x10) + 0x49);
			p += 0x18;
		} while (v6 < *(int*) 0x86805c);
	}
	count = *(int*) 0x86805c;
	if (count <= 0) {
		goto fail_0;
	}
	v4 = 1;
	v5 = 0;
	do {
		if (v4 < count) {
			v7 = v5 + 0x868c58;
			n = count - v4;
			do {
				if (*(float*) (v5 + 0x868c50) < *(float*) (v7 + 0x10)) {
					memcpy(tmp, (void*) (v5 + 0x868c40), 0x18);
					memcpy((void*) (v5 + 0x868c40), (void*) v7, 0x18);
					memcpy((void*) v7, tmp, 0x18);
				}
				v7 += 0x18;
				n--;
			} while (n);
		}
		v4++;
		v5 += 0x18;
	} while (v4 - 1 < count);
	goto fail_0;
fail_0:
	return 0;
}




extern unsigned char gm_ActiveTownIndex;

unsigned short* __cdecl gm_QueryEntities(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_LookupWeaponSpec(int);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);

/* ADDRESS: GOLDDE 0x004bbe80 */
void __cdecl gm_RemoveSpecialTableItems(char* entity)
{
	unsigned short* p;
	int id;

	for (p = gm_QueryEntities(*(int*) (entity + 0x178), 1, 5); p != 0; p = gm_NextEntityQueryMatch()) {
		id = *p;
		if (gm_LookupWeaponSpec(id) != 0) {
			cm_SendSellObjekt(-1, *(int*) (entity + 4), id, *(int*) ((char*) p + 0xe), (*(char*)&gm_ActiveTownIndex), 0);
		}
	}
}

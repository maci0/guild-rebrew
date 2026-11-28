extern unsigned char gm_ActiveTownIndex;
extern char gm_EntitySlotTable[][0x21c];

typedef struct {
	unsigned short id;
	unsigned char type;
	char pad[0x21c - 3];
} OWNER_HEADER_STUB;

int __cdecl fcn_0050d2a0(void*);
int __cdecl gm_QueryEntities(int, int, ...);
int __cdecl fcn_00502850(void);
float __cdecl gm_GetSeasonPrice(int id, unsigned char a);

/* ADDRESS: GOLDTL 0x0050d0c0 */
int __cdecl gm_CalcOwnerAndStockValue(char* bld, int flag)
{
	char* unused;
	char* slot;
	unsigned int i;
	int val;

	val = 0;
	if (*(unsigned short*) (bld + 0x27) != 0xffff) {
		i = *(unsigned short*) (bld + 0x27);
		if ((unsigned char) gm_EntitySlotTable[i][2] < 0xa) {
			val = fcn_0050d2a0(gm_EntitySlotTable[i]);
		}
	}
	if (flag != 0) {
		slot = (char*) gm_QueryEntities(*(int*) (bld + 0x5d), 2, 6, 0, 0x2a);
		if (slot != 0) {
			slot = (char*) gm_QueryEntities(*(int*) (slot + 0x14), 1, 5);
			if (slot != 0) {
				do {
					val = (int) (gm_GetSeasonPrice(*(unsigned short*) slot,
					                          gm_ActiveTownIndex)
					             + (float) val);
					slot = (char*) fcn_00502850();
				} while (slot != 0);
			}
		}
	}
	return val;
}

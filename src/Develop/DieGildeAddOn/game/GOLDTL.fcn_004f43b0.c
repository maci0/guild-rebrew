


extern char* gm_CityEntity;

int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
unsigned char* __cdecl FindSlotEntryFiltered(int a, char* e, unsigned char* prev, void* filter, int mask);
int __cdecl fcn_004f1850(void);

unsigned char* __cdecl gv_FindLowestCostSlot(char* building, unsigned char lim)
{
	unsigned char* best;
	unsigned char* entry;

	best = 0;
	if (*(unsigned short*) (building + 0x27) == 0xffff || *(unsigned short*) (building + 0x27) == *((unsigned short*)gm_CityEntity)) {
		return 0;
	}
	if (!fcn_00502cd0(*(int*) (building + 0x5d), 2, 4, 0x1f8, 6)) {
		return 0;
	}
	entry = FindSlotEntryFiltered(0, building, best, (void*) fcn_004f1850, 0xff);
	while (entry != 0) {
		if (entry[0xc] < lim && (best == 0 || entry[0xc] < best[0xc])) {
			best = entry;
		}
		entry = FindSlotEntryFiltered(0, building, entry, (void*) fcn_004f1850, 0xff);
	}
	return best;
}

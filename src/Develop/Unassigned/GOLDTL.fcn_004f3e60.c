#pragma pack(push, 1)
typedef struct GV_BUILDING_CAP_VIEW {
	unsigned char kind;
	char pad1[0x230];
	unsigned char b231;
	unsigned char b232;
	char pad233[0x24d - 0x233];
} GV_BUILDING_CAP_VIEW;
#pragma pack(pop)
// SIZE 0x24d

extern unsigned char* lpGebaeudePROT;
extern char g_7f4ca0[];

/* ADDRESS: GOLDTL 0x004f3e60 */
int __cdecl gv_CanHireGraveyardWorker(unsigned char* building, int* count)
{
	GV_BUILDING_CAP_VIEW* proto;
	int cap;
	int workerCount;
	int entryPtr;

	proto = &((GV_BUILDING_CAP_VIEW*)lpGebaeudePROT)[*building];
	if (proto->kind != 0x1d) {
		return -1;
	}
	if (*(int*) (building + 0x65) == 0) {
		return -1;
	}
	cap = proto->b232 + proto->b231;
	workerCount = 0;
	for (entryPtr = (int) (g_7f4ca0 + 0x16c); entryPtr < (int) (g_7f4ca0 + 0x16c + 0x65400); entryPtr += 0x21c) {
		if (*(unsigned short*) (entryPtr - 0x16c) != 0xffff && *(char*) (entryPtr - 0x16a) == 0x14 && *(unsigned char**) entryPtr == building) {
			workerCount++;
		}
	}
	if (count != 0) {
		*count = workerCount;
	}
	return workerCount < cap;
}

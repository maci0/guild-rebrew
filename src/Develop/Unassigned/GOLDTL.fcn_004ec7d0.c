


typedef struct
{
	char type;
	char pad[0x24c];
} Tile;
// SIZE 0x24d

extern unsigned char* lpGebaeudePROT;

void* __cdecl gm_LookupEntityRecordById(int);

void* __cdecl fcn_004ec7d0(unsigned char* a1)
{
	int* idPtr;

	if (((Tile*)lpGebaeudePROT)[a1[0]].type == 0x1e) {
		idPtr = *(int**) (a1 + 0x65);
		if (idPtr != 0) {
			return gm_LookupEntityRecordById(*idPtr);
		}
	}
	return 0;
}

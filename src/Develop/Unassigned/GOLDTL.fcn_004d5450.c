


typedef struct
{
	char type;
	char pad[0x24c];
} Tile;
// SIZE 0x24d

extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_004d5450(unsigned char* a1)
{
	Tile* tile;

	tile = &((Tile*)lpGebaeudePROT)[a1[0]];
	if (tile->type == 0x13) {
		return 0;
	}
	if (tile->type == 0x10) {
		return 1;
	}
	return tile->type == 4 ? 2 : 0;
}

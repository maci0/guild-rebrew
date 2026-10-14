


typedef struct
{
	char type;
	char pad[0x24c];
} Tile;
// SIZE 0x24d

extern unsigned char* g_868050;

void* __cdecl fcn_00508e40(int);

void* __cdecl fcn_004ec7d0(unsigned char* a1)
{
	int* p;

	if (((Tile*)g_868050)[a1[0]].type == 0x1e) {
		p = *(int**) (a1 + 0x65);
		if (p != 0) {
			return fcn_00508e40(*p);
		}
	}
	return 0;
}

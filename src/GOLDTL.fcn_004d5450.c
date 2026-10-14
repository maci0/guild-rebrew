


typedef struct
{
	char type;
	char pad[0x24c];
} Tile;
// SIZE 0x24d

extern unsigned char* g_868050;

int __cdecl fcn_004d5450(unsigned char* a1)
{
	Tile* t;

	t = &((Tile*)g_868050)[a1[0]];
	if (t->type == 0x13) {
		return 0;
	}
	if (t->type == 0x10) {
		return 1;
	}
	return t->type == 4 ? 2 : 0;
}

#pragma pack(push, 1)
typedef struct {
	unsigned char kind;
	char pad[0x40];
} Obj5013c0;
#pragma pack(pop)
// SIZE 0x41

extern char* g_99ec10;

// FUNCTION: GOLDTL 0x005013c0
int __cdecl fcn_005013c0(unsigned short* id)
{
	int t[16] = { 1, 3, 4, 0xb, 0xd, 0xe, 0x12, 0x13, 0x15, 0x16, 0x1a, 0x1b, 0x1c, 0x1f, 0x21, 0 };
	Obj5013c0* o;
	int i;

	i = 0;
	o = &((Obj5013c0*)g_99ec10)[*id];
	while (t[i] != 0) {
		if (o->kind == t[i]) {
			return t[i];
		}
		i++;
	}
	return 0;
}

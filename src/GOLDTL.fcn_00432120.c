// FUNCTION: GOLDTL 0x432120

// SIZE 0xc0
typedef struct Rec {
	int pad[8];
	int a[3];
	int b[3];
	int rest[34];
} Rec;

void __cdecl fcn_00432120(int unused, char* obj, int idx, int* a, int* b)
{
	a[0] = (*(Rec**) (*(char**) (obj + 0x68) + 0x15c))[idx].a[0];
	a[1] = (*(Rec**) (*(char**) (obj + 0x68) + 0x15c))[idx].a[1];
	a[2] = (*(Rec**) (*(char**) (obj + 0x68) + 0x15c))[idx].a[2];
	b[0] = (*(Rec**) (*(char**) (obj + 0x68) + 0x15c))[idx].b[0];
	b[1] = (*(Rec**) (*(char**) (obj + 0x68) + 0x15c))[idx].b[1];
	b[2] = (*(Rec**) (*(char**) (obj + 0x68) + 0x15c))[idx].b[2];
}

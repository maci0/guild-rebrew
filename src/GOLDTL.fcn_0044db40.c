// FUNCTION: GOLD 0x0044f210
// FUNCTION: GOLDTL 0x44db40

typedef struct
{
	int pad0;
	int pad1;
	int idx;
	int pad2;
	int base;
} F4dRec;
// SIZE 0x14

void __cdecl fcn_00401180(int, char*);

void __cdecl fcn_0044db40(int a1, F4dRec* a2)
{
	fcn_00401180(a1, (char*) &a1);
	*(unsigned char*) ((char*) a2->base + a2->idx * 0xe0 + 0xc4) = (unsigned char) (a1 & 1);
	*(unsigned char*) ((char*) a2->base + a2->idx * 0xe0 + 0xc7) = (unsigned char) (a1 & 0xfe);
}

// FUNCTION: GOLD 0x0054d9e0
// FUNCTION: GOLDTL 0x555a40

#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	int c;
	short d;
} S14;

#pragma pack(pop)
// SIZE 0xe

int __cdecl gm_RandomMod(int);

void __cdecl fcn_00555a40(void* a1)
{
	*(S14*) ((char*) a1 + 0x52) = *(S14*) ((char*) a1 + 0x44);
	*(int*) ((char*) a1 + 0xb4) = gm_RandomMod(6) & 0xffff;
}

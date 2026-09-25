// FUNCTION: GOLD 0x004c58a0
// SIZE: 57
// FUNCTION: GOLDTL 0x4c6360
// SIZE: 57

void __cdecl fcn_004c4330(void*);

#pragma pack(push, 1)

typedef struct
{
	int a;
	short b;
	char c;
} Small7;
// SIZE 0x7

#pragma pack(pop)

void __cdecl fcn_004c6360(Small7* a1)
{
	char buf[0x9c];

	buf[0] = 0x44;
	*(Small7*) (buf + 0x10) = *a1;
	fcn_004c4330(buf);
}

void __cdecl fcn_0055afb0(char*);

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()


extern struct pos14 g_7f4c00;

// FUNCTION: GOLDTL 0x55afb0
// SIZE: 100

void __cdecl fcn_0055afb0(char* o)
{
	*(struct pos14*) (o + 0x52) = g_7f4c00;
	*(struct pos14*) (o + 0xac) = g_7f4c00;
	*(int*) (o + 0x70) = 0;
}

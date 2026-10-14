


void __cdecl fcn_004c4330(void*);

#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	int c;
	short d;
	char e;
} Packed15;

#pragma pack(pop)
// SIZE 0xf

void __cdecl fcn_004c63a0(Packed15* a1)
{
	char buf[0x9c];

	buf[0] = 0x45;
	*(Packed15*) (buf + 0x10) = *a1;
	fcn_004c4330(buf);
}

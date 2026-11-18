


void __cdecl fcn_004c4330(void*);

#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	short c;
} Small10;
// SIZE 0xa

#pragma pack(pop)

void __cdecl fcn_004c6b60(Small10* body)
{
	char buf[0x9c];

	buf[0] = 0x5c;
	*(Small10*) (buf + 0x10) = *body;
	fcn_004c4330(buf);
}

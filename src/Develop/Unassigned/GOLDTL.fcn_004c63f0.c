


void __cdecl fcn_004c4330(void*);

#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	char c;
} Small3;
// SIZE 0x9

#pragma pack(pop)

void __cdecl fcn_004c63f0(Small3* body)
{
	char buf[0x9c];

	buf[0] = 0x46;
	*(Small3*) (buf + 0x10) = *body;
	fcn_004c4330(buf);
}

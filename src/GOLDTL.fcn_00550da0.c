// FUNCTION: GOLDTL 0x550da0
// SIZE: 61

#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	int c;
	short d;
} S14b;

#pragma pack(pop)
// SIZE 0xe

int __cdecl fcn_0042e410(int);
void __cdecl fcn_00546190(void*);

void __cdecl fcn_00550da0(void* a1)
{
	*(S14b*) ((char*) a1 + 0x52) = *(S14b*) ((char*) a1 + 0x44);
	if ((short) fcn_0042e410(2) != 0) {
		fcn_00546190(a1);
	}
}

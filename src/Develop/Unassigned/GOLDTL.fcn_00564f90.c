

#pragma pack(push, 1)
typedef struct {
	int f0;
	int f4;
	int f8;
	unsigned short fc;
} fcn_00564f90_rec;
#pragma pack(pop)
// SIZE 0xe

void __cdecl fcn_00564f90(char* a1)
{
	*(fcn_00564f90_rec*) (a1 + 0x52) = *(fcn_00564f90_rec*) (a1 + 0x44);
}

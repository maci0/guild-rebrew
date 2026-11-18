


#pragma pack(push, 1)
typedef struct {
	int f0;
	int f4;
	int f8;
	unsigned short fc;
} fcn_00561250_rec;
#pragma pack(pop)
// SIZE 0xe

void __cdecl fcn_00561250(char* object)
{
	*(fcn_00561250_rec*) (object + 0x52) = *(fcn_00561250_rec*) (object + 0xb4);
}



#pragma pack(push, 1)
typedef struct {
	int f0;
	int f4;
	int f8;
	unsigned short fc;
} fcn_00566920_rec;
#pragma pack(pop)
// SIZE 0xe

void __cdecl fcn_00566920(char* obj)
{
	*(fcn_00566920_rec*) (obj + 0x52) = *(fcn_00566920_rec*) (obj + 0x44);
}

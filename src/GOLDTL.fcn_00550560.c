


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

int __cdecl gm_RandomMod(int);

void __cdecl fcn_00550560(char* e)
{
	*(int*) (e + 0xb0) = -1;
	*(Rec14*) (e + 0x52) = *(Rec14*) (e + 0x44);
	*(short*) (e + 0x56) += gm_RandomMod(4) + 2;
	*(int*) (e + 0x70) = 0;
}

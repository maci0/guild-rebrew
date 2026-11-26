


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

void __cdecl gm_AddTime(char*, int, int, int);

void __cdecl fcn_0055cc40(char* e)
{
	*(Rec14*) (e + 0x52) = *(Rec14*) (e + 0x44);
	gm_AddTime(e + 0x52, 0, 0xf, 0);
}

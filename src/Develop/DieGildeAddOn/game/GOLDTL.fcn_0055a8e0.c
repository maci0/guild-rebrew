

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

int __cdecl cm_SendSetHE(int, char*);

void __cdecl he_StartSideChange(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(Rec14*) (e + 0x52) = *(Rec14*) (e + 0x44);
		*(int*) (e + 0x84) = cm_SendSetHE(0, e);
	}
}

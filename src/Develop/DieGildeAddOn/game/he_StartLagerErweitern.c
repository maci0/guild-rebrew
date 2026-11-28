

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

void __cdecl gm_AddTime(char*, int, int, int);

/* ADDRESS: GOLDDE 0x00546170 */
void __cdecl he_StartLagerErweitern(char* e)
{
	*(Rec14*) (e + 0x52) = *(Rec14*) (e + 0x44);
	gm_AddTime(e + 0x52, 2, 0, 0);
}

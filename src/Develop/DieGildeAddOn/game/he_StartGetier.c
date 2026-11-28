


#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl he_AssignActionSlot(int, int, int, char*);
void __cdecl gm_AddTime(struct pos14*, int, int, int);

/* ADDRESS: GOLDDE 0x00546b10 */
void __cdecl he_StartGetier(char* e)
{
	char* p;
	int i;

	for (i = 0; i < *(unsigned char*) (e + 0xac); i++) {
		p = gm_LookupEntityRecordById(((int*) (e + 0x8c))[i]);
		if (p != 0) {
			he_AssignActionSlot(0, 0, *(unsigned short*) p, e);
		}
	}
	*(struct pos14*) (e + 0x52) = *(struct pos14*) (e + 0x44);
	gm_AddTime((struct pos14*) (e + 0x52), 0, 1, 0);
}

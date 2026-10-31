


typedef struct
{
	unsigned short id;
	char pad2[0x164];
	unsigned char x166;
	char pad167[0xb5];
} Ent21c;
// SIZE 0x21c

extern char g_7f4ca0[];
extern char g_679060[];

unsigned char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_005d52d0(unsigned char* a1, int* a2);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f7bf0(unsigned char* a1, int* a2)
{
	int i;
	int id;
	unsigned char* e;

	if (*a2 != 3 && *a2 != 1) {
		return 1;
	}
	if (a1[0xd] < 5) {
		return 1;
	}
	for (i = 0; i < 768; i++) {
		if (((Ent21c*)g_7f4ca0)[i].id != 0xffff && (((Ent21c*)g_7f4ca0)[i].x166 != 0x12 || ((Ent21c*)g_7f4ca0)[i].x166 <= 0x15)) {
			break;
		}
	}
	id = *(int*) (a1 + 0x5c);
	if (id == -1) {
		return 1;
	}
	if (i >= 0x300) {
		return 1;
	}
	e = gm_LookupEntityRecordById(id);
	if (e == 0) {
		return 1;
	}
	if (e[8] == 0) {
		return 1;
	}
	if (*a2 == 3) {
		return fcn_005d52d0(a1, a2);
	}
	if (*a2 == 1 && a1[2] == 6) {
		io_FormatTextBuffer((char*) a2 + 0x14, (int) g_679060, 0x1d8e);
	}
	return 2;
}

// FUNCTION: GOLDTL 0x560d30
// SIZE: 378

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

extern struct pos14 g_7f4c00;

char* __cdecl fcn_00508e40(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_00529160(char*, char*, int, char*);
void __cdecl fcn_00500bb0(struct pos14*, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00560d30(char* u)
{
	char* h;
	char* e;
	char* q;

	q = 0;
	h = fcn_00508e40(*(int*) (u + 0xb0));
	if (h != 0 && (*(char**) (h + 0x17c) == 0 || **(char**) (h + 0x17c) != 0x16)) {
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0x10));
		if (e != 0) {
			if (*(int*) (u + 0xb4) != -1) {
				q = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 1, *(int*) (u + 0xb4));
			}
			*(struct pos14*) (u + 0x52) = g_7f4c00;
			*(struct pos14*) (u + 0x44) = g_7f4c00;
			if (q != 0) {
				fcn_00529160(e, q, *(unsigned short*) h, u);
			} else {
				fcn_00529160(e, 0, *(unsigned short*) h, u);
			}
			*(struct pos14*) (u + 0x60) = g_7f4c00;
			fcn_00500bb0((struct pos14*) (u + 0x52), 0, 0x1e, 0);
			*(struct pos14*) (u + 0xb8) = *(struct pos14*) (u + 0x52);
			fcn_00500bb0((struct pos14*) (u + 0xb8), 6, 0, 0);
			if (*(unsigned short*) (u + 0xbc) < 6) {
				*(unsigned short*) (u + 0xbc) = *(unsigned short*) (u + 0xbc) - *(unsigned short*) (u + 0x56) + 0x1d;
			}
			return;
		}
	}
	fcn_00546190(u);
}

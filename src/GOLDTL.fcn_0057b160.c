// FUNCTION: GOLDTL 0x57b160
// SIZE: 142

#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad[0x24c];
};
#pragma pack()

// SIZE 0x21c
struct house {
	char pad[0x21c];
};

extern struct good* g_868050;
extern struct house g_7f4ca0[];

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_004f2a10(int, unsigned char*, int, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_005b2e50(struct house*, char*, unsigned char*, int);

void __cdecl fcn_0057b160(char* u)
{
	unsigned char* e;
	char* h;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
	if (e != 0 && g_868050[*e].kind == 0x1d) {
		fcn_004f2a10(0, e, *(int*) (u + 0xb0), *(unsigned char*) (u + 0xb4));
		h = fcn_00508e40(*(int*) (u + 0xc));
		if (h != 0) {
			fcn_005b2e50(&g_7f4ca0[*(unsigned short*) (e + 0x27)], h, e, *(int*) (u + 0xb0));
		}
	}
}

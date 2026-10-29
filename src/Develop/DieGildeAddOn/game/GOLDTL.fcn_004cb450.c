#include <string.h>

extern char g_68b0d8[];
extern char g_68b1f8[];
extern char g_68b214[];
extern char* lpObjektePROT;

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_004032b0(char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int, ...);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_00515540(char*);
int __cdecl fcn_005155e0(char*);
void __cdecl ch_UseGate(char*, char*, char*, int, int, int);
char* __cdecl strupr(char*);

/* ADDRESS: GOLDTL 0x004cb450 */
int __cdecl fcn_004cb450(char* a0, char* a1)
{
	char gate2[0x80];
	char search[0x80];
	char gate[0x80];
	char* o;
	char* s;
	char* d;
	char* v4;
	int id;
	int k;

	fcn_0064d41a(search, g_68b0d8, *(int*) (a0 + 0x10));
	o = fcn_004032b0(search);
	if (!o)
		return 1;
	s = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0x14));
	d = fcn_00502cd0(*(int*) (s + 0x5d), 1, 1, *(int*) (a0 + 0x18));
	id = *(int*) (o + 0x30);
	if (id != -1)
		v4 = fcn_00502cd0(*(int*) (s + 0x5d), 1, 1, id);
	else
		v4 = fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0xfd);
	if (*(unsigned short*) d == 0xfd) {
		k = fcn_005155e0(s);
		fcn_0064d41a(gate, g_68b1f8);
	} else {
		k = fcn_00515540(d);
		fcn_0064d41a(gate, g_68b214, strupr(lpObjektePROT + *(unsigned short*) d * 0x41 + 1));
	}
	fcn_0064d41a(gate2, g_68b214, strupr(lpObjektePROT + *(unsigned short*) v4 * 0x41 + 1));
	if (k >= 0)
		ch_UseGate(o, gate2, gate, k, *(int*) (s + 1), *(int*) (d + 2));
	if (a1) {
		a1[0] = 2;
		a1[1] = 0;
		*(int*) (a1 + 6) = 0;
	}
	return 0;
}

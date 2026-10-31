


extern int g_14ce8e0;
extern int g_774654;
extern int g_7746d8;
extern int g_7746a0;
extern int g_14b5458;
extern int g_14ad0f8;
extern int g_14b5400;
extern int g_14ad0f0;
extern int g_14ad100;
extern int g_14b53fc;
extern int g_14b59d0[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void (__cdecl*)(char*, char*), int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005ba8e0(char*);
void __cdecl fcn_005be140(char*, int);
void __cdecl fcn_0058acb0(char*, char*);
int __cdecl fcn_004ecf00(char*, int*, int*, int);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_005944d0(char*);
#ifdef REBREW_GOLD
#define fcn_00585030 fcn_0057c950
#endif

void __cdecl fcn_00585030(char*);
void __cdecl fcn_00585910(char*);
void __cdecl fcn_005848b0(char*);

void __cdecl fcn_0058aad0(char* a, char* b)
{
	int book;
	int alch;
	int x;
	int y;
	int contract;
	int store;
	int transport;
	int alchcontract;
	int r;

	contract = 0;
	store = 0;
	transport = 0;
	book = 0;
	alchcontract = 0;
	alch = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_0058aad0, 0x67fff) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_7746d8 & 0x200) {
			alch = fcn_005338d0("contact_REZEPTBUCH", g_14b5458, 0x16);
			book = fcn_005338d0("contact_PRODUKTION_ALCHIMIST", g_14ad0f8, 0x13);
		}
		if (g_7746d8 & 0x400) {
			contract = fcn_005338d0("contact_CONTRACT", g_14b5400, 0xe);
			store = fcn_005338d0("contact_LAGER", g_14ad0f0, 0xe);
			transport = fcn_005338d0("contact_TRANSPORT", g_14ad100, 0x15);
			alchcontract = fcn_005338d0("contact_ALCHIMISTENVERTRAG", g_14b53fc, 0x16);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == transport) {
				fcn_005ba8e0(a);
			} else if (g_7746a0 == store) {
				fcn_005be140(a, *(int*) (a + 0x5d));
			} else if (*(int*) (b + 0x1c) != 0) {
				fcn_0058acb0(a, b);
			} else if (g_7746a0 == book) {
				r = fcn_004ecf00(a, &y, &x, 0);
				if (r != 0) {
					fcn_00526120(g_14b59d0[r], 0x100);
				} else {
					fcn_005944d0(a);
				}
			} else if (g_7746a0 == alch) {
				fcn_00585030(a);
			} else if (g_7746a0 == alchcontract) {
				fcn_00585910(a);
			} else if (g_7746a0 == contract) {
				fcn_005848b0(a);
			}
		}
	}
}

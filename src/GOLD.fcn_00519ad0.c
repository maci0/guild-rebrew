extern int g_633444;
extern char* g_889f74;

#pragma pack(1)
// SIZE 0xa
struct ref_f31161 {
	char type;
	char pad[4];
	int ref;
	char pad2;
};
#pragma pack()

extern struct ref_f31161 g_f31161[0x8000];

// FUNCTION: GOLD 0x00519ad0
// SIZE: 169
/* Twin of GOLDTL 0x51ea70; the back-pointer field sits at 0x200 in GOLD, 0x204 in GOLDTL. */

void __cdecl fcn_004478e0(int, int);
int __cdecl fcn_00508e40(int);
int __cdecl fcn_004fe980(int);
int __cdecl fcn_00502020(int);
int __cdecl fcn_004e50a0(int);

void __cdecl fcn_00519ad0(void)
{
	int save;
	int i;
	char* e;

	save = g_633444;
	fcn_004478e0(0, 1);
	for (i = 0; i < 0x100; i++) {
		e = g_889f74 + i * 0xa9;
		if (*e != 0 && *(char**) (e + 0x61) != 0) {
			*(char**) (*(char**) (e + 0x61) + 0x200) = e;
		}
	}
	fcn_004478e0(save, 1);
	for (i = 0; i < 0x8000; i++) {
		if (g_f31161[i].ref != 0) {
			if (g_f31161[i].type == 1) {
				g_f31161[i].ref = fcn_00508e40(g_f31161[i].ref);
			}
			if (g_f31161[i].type == 3) {
				g_f31161[i].ref = fcn_004fe980(g_f31161[i].ref);
			}
			if (g_f31161[i].type == 2) {
				g_f31161[i].ref = fcn_00502020(g_f31161[i].ref);
			}
			if (g_f31161[i].type == 9) {
				g_f31161[i].ref = fcn_004e50a0(g_f31161[i].ref);
			}
		}
	}
}

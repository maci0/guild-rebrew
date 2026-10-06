// GLOBAL: GOLDTL 0x68cfc0
extern char g_68cfc0[];
// GLOBAL: GOLD 0x60e340
extern char g_68cfc0[];
// GLOBAL: GOLDTL 0x68cfec
extern char g_68cfec[];
// GLOBAL: GOLD 0x60e36c
extern char g_68cfec[];
/* Owned (both targets) by src/GOLDTL.fcn_00549330.c. */
extern char g_7f4ca4[];

// FUNCTION: GOLDTL 0x4e1ea0
// FUNCTION: GOLD 0x4e0580

void* __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_004e6240(void*, void*, char*, char*);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_004c5420(int, int, int, int, int);

int __cdecl fcn_004e1ea0(void* a1)
{
	char buf[0x200];
	void* e1;
	void* e2;
	char* p;

	e1 = fcn_00508e40(*(int*) ((char*) a1 + 0x34));
	e2 = fcn_00508e40(*(int*) ((char*) a1 + 0x38));
	if (e1 != 0) {
		if (e2 != 0 && *(char*) ((char*) e1 + 9) != *(char*) ((char*) e2 + 9)) {
			if (*(char*) ((char*) e1 + 2) == 6 || *(char*) ((char*) e1 + 2) == 7) {
				fcn_0051af00(buf, 0x11c3, *(unsigned short*) e2);
				fcn_004e6240(e1, a1, buf, g_68cfec);
			}
			if (*(char*) ((char*) e1 + 2) == 6 || *(char*) ((char*) e1 + 2) == 7 ||
			    *(char*) ((char*) e1 + 2) == 5) {
				fcn_0051af00(buf, 0x11c4, *(unsigned short*) e1, *(unsigned short*) e2);
				for (p = g_7f4ca4; (int) p < (int) (g_7f4ca4 + 0x65400); p += 0x21c) {
					if ((*(char*) (p - 2) == 6 || *(char*) (p - 2) == 7) &&
					    *(int*) p != *(int*) ((char*) e1 + 4) &&
					    *(int*) p != *(int*) ((char*) e2 + 4)) {
						fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, g_68cfc0);
					}
				}
			}
			if (*(char*) ((char*) e1 + 2) == 6 || *(char*) ((char*) e1 + 2) == 7) {
				return 1;
			}
		}
		fcn_004c5420(*(int*) ((char*) e1 + 4), 0x1c8, 4, 0, 0x40000);
	}
	if (e2 != 0) {
		fcn_004c5420(*(int*) ((char*) e2 + 4), 0x1c8, 4, 0, 0x40000);
	}
	return 0;
}

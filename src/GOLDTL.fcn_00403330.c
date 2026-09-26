// FUNCTION: GOLD 0x00402af0
// SIZE: 176
// FUNCTION: GOLDTL 0x00403330
// SIZE: 176

extern void* g_14d0020[];
extern int g_6b8010;
extern int g_6b5c34;
int __cdecl fcn_00413190(int p);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_00413120(int h);
void __cdecl fcn_00442be0(int h);
void __cdecl fcn_00403870(char* e);
void __cdecl fcn_004033e0(char* e);

void __cdecl fcn_00403330(unsigned char mode)
{
	int saved;
	char** p;
	char* e;

	saved = g_6b8010;
	p = ((char**)g_14d0020);
	do {
		e = *p;
		if (e != 0) {
			fcn_004432d0(fcn_00413190(*(int*) (e + 0x88)), 1);
			if (mode == 2) {
				if (*(int*) (e + 0x22c) != 0) {
					fcn_00413120(*(int*) (e + 0x22c));
					fcn_00442be0(*(int*) (e + 0x22c));
					*(int*) (e + 0x22c) = 0;
				}
			} else if ((mode == 0 || mode == 1) && *(int*) (e + 0x22c) == 0) {
				fcn_00403870(e);
				fcn_004033e0(e);
			}
		}
		p++;
	} while ((int) p < (int) (((char**)g_14d0020) + 0x300));
	g_6b5c34 = 2 - mode;
	fcn_004432d0(saved, 1);
}

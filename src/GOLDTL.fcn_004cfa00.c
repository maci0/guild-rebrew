// FUNCTION: GOLDTL 0x4cfa00
// SIZE: 113

extern int g_772f3c;
extern int g_14ce8e0;
extern char g_14cf950;

int __cdecl fcn_005373e0(int, int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);
void __cdecl fcn_004116d0(void);

void __cdecl fcn_004cfa00(int id)
{
	int r;

	if (g_772f3c != 0)
		return;
	if (fcn_005373e0(0, 0x7d6c6) != 0) {
		do {
			if (g_14ce8e0 != 0 || g_14cf950 != 0)
				break;
			if (fcn_00426cc0(id) == 0)
				return;
		} while (fcn_005373e0(0, 0x7d6c6) != 0);
	}
	r = fcn_00426cc0(id);
	if (r != 0)
		fcn_00428720(r);
	fcn_004116d0();
}

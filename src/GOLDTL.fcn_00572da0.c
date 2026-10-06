// FUNCTION: GOLDTL 0x572da0

extern int g_100f884;
extern int g_100f1dc;

void __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190();
void __cdecl fcn_00545780(char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00572da0(char* e)
{
	int id;

	switch (*(int*) (e + 0x70)) {
	case 0:
		id = *(int*) (e + 0xac);
		fcn_00545670(e, 0, 0, "Misc\\EventMessagebox", 0x5f2);
		fcn_004727a0(*(int*) (*(char**) (e + 0x74) + 8), 0);
		fcn_00519190("HE_NEUE_VORKOMMEN_SUCHEN_MSG: Ich bin ein Bug !!! %s gefunden!!", id * 2 + 0x9a8);
		*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
		return;
	case 1:
		if (g_100f884 != *(int*) (*(char**) (e + 0x74) + 8) || g_100f1dc == -1 || g_100f1dc != 2) {
			return;
		}
		/* fall through */
	case -2:
	case -1:
		fcn_00545780(e);
		fcn_00546190(e);
	}
}

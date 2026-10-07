// FUNCTION: GOLD 0x00599b80
// FUNCTION: GOLDTL 0x005a2d60

extern unsigned short g_774970;

char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_005a2580(char*, char*, char*);
void __cdecl fcn_005a2970(char*, char*);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005a2d60(char* a, char* b)
{
	char* e;

	e = fcn_00502cd0(*(int*) (b + 0x14), 1, 0, 0x12c);
	if (e != 0) {
		if (*(unsigned short*) (a + 0x27) == g_774970) {
			fcn_005a2580(a, b, e);
		}
		else {
			fcn_005a2970(a, e);
		}
	}
	fcn_00532ef0();
}

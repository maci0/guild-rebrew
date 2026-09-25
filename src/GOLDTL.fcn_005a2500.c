// FUNCTION: GOLD 0x599320
// SIZE: 124
// FUNCTION: GOLDTL 0x005a2500
// SIZE: 124

typedef struct
{
	unsigned short x0;
	char pad2[0x21a];
} Player;
// SIZE 0x21c

extern unsigned short g_774970;
extern Player g_7f4ca0[];

char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl fcn_005463a0(int, int, int, int, int);
void __cdecl fcn_005a1e40(char*, char*);
void __cdecl fcn_005a2080(char*, char*);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005a2500(char* a, char* b)
{
	char* e;

	e = fcn_00502cd0(*(int*) (b + 0x14), 1, 0, 0x12d);
	if (e != 0 && fcn_005463a0(2, 0, 0x2a, 3, *(int*) (a + 1)) != 0) {
		if (g_7f4ca0[g_774970].x0 == *(unsigned short*) (a + 0x27)) {
			fcn_005a1e40(a, e);
		}
		else {
			fcn_005a2080(a, e);
		}
	}
	fcn_00532ef0();
}

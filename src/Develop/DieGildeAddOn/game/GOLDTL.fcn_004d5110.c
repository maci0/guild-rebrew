extern unsigned char g_773d75;
extern double g_662a20;
extern double g_664f18;
extern double g_6640e8;

char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_AccumulateTyped2(char* entity);
int __cdecl fcn_004c5150(int a1, int a2, char a3, int a4);
int __cdecl fcn_004c51f0(int a1, int a2, int a3, int a4, char a5, int a6);
float __cdecl fcn_0050bb50(int id, unsigned char a);
unsigned int __cdecl fcn_004e6cb0(unsigned int n);
int __cdecl _ftol(void);
char* __cdecl gm_NextEntityQueryMatch(void);
short* __cdecl gm_GetEntityTableEntry(char* entity);

/* ADDRESS: GOLDTL 0x004d5110 */
int __cdecl fcn_004d5110(char* a1, char* a2, char* a3, char* a4)
{
	char* p1;
	char* p2;
	char* match;
	int v;
	int delay;

	p1 = fcn_00502cd0(*(int*) (a2 + 0x5d), 2, 6, 0, 0x116);
	p2 = fcn_00502cd0(*(int*) (a1 + 0x5d), 2, 6, 0, 0x2a);
	v = gm_AccumulateTyped2(a4);
	v = v < 0 ? 0 : v;
	if (v >= 0x9c400) {
		v = 0x9c400;
	}
	v = (int) (((double) fcn_004e6cb0(0x32) * g_662a20 + g_664f18) * v);
	fcn_004c5150(*(int*) (a3 + 4), *(int*) (a4 + 4), g_773d75, v);
	if (p2 != 0 && p1 != 0) {
		match = fcn_00502cd0(*(int*) (p2 + 0x14), 1, 5);
		while (match != 0) {
			delay = (int) (((double) (fcn_004e6cb0(0x14) + 0x50) * g_6640e8) * *(int*) (match + 0xe));
			if (delay < 1) {
				delay = 1;
			}
			fcn_004c51f0(*(int*) (p1 + 2), *(int*) (p2 + 2), (unsigned int) (unsigned short) *(short*) match, delay, g_773d75, 0);
			v = (int) (fcn_0050bb50(*(unsigned short*) match, g_773d75) * delay + v);
			match = gm_NextEntityQueryMatch();
		}
	}
	p1 = (char*) gm_GetEntityTableEntry(a3);
	if (p1 != 0) {
		*(int*) (p1 + 0x1c) += v;
	}
	return v;
}

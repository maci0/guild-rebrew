typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

extern int g_14cbca0;
extern int g_699364;
extern int g_68a9d8;

char* __cdecl gm_SearchTable67(int);
char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl fcn_00502fe0(int, int, int);

// FUNCTION: GOLDTL 0x4cd860
// SIZE: 284

int __cdecl fcn_004cd860(char* a1, char* a2)
{
	char* e1;
	char* e2;
	char* q;

	if (g_14cbca0 != -1)
		g_699364 = *(int*) (a1 + 0x10);
	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	e1 = gm_SearchTable67(*(int*) (a1 + 0x26));
	if (e1 == 0)
		return 1;
	e2 = gm_SearchTable67(*(int*) (a1 + 0x14));
	if (e2 == 0)
		return 1;
	for (q = fcn_00502cd0(*(int*) (e2 + 0x5d), 1, 0, 0xca); q != 0; q = gm_NextEntityQueryMatch()) {
		if (*(int*) (q + 0x2a) == *(int*) (e1 + 1))
			goto found;
	}
	q = fcn_00502fe0(*(int*) (e2 + 1), 0xca, 1);
	if (q == 0)
		return 1;
	g_68a9d8 = *(int*) (q + 2);
found:
	*(stamp14*) (q + 0x1c) = *(stamp14*) (a1 + 0x18);
	*(int*) (q + 0x2a) = *(int*) (a1 + 0x26);
	*(int*) (q + 0x32) = *(int*) (a1 + 0x2e);
	q[0x36] = a1[0x32];
	*(unsigned char*) (q + 0x37) += a1[0x33];
	*(unsigned char*) (q + 0x37) = *(unsigned char*) (q + 0x37) > 100 ? 100 : *(unsigned char*) (q + 0x37);
	if (a2 != 0)
		a2[0] = 1;
	return 0;
}

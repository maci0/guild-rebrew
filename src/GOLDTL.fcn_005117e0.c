// FUNCTION: GOLDTL 0x005117e0
// SIZE: 285

extern char* g_773dac;
extern char* g_773db0;
extern char* g_aed32c;

void __cdecl fcn_004c44a0(void);
int __cdecl fcn_004c4fc0(int a, int b, int c, int d, int e, int f, int g, int h);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_004c3ff0(void);
void __cdecl fcn_004c4940(void);
void __cdecl ls_ID2Ptr(void);
int* __cdecl fcn_004c4480(int h);
void __cdecl fcn_004c4510(int* p, int n);
void __cdecl fcn_004c4570(int a, int b, int off, int* v);
void __cdecl fcn_004c5360(void);

void __cdecl fcn_005117e0(void)
{
	int a;
	int b;
	int v;

	fcn_004c44a0();
	a = fcn_004c4fc0(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	b = fcn_004c4fc0(0xc, -1, -1, 0x12, -1, 0, 0, 0);
	fcn_004c44b0();
	while (!fcn_004c44c0()) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
	(*(int**)&g_773dac) = fcn_004c4480(a);
	(*(int**)&g_773db0) = fcn_004c4480(b);
	fcn_004c44a0();
	v = 0;
	fcn_004c4510((*(int**)&g_773dac), (*(int**)&g_773dac)[1]);
	fcn_004c4570(1, 1, (int) (*(int**)&g_773dac) - (*(int*)&g_aed32c) + 0xc, &v);
	fcn_004c5360();
	v = 1;
	fcn_004c4510((*(int**)&g_773db0), (*(int**)&g_773db0)[1]);
	fcn_004c4570(1, 1, (int) (*(int**)&g_773db0) - (*(int*)&g_aed32c) + 0xc, &v);
	fcn_004c5360();
	fcn_004c44b0();
	while (!fcn_004c44c0()) {
		fcn_004c3ff0();
		fcn_004c4940();
		ls_ID2Ptr();
	}
}

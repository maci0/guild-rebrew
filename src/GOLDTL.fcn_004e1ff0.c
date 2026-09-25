// FUNCTION: GOLD 0x004e06d0
// SIZE: 156
// FUNCTION: GOLDTL 0x4e1ff0
// SIZE: 156

extern char g_68d00c[];
extern char g_6b5c60[];
extern int g_772f54;
extern int g_7725c8;

void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004237f0(int, int);
void __cdecl fcn_004230e0(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004e4610(int);
int __cdecl fcn_004e44b0(char*, char*);
void __cdecl fcn_004e44f0(int);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004e4eb0(void);

int __cdecl fcn_004e1ff0(int* x)
{
	fcn_004e48b0();
	if (x[3] != 0)
		fcn_004237f0(x[3], 0);
	x[3] = 0;
	fcn_004230e0(x[2]);
	if (x[1] != -1)
		fcn_00471e30(x[1]);
	if (x[0] != -1)
		fcn_004e4610(x[0]);
	x[0] = fcn_004e44b0(g_68d00c, g_6b5c60);
	fcn_004e44f0(x[0]);
	x[0] = -1;
	x[1] = -1;
	g_772f54 = 0;
	fcn_004e4910();
	fcn_004e4eb0();
	g_7725c8 = 0;
	return 1;
}
